# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/snooze/projects/ANN

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/snooze/projects/ANN/build

# Include any dependencies generated for this target.
include CMakeFiles/ann.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ann.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ann.dir/flags.make

CMakeFiles/ann.dir/main.cpp.o: CMakeFiles/ann.dir/flags.make
CMakeFiles/ann.dir/main.cpp.o: ../main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/snooze/projects/ANN/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ann.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ann.dir/main.cpp.o -c /home/snooze/projects/ANN/main.cpp

CMakeFiles/ann.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ann.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/snooze/projects/ANN/main.cpp > CMakeFiles/ann.dir/main.cpp.i

CMakeFiles/ann.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ann.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/snooze/projects/ANN/main.cpp -o CMakeFiles/ann.dir/main.cpp.s

CMakeFiles/ann.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/ann.dir/main.cpp.o.requires

CMakeFiles/ann.dir/main.cpp.o.provides: CMakeFiles/ann.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/ann.dir/build.make CMakeFiles/ann.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/ann.dir/main.cpp.o.provides

CMakeFiles/ann.dir/main.cpp.o.provides.build: CMakeFiles/ann.dir/main.cpp.o

# Object files for target ann
ann_OBJECTS = \
"CMakeFiles/ann.dir/main.cpp.o"

# External object files for target ann
ann_EXTERNAL_OBJECTS =

ann: CMakeFiles/ann.dir/main.cpp.o
ann: CMakeFiles/ann.dir/build.make
ann: CMakeFiles/ann.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ann"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ann.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ann.dir/build: ann
.PHONY : CMakeFiles/ann.dir/build

CMakeFiles/ann.dir/requires: CMakeFiles/ann.dir/main.cpp.o.requires
.PHONY : CMakeFiles/ann.dir/requires

CMakeFiles/ann.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ann.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ann.dir/clean

CMakeFiles/ann.dir/depend:
	cd /home/snooze/projects/ANN/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/snooze/projects/ANN /home/snooze/projects/ANN /home/snooze/projects/ANN/build /home/snooze/projects/ANN/build /home/snooze/projects/ANN/build/CMakeFiles/ann.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ann.dir/depend

