# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = "/Users/andreadarpa/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/202.7660.37/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/andreadarpa/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/202.7660.37/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug

# Include any dependencies generated for this target.
include Classi/CMakeFiles/Fire.dir/depend.make

# Include the progress variables for this target.
include Classi/CMakeFiles/Fire.dir/progress.make

# Include the compile flags for this target's objects.
include Classi/CMakeFiles/Fire.dir/flags.make

Classi/CMakeFiles/Fire.dir/src/Fire.cxx.o: Classi/CMakeFiles/Fire.dir/flags.make
Classi/CMakeFiles/Fire.dir/src/Fire.cxx.o: ../Classi/src/Fire.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Classi/CMakeFiles/Fire.dir/src/Fire.cxx.o"
	cd /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug/Classi && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Fire.dir/src/Fire.cxx.o -c /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/Classi/src/Fire.cxx

Classi/CMakeFiles/Fire.dir/src/Fire.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Fire.dir/src/Fire.cxx.i"
	cd /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug/Classi && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/Classi/src/Fire.cxx > CMakeFiles/Fire.dir/src/Fire.cxx.i

Classi/CMakeFiles/Fire.dir/src/Fire.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Fire.dir/src/Fire.cxx.s"
	cd /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug/Classi && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/Classi/src/Fire.cxx -o CMakeFiles/Fire.dir/src/Fire.cxx.s

# Object files for target Fire
Fire_OBJECTS = \
"CMakeFiles/Fire.dir/src/Fire.cxx.o"

# External object files for target Fire
Fire_EXTERNAL_OBJECTS =

Classi/libFire.a: Classi/CMakeFiles/Fire.dir/src/Fire.cxx.o
Classi/libFire.a: Classi/CMakeFiles/Fire.dir/build.make
Classi/libFire.a: Classi/CMakeFiles/Fire.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libFire.a"
	cd /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug/Classi && $(CMAKE_COMMAND) -P CMakeFiles/Fire.dir/cmake_clean_target.cmake
	cd /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug/Classi && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Fire.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Classi/CMakeFiles/Fire.dir/build: Classi/libFire.a

.PHONY : Classi/CMakeFiles/Fire.dir/build

Classi/CMakeFiles/Fire.dir/clean:
	cd /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug/Classi && $(CMAKE_COMMAND) -P CMakeFiles/Fire.dir/cmake_clean.cmake
.PHONY : Classi/CMakeFiles/Fire.dir/clean

Classi/CMakeFiles/Fire.dir/depend:
	cd /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/Classi /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug/Classi /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug/Classi/CMakeFiles/Fire.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Classi/CMakeFiles/Fire.dir/depend
