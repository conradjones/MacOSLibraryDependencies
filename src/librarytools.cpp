#include <iostream>

#include "file_system.h"
#include "librarytools.h"
#include "process.h"
#include "string_utils.h"
#include <stdexcept>
#include <string>
#include <vector>

bool findAndCopyDependency(const std::vector<std::string>& library_paths, const std::string& libOrFramework, const boost::filesystem::path& destination)
{
    std::cout << "Looking for library : " << libOrFramework << "\n";

    boost::filesystem::path destLibOrFrameworkPath = destination / libOrFramework;

    for (auto library_path : library_paths) {
        auto testLibrarySourcePath = boost::filesystem::path(library_path) / libOrFramework;
        if (!boost::filesystem::exists(testLibrarySourcePath)) {
            continue;
        }
        if (boost::filesystem::is_directory(testLibrarySourcePath)) {
            recursive_copy(testLibrarySourcePath, destLibOrFrameworkPath, { "Headers", "PrivateHeaders", "Modules" }, { ".h" });
            return true;
        } else if (boost::filesystem::is_regular_file(testLibrarySourcePath)) {
            boost::filesystem::copy_file(testLibrarySourcePath, destLibOrFrameworkPath);
            return true;
        }
    }
    return false;
}

bool findAndCopyDependencies(const std::vector<std::string>& library_paths, const boost::filesystem::path& binary, const std::string& newRPath, const boost::filesystem::path& destinationPath)
{
    bool flag = true;


    auto libraries = otoolFindLibraries(binary, [newRPath](const std::string& line) {
        return startsWith(line, newRPath);
    });

    for (auto lib : libraries) {
        std::string newPath = lib;
        std::cout << lib << "\n";
        newPath.replace(0, newRPath.length(), "");
        newPath = trimR<'/'>(newPath);

        std::cout << newPath << "\n";

        auto testDestPath = destinationPath / newPath;

        if (boost::filesystem::exists(testDestPath)) {
            std::cout << "Skipping: " << testDestPath << "\n";
            continue;
        }

        if (!findAndCopyDependency(library_paths, newPath, destinationPath)) {
            flag = false;
        }
    }

    return flag;
}

void patch_rpaths(const std::string& newRPath, const boost::filesystem::path& binary)
{
    std::string_view rpath_str = "@rpath/";
    auto libraryList = otoolFindLibraries(binary, [rpath_str](const std::string& line) {
        return line.rfind(rpath_str, 0) == 0;
    });
    for (auto lib : libraryList) {
        std::string newPath = lib;
        newPath.replace(0, rpath_str.length(), newRPath);
        std::string installNameTool = "/usr/bin/install_name_tool -change \"" + lib + "\" \"" + newPath + "\" " + binary.string();
        std::cout << installNameTool << "\n";
        exec(installNameTool.c_str());
    }
}
