#ifndef MACOS_BUNDLE_DEPS_FILE_SYSTEM_H
#define MACOS_BUNDLE_DEPS_FILE_SYSTEM_H

#include <cstdio>
#include <iostream>
#include <boost/filesystem.hpp>

template <typename VALUE, typename CONTAINER>
inline bool contains(const VALUE& value, const CONTAINER& container)
{
    return (std::find(container.begin(), container.end(), value) != container.end());
}

inline void recursive_copy(const boost::filesystem::path& src, const boost::filesystem::path& dst, std::vector<std::string> filterFolders, std::vector<std::string> filterOutExts)
{
    if (boost::filesystem::exists(dst)) {
        throw std::runtime_error(dst.generic_string() + " exists");
    }

    if (boost::filesystem::is_directory(src)) {
        std::cout << src.string() << "\n";
        if (contains(src.filename().string(), filterFolders)) {
            return;
        }
        boost::filesystem::create_directories(dst);
        for (boost::filesystem::directory_entry& item : boost::filesystem::directory_iterator(src)) {
            recursive_copy(item.path(), dst / item.path().filename(), filterFolders, filterOutExts);
        }
    } else if (boost::filesystem::is_regular_file(src)) {
        if (contains(src.extension().string(), filterOutExts)) {
            return;
        }
        boost::filesystem::copy(src, dst);
    } else {
        throw std::runtime_error(dst.generic_string() + " not dir or file");
    }
}

#endif //MACOS_BUNDLE_DEPS_FILE_SYSTEM_H
