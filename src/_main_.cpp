#include "librarytools.h"
#include <boost/algorithm/string.hpp>
#include <stdexcept>
#include <vector>

int do_main(const std::string& binary, const std::string& library_paths_str, const std::string& new_rpath, const boost::filesystem::path& library_destination)
{
    auto library_paths = std::vector<std::string>();
    boost::split(library_paths, library_paths_str, boost::is_any_of(";"));

    patch_rpaths(new_rpath, binary);

    if (!findAndCopyDependencies(library_paths, binary, new_rpath, library_destination)) {
        return 1;
    }

    return 0;
}
