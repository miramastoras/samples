# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/miramastoras/ECS_30/homework3.2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/miramastoras/ECS_30/homework3.2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/homework3_2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/homework3_2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/homework3_2.dir/flags.make

CMakeFiles/homework3_2.dir/main.c.o: CMakeFiles/homework3_2.dir/flags.make
CMakeFiles/homework3_2.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/miramastoras/ECS_30/homework3.2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/homework3_2.dir/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/homework3_2.dir/main.c.o   -c /Users/miramastoras/ECS_30/homework3.2/main.c

CMakeFiles/homework3_2.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/homework3_2.dir/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/miramastoras/ECS_30/homework3.2/main.c > CMakeFiles/homework3_2.dir/main.c.i

CMakeFiles/homework3_2.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/homework3_2.dir/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/miramastoras/ECS_30/homework3.2/main.c -o CMakeFiles/homework3_2.dir/main.c.s

CMakeFiles/homework3_2.dir/main.c.o.requires:

.PHONY : CMakeFiles/homework3_2.dir/main.c.o.requires

CMakeFiles/homework3_2.dir/main.c.o.provides: CMakeFiles/homework3_2.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/homework3_2.dir/build.make CMakeFiles/homework3_2.dir/main.c.o.provides.build
.PHONY : CMakeFiles/homework3_2.dir/main.c.o.provides

CMakeFiles/homework3_2.dir/main.c.o.provides.build: CMakeFiles/homework3_2.dir/main.c.o


# Object files for target homework3_2
homework3_2_OBJECTS = \
"CMakeFiles/homework3_2.dir/main.c.o"

# External object files for target homework3_2
homework3_2_EXTERNAL_OBJECTS =

homework3_2: CMakeFiles/homework3_2.dir/main.c.o
homework3_2: CMakeFiles/homework3_2.dir/build.make
homework3_2: CMakeFiles/homework3_2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/miramastoras/ECS_30/homework3.2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable homework3_2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/homework3_2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/homework3_2.dir/build: homework3_2

.PHONY : CMakeFiles/homework3_2.dir/build

CMakeFiles/homework3_2.dir/requires: CMakeFiles/homework3_2.dir/main.c.o.requires

.PHONY : CMakeFiles/homework3_2.dir/requires

CMakeFiles/homework3_2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/homework3_2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/homework3_2.dir/clean

CMakeFiles/homework3_2.dir/depend:
	cd /Users/miramastoras/ECS_30/homework3.2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/miramastoras/ECS_30/homework3.2 /Users/miramastoras/ECS_30/homework3.2 /Users/miramastoras/ECS_30/homework3.2/cmake-build-debug /Users/miramastoras/ECS_30/homework3.2/cmake-build-debug /Users/miramastoras/ECS_30/homework3.2/cmake-build-debug/CMakeFiles/homework3_2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/homework3_2.dir/depend

