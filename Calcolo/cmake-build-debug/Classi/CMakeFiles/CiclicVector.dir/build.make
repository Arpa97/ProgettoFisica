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
include Classi/CMakeFiles/CiclicVector.dir/depend.make

# Include the progress variables for this target.
include Classi/CMakeFiles/CiclicVector.dir/progress.make

# Include the compile flags for this target's objects.
include Classi/CMakeFiles/CiclicVector.dir/flags.make

Classi/CMakeFiles/CiclicVector.dir/src/CiclicVector.cxx.o: Classi/CMakeFiles/CiclicVector.dir/flags.make
Classi/CMakeFiles/CiclicVector.dir/src/CiclicVector.cxx.o: ../Classi/src/CiclicVector.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Classi/CMakeFiles/CiclicVector.dir/src/CiclicVector.cxx.o"
	cd /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug/Classi && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CiclicVector.dir/src/CiclicVector.cxx.o -c /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/Classi/src/CiclicVector.cxx

Classi/CMakeFiles/CiclicVector.dir/src/CiclicVector.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CiclicVector.dir/src/CiclicVector.cxx.i"
	cd /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug/Classi && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/Classi/src/CiclicVector.cxx > CMakeFiles/CiclicVector.dir/src/CiclicVector.cxx.i

Classi/CMakeFiles/CiclicVector.dir/src/CiclicVector.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CiclicVector.dir/src/CiclicVector.cxx.s"
	cd /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug/Classi && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/Classi/src/CiclicVector.cxx -o CMakeFiles/CiclicVector.dir/src/CiclicVector.cxx.s

# Object files for target CiclicVector
CiclicVector_OBJECTS = \
"CMakeFiles/CiclicVector.dir/src/CiclicVector.cxx.o"

# External object files for target CiclicVector
CiclicVector_EXTERNAL_OBJECTS =

Classi/libCiclicVector.a: Classi/CMakeFiles/CiclicVector.dir/src/CiclicVector.cxx.o
Classi/libCiclicVector.a: Classi/CMakeFiles/CiclicVector.dir/build.make
Classi/libCiclicVector.a: Classi/CMakeFiles/CiclicVector.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libCiclicVector.a"
	cd /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug/Classi && $(CMAKE_COMMAND) -P CMakeFiles/CiclicVector.dir/cmake_clean_target.cmake
	cd /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug/Classi && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CiclicVector.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Classi/CMakeFiles/CiclicVector.dir/build: Classi/libCiclicVector.a

.PHONY : Classi/CMakeFiles/CiclicVector.dir/build

Classi/CMakeFiles/CiclicVector.dir/clean:
	cd /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug/Classi && $(CMAKE_COMMAND) -P CMakeFiles/CiclicVector.dir/cmake_clean.cmake
.PHONY : Classi/CMakeFiles/CiclicVector.dir/clean

Classi/CMakeFiles/CiclicVector.dir/depend:
	cd /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/Classi /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug/Classi /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug/Classi/CMakeFiles/CiclicVector.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Classi/CMakeFiles/CiclicVector.dir/depend

