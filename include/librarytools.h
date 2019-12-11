#ifndef MACOS_BUNDLE_DEPS_LIBRARY_TOOLS_H
#define MACOS_BUNDLE_DEPS_LIBRARY_TOOLS_H

#include "process.h"
#include "string_utils.h"
#include <boost/filesystem.hpp>
#include <iostream>
#include <vector>

template <typename PREDICATE>
std::vector<std::string> otoolFindLibraries(const boost::filesystem::path& binary, PREDICATE predicate)
{
    auto result = std::vector<std::string>();

    std::string otoolL = "/usr/bin/otool -L " + binary.string();
    auto out = exec(otoolL.c_str());

    std::string line;

    while (std::getline(out, line, '\n')) {
        line = trimL<' '>(line);
        line = trimL<'\t'>(line);
        line = trimR<' '>(line);
        if (predicate(line)) {
            result.push_back(line);
        }
    }

    return result;
}

bool findAndCopyDependency(const std::vector<std::string>& library_paths, const std::string& libOrFramework, const boost::filesystem::path& destination);
bool findAndCopyDependencies(const std::vector<std::string>& library_paths, const boost::filesystem::path& binary, const std::string& newRPath, const boost::filesystem::path& destinationPath);
void patch_rpaths(const std::string& newRPath, const boost::filesystem::path& binary);

int do_main(const std::string& binary, const std::string& library_paths_str, const std::string& new_rpath, const boost::filesystem::path& library_destination);

#endif
