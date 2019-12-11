#include "librarytools.h"
#include <stdexcept>

int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cout << "Usage:" << argv[0] << " <binary> <library_path1;library_path2>\n";
        return 1;
    }
    std::string binary = argv[1];
    std::string library_paths_str = argv[2];

    auto framework_path = boost::filesystem::path(binary).parent_path().parent_path() / "Frameworks";
    return do_main(binary, library_paths_str, "@executable_path/../Frameworks/", framework_path);
}