# MacOSLibraryDependencies
Copy dylibs / frameworks to the bundle frameworks folder or standalone executable folder and fix the rpaths


This is a quick/simple utility to copy the frameworks and dylibs required by an executable or a bundle to 
either the executables folder or the bundle's frameworks folder respectively. 

It is expected to be used as part of a CI pipeline.

Usage :

--> Fixes a standalone executable

macho_standalone_deps <binary> <list_of_library_paths_to_search>

--> Fixes an app bundle

macho_bundle_deps <binary> <list_of_library_paths_to_search>
