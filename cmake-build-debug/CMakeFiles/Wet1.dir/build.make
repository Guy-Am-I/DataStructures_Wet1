# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/guy_steinberg/Documents/DataStructures/Wet1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/guy_steinberg/Documents/DataStructures/Wet1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Wet1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Wet1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Wet1.dir/flags.make

CMakeFiles/Wet1.dir/main1.cpp.o: CMakeFiles/Wet1.dir/flags.make
CMakeFiles/Wet1.dir/main1.cpp.o: ../main1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/guy_steinberg/Documents/DataStructures/Wet1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Wet1.dir/main1.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Wet1.dir/main1.cpp.o -c /Users/guy_steinberg/Documents/DataStructures/Wet1/main1.cpp

CMakeFiles/Wet1.dir/main1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Wet1.dir/main1.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/guy_steinberg/Documents/DataStructures/Wet1/main1.cpp > CMakeFiles/Wet1.dir/main1.cpp.i

CMakeFiles/Wet1.dir/main1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Wet1.dir/main1.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/guy_steinberg/Documents/DataStructures/Wet1/main1.cpp -o CMakeFiles/Wet1.dir/main1.cpp.s

CMakeFiles/Wet1.dir/library1.cpp.o: CMakeFiles/Wet1.dir/flags.make
CMakeFiles/Wet1.dir/library1.cpp.o: ../library1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/guy_steinberg/Documents/DataStructures/Wet1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Wet1.dir/library1.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Wet1.dir/library1.cpp.o -c /Users/guy_steinberg/Documents/DataStructures/Wet1/library1.cpp

CMakeFiles/Wet1.dir/library1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Wet1.dir/library1.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/guy_steinberg/Documents/DataStructures/Wet1/library1.cpp > CMakeFiles/Wet1.dir/library1.cpp.i

CMakeFiles/Wet1.dir/library1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Wet1.dir/library1.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/guy_steinberg/Documents/DataStructures/Wet1/library1.cpp -o CMakeFiles/Wet1.dir/library1.cpp.s

# Object files for target Wet1
Wet1_OBJECTS = \
"CMakeFiles/Wet1.dir/main1.cpp.o" \
"CMakeFiles/Wet1.dir/library1.cpp.o"

# External object files for target Wet1
Wet1_EXTERNAL_OBJECTS =

Wet1: CMakeFiles/Wet1.dir/main1.cpp.o
Wet1: CMakeFiles/Wet1.dir/library1.cpp.o
Wet1: CMakeFiles/Wet1.dir/build.make
Wet1: CMakeFiles/Wet1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/guy_steinberg/Documents/DataStructures/Wet1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Wet1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Wet1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Wet1.dir/build: Wet1

.PHONY : CMakeFiles/Wet1.dir/build

CMakeFiles/Wet1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Wet1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Wet1.dir/clean

CMakeFiles/Wet1.dir/depend:
	cd /Users/guy_steinberg/Documents/DataStructures/Wet1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/guy_steinberg/Documents/DataStructures/Wet1 /Users/guy_steinberg/Documents/DataStructures/Wet1 /Users/guy_steinberg/Documents/DataStructures/Wet1/cmake-build-debug /Users/guy_steinberg/Documents/DataStructures/Wet1/cmake-build-debug /Users/guy_steinberg/Documents/DataStructures/Wet1/cmake-build-debug/CMakeFiles/Wet1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Wet1.dir/depend

