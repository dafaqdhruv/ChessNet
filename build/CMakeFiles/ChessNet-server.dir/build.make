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
include CMakeFiles/ChessNet-server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ChessNet-server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ChessNet-server.dir/flags.make

CMakeFiles/ChessNet-server.dir/src/chess_server.cpp.o: CMakeFiles/ChessNet-server.dir/flags.make
CMakeFiles/ChessNet-server.dir/src/chess_server.cpp.o: ../src/chess_server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dfqm8/dev/ChessNet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ChessNet-server.dir/src/chess_server.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ChessNet-server.dir/src/chess_server.cpp.o -c /home/dfqm8/dev/ChessNet/src/chess_server.cpp

CMakeFiles/ChessNet-server.dir/src/chess_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChessNet-server.dir/src/chess_server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dfqm8/dev/ChessNet/src/chess_server.cpp > CMakeFiles/ChessNet-server.dir/src/chess_server.cpp.i

CMakeFiles/ChessNet-server.dir/src/chess_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChessNet-server.dir/src/chess_server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dfqm8/dev/ChessNet/src/chess_server.cpp -o CMakeFiles/ChessNet-server.dir/src/chess_server.cpp.s

# Object files for target ChessNet-server
ChessNet__server_OBJECTS = \
"CMakeFiles/ChessNet-server.dir/src/chess_server.cpp.o"

# External object files for target ChessNet-server
ChessNet__server_EXTERNAL_OBJECTS =

ChessNet-server: CMakeFiles/ChessNet-server.dir/src/chess_server.cpp.o
ChessNet-server: CMakeFiles/ChessNet-server.dir/build.make
ChessNet-server: include/libChessLib.a
ChessNet-server: include/network/libChessNetLib.a
ChessNet-server: CMakeFiles/ChessNet-server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dfqm8/dev/ChessNet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ChessNet-server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ChessNet-server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ChessNet-server.dir/build: ChessNet-server

.PHONY : CMakeFiles/ChessNet-server.dir/build

CMakeFiles/ChessNet-server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ChessNet-server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ChessNet-server.dir/clean

CMakeFiles/ChessNet-server.dir/depend:
	cd /home/dfqm8/dev/ChessNet/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dfqm8/dev/ChessNet /home/dfqm8/dev/ChessNet /home/dfqm8/dev/ChessNet/build /home/dfqm8/dev/ChessNet/build /home/dfqm8/dev/ChessNet/build/CMakeFiles/ChessNet-server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ChessNet-server.dir/depend

