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
include CMakeFiles/TEST.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TEST.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TEST.dir/flags.make

CMakeFiles/TEST.dir/Main.cxx.o: CMakeFiles/TEST.dir/flags.make
CMakeFiles/TEST.dir/Main.cxx.o: ../Main.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TEST.dir/Main.cxx.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TEST.dir/Main.cxx.o -c /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/Main.cxx

CMakeFiles/TEST.dir/Main.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TEST.dir/Main.cxx.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/Main.cxx > CMakeFiles/TEST.dir/Main.cxx.i

CMakeFiles/TEST.dir/Main.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TEST.dir/Main.cxx.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/Main.cxx -o CMakeFiles/TEST.dir/Main.cxx.s

# Object files for target TEST
TEST_OBJECTS = \
"CMakeFiles/TEST.dir/Main.cxx.o"

# External object files for target TEST
TEST_EXTERNAL_OBJECTS =

TEST: CMakeFiles/TEST.dir/Main.cxx.o
TEST: CMakeFiles/TEST.dir/build.make
TEST: Librerie/libRothermel.a
TEST: Classi/libVertex.a
TEST: Classi/libCiclicVector.a
TEST: Classi/libWaveFront.a
TEST: Classi/libFire.a
TEST: Classi/libFuel.a
TEST: Classi/libCell.a
TEST: Classi/libEnvironment.a
TEST: Librerie/libRothermel.a
TEST: Classi/libCell.a
TEST: Classi/libFuel.a
TEST: Classi/libFire.a
TEST: Classi/libWaveFront.a
TEST: Classi/libCiclicVector.a
TEST: Classi/libVertex.a
TEST: Librerie/libRothermel.a
TEST: CMakeFiles/TEST.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TEST"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TEST.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TEST.dir/build: TEST

.PHONY : CMakeFiles/TEST.dir/build

CMakeFiles/TEST.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TEST.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TEST.dir/clean

CMakeFiles/TEST.dir/depend:
	cd /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug /Users/andreadarpa/Desktop/ProgettoFisica/ProgettoFisica/Calcolo/cmake-build-debug/CMakeFiles/TEST.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TEST.dir/depend
