cmake_minimum_required(VERSION 3.15)
project(MacOSLibraryDependencies)

set(CMAKE_CXX_STANDARD 14)

include(conan.cmake)

conan_cmake_run(CONANFILE conanfile.txt
        BASIC_SETUP
        PROFILE default)

include_directories("include")

add_executable(macho_bundle_deps src/_main_.cpp src/main_bundle.cpp src/librarytools.cpp)
target_link_libraries(macho_bundle_deps boost_filesystem)

add_executable(macho_standalone_deps src/_main_.cpp src/main_standalone.cpp src/librarytools.cpp)
target_link_libraries(macho_standalone_deps boost_filesystem)