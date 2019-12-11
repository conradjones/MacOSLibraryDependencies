#ifndef MACOS_BUNDLE_DEPS_PROCESS_H
#define MACOS_BUNDLE_DEPS_PROCESS_H

#include <sstream>
#include <array>


inline std::stringstream exec(std::string cmd)
{
    std::array<char, 128> buffer;
    std::stringstream result;
    cmd += " 2>&1";
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str() , "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result << buffer.data();
    }
    return result;
}

#endif //FIX_RPATHS_PROCESS_H
