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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dfqm8/dev/ChessNet

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dfqm8/dev/ChessNet/build

# Include any dependencies generated for this target.
include include/CMakeFiles/ChessLib.dir/depend.make

# Include the progress variables for this target.
include include/CMakeFiles/ChessLib.dir/progress.make

# Include the compile flags for this target's objects.
include include/CMakeFiles/ChessLib.dir/flags.make

include/CMakeFiles/ChessLib.dir/bundle.cpp.o: include/CMakeFiles/ChessLib.dir/flags.make
include/CMakeFiles/ChessLib.dir/bundle.cpp.o: ../include/bundle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dfqm8/dev/ChessNet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object include/CMakeFiles/ChessLib.dir/bundle.cpp.o"
	cd /home/dfqm8/dev/ChessNet/build/include && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ChessLib.dir/bundle.cpp.o -c /home/dfqm8/dev/ChessNet/include/bundle.cpp

include/CMakeFiles/ChessLib.dir/bundle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChessLib.dir/bundle.cpp.i"
	cd /home/dfqm8/dev/ChessNet/build/include && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dfqm8/dev/ChessNet/include/bundle.cpp > CMakeFiles/ChessLib.dir/bundle.cpp.i

include/CMakeFiles/ChessLib.dir/bundle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChessLib.dir/bundle.cpp.s"
	cd /home/dfqm8/dev/ChessNet/build/include && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dfqm8/dev/ChessNet/include/bundle.cpp -o CMakeFiles/ChessLib.dir/bundle.cpp.s

# Object files for target ChessLib
ChessLib_OBJECTS = \
"CMakeFiles/ChessLib.dir/bundle.cpp.o"

# External object files for target ChessLib
ChessLib_EXTERNAL_OBJECTS =

include/libChessLib.a: include/CMakeFiles/ChessLib.dir/bundle.cpp.o
include/libChessLib.a: include/CMakeFiles/ChessLib.dir/build.make
include/libChessLib.a: include/CMakeFiles/ChessLib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dfqm8/dev/ChessNet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libChessLib.a"
	cd /home/dfqm8/dev/ChessNet/build/include && $(CMAKE_COMMAND) -P CMakeFiles/ChessLib.dir/cmake_clean_target.cmake
	cd /home/dfqm8/dev/ChessNet/build/include && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ChessLib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
include/CMakeFiles/ChessLib.dir/build: include/libChessLib.a

.PHONY : include/CMakeFiles/ChessLib.dir/build

include/CMakeFiles/ChessLib.dir/clean:
	cd /home/dfqm8/dev/ChessNet/build/include && $(CMAKE_COMMAND) -P CMakeFiles/ChessLib.dir/cmake_clean.cmake
.PHONY : include/CMakeFiles/ChessLib.dir/clean

include/CMakeFiles/ChessLib.dir/depend:
	cd /home/dfqm8/dev/ChessNet/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dfqm8/dev/ChessNet /home/dfqm8/dev/ChessNet/include /home/dfqm8/dev/ChessNet/build /home/dfqm8/dev/ChessNet/build/include /home/dfqm8/dev/ChessNet/build/include/CMakeFiles/ChessLib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : include/CMakeFiles/ChessLib.dir/depend
