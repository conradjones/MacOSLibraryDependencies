#ifndef MACOS_BUNDLE_DEPS_STRING_UTILS_H
#define MACOS_BUNDLE_DEPS_STRING_UTILS_H

template <char CHAR>
std::string trimL(const std::string& str)
{
    size_t first = str.find_first_not_of(CHAR);
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(CHAR);
    return str.substr(first, (last - first + 1));
}

template <char CHAR>
std::string trimR(const std::string& str)
{
    size_t last = str.find_first_of(CHAR);
    return str.substr(0, last);
}

inline bool startsWith(const std::string& stringToLookAt, const std::string& wantedStart)
{
    return stringToLookAt.rfind(wantedStart, 0) == 0;
}

#endif //MACOS_BUNDLE_DEPS_STRING_UTILS_H
