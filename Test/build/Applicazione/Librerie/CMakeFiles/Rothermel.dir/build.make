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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/luca/Scrivania/Introduzione sistemi complessi/Progetto/git/ProgettoFisica/Test"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/luca/Scrivania/Introduzione sistemi complessi/Progetto/git/ProgettoFisica/Test/build"

# Include any dependencies generated for this target.
include Applicazione/Librerie/CMakeFiles/Rothermel.dir/depend.make

# Include the progress variables for this target.
include Applicazione/Librerie/CMakeFiles/Rothermel.dir/progress.make

# Include the compile flags for this target's objects.
include Applicazione/Librerie/CMakeFiles/Rothermel.dir/flags.make

Applicazione/Librerie/CMakeFiles/Rothermel.dir/src/Rothermel.cxx.o: Applicazione/Librerie/CMakeFiles/Rothermel.dir/flags.make
Applicazione/Librerie/CMakeFiles/Rothermel.dir/src/Rothermel.cxx.o: ../Applicazione/Librerie/src/Rothermel.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/luca/Scrivania/Introduzione sistemi complessi/Progetto/git/ProgettoFisica/Test/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Applicazione/Librerie/CMakeFiles/Rothermel.dir/src/Rothermel.cxx.o"
	cd "/home/luca/Scrivania/Introduzione sistemi complessi/Progetto/git/ProgettoFisica/Test/build/Applicazione/Librerie" && /bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Rothermel.dir/src/Rothermel.cxx.o -c "/home/luca/Scrivania/Introduzione sistemi complessi/Progetto/git/ProgettoFisica/Test/Applicazione/Librerie/src/Rothermel.cxx"

Applicazione/Librerie/CMakeFiles/Rothermel.dir/src/Rothermel.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Rothermel.dir/src/Rothermel.cxx.i"
	cd "/home/luca/Scrivania/Introduzione sistemi complessi/Progetto/git/ProgettoFisica/Test/build/Applicazione/Librerie" && /bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/luca/Scrivania/Introduzione sistemi complessi/Progetto/git/ProgettoFisica/Test/Applicazione/Librerie/src/Rothermel.cxx" > CMakeFiles/Rothermel.dir/src/Rothermel.cxx.i

Applicazione/Librerie/CMakeFiles/Rothermel.dir/src/Rothermel.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Rothermel.dir/src/Rothermel.cxx.s"
	cd "/home/luca/Scrivania/Introduzione sistemi complessi/Progetto/git/ProgettoFisica/Test/build/Applicazione/Librerie" && /bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/luca/Scrivania/Introduzione sistemi complessi/Progetto/git/ProgettoFisica/Test/Applicazione/Librerie/src/Rothermel.cxx" -o CMakeFiles/Rothermel.dir/src/Rothermel.cxx.s

# Object files for target Rothermel
Rothermel_OBJECTS = \
"CMakeFiles/Rothermel.dir/src/Rothermel.cxx.o"

# External object files for target Rothermel
Rothermel_EXTERNAL_OBJECTS =

Applicazione/Librerie/libRothermel.a: Applicazione/Librerie/CMakeFiles/Rothermel.dir/src/Rothermel.cxx.o
Applicazione/Librerie/libRothermel.a: Applicazione/Librerie/CMakeFiles/Rothermel.dir/build.make
Applicazione/Librerie/libRothermel.a: Applicazione/Librerie/CMakeFiles/Rothermel.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/luca/Scrivania/Introduzione sistemi complessi/Progetto/git/ProgettoFisica/Test/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libRothermel.a"
	cd "/home/luca/Scrivania/Introduzione sistemi complessi/Progetto/git/ProgettoFisica/Test/build/Applicazione/Librerie" && $(CMAKE_COMMAND) -P CMakeFiles/Rothermel.dir/cmake_clean_target.cmake
	cd "/home/luca/Scrivania/Introduzione sistemi complessi/Progetto/git/ProgettoFisica/Test/build/Applicazione/Librerie" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Rothermel.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Applicazione/Librerie/CMakeFiles/Rothermel.dir/build: Applicazione/Librerie/libRothermel.a

.PHONY : Applicazione/Librerie/CMakeFiles/Rothermel.dir/build

Applicazione/Librerie/CMakeFiles/Rothermel.dir/clean:
	cd "/home/luca/Scrivania/Introduzione sistemi complessi/Progetto/git/ProgettoFisica/Test/build/Applicazione/Librerie" && $(CMAKE_COMMAND) -P CMakeFiles/Rothermel.dir/cmake_clean.cmake
.PHONY : Applicazione/Librerie/CMakeFiles/Rothermel.dir/clean

Applicazione/Librerie/CMakeFiles/Rothermel.dir/depend:
	cd "/home/luca/Scrivania/Introduzione sistemi complessi/Progetto/git/ProgettoFisica/Test/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/luca/Scrivania/Introduzione sistemi complessi/Progetto/git/ProgettoFisica/Test" "/home/luca/Scrivania/Introduzione sistemi complessi/Progetto/git/ProgettoFisica/Test/Applicazione/Librerie" "/home/luca/Scrivania/Introduzione sistemi complessi/Progetto/git/ProgettoFisica/Test/build" "/home/luca/Scrivania/Introduzione sistemi complessi/Progetto/git/ProgettoFisica/Test/build/Applicazione/Librerie" "/home/luca/Scrivania/Introduzione sistemi complessi/Progetto/git/ProgettoFisica/Test/build/Applicazione/Librerie/CMakeFiles/Rothermel.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : Applicazione/Librerie/CMakeFiles/Rothermel.dir/depend

