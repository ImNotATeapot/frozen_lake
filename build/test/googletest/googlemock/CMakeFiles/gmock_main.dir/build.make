# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.15.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.15.4/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Pearl/Desktop/frozen_lake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Pearl/Desktop/frozen_lake/build

# Include any dependencies generated for this target.
include test/googletest/googlemock/CMakeFiles/gmock_main.dir/depend.make

# Include the progress variables for this target.
include test/googletest/googlemock/CMakeFiles/gmock_main.dir/progress.make

# Include the compile flags for this target's objects.
include test/googletest/googlemock/CMakeFiles/gmock_main.dir/flags.make

test/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o: test/googletest/googlemock/CMakeFiles/gmock_main.dir/flags.make
test/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o: ../test/googletest/googlemock/src/gmock_main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Pearl/Desktop/frozen_lake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o"
	cd /Users/Pearl/Desktop/frozen_lake/build/test/googletest/googlemock && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gmock_main.dir/src/gmock_main.cc.o -c /Users/Pearl/Desktop/frozen_lake/test/googletest/googlemock/src/gmock_main.cc

test/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gmock_main.dir/src/gmock_main.cc.i"
	cd /Users/Pearl/Desktop/frozen_lake/build/test/googletest/googlemock && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Pearl/Desktop/frozen_lake/test/googletest/googlemock/src/gmock_main.cc > CMakeFiles/gmock_main.dir/src/gmock_main.cc.i

test/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gmock_main.dir/src/gmock_main.cc.s"
	cd /Users/Pearl/Desktop/frozen_lake/build/test/googletest/googlemock && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Pearl/Desktop/frozen_lake/test/googletest/googlemock/src/gmock_main.cc -o CMakeFiles/gmock_main.dir/src/gmock_main.cc.s

# Object files for target gmock_main
gmock_main_OBJECTS = \
"CMakeFiles/gmock_main.dir/src/gmock_main.cc.o"

# External object files for target gmock_main
gmock_main_EXTERNAL_OBJECTS =

lib/libgmock_main.a: test/googletest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o
lib/libgmock_main.a: test/googletest/googlemock/CMakeFiles/gmock_main.dir/build.make
lib/libgmock_main.a: test/googletest/googlemock/CMakeFiles/gmock_main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Pearl/Desktop/frozen_lake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../../lib/libgmock_main.a"
	cd /Users/Pearl/Desktop/frozen_lake/build/test/googletest/googlemock && $(CMAKE_COMMAND) -P CMakeFiles/gmock_main.dir/cmake_clean_target.cmake
	cd /Users/Pearl/Desktop/frozen_lake/build/test/googletest/googlemock && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gmock_main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/googletest/googlemock/CMakeFiles/gmock_main.dir/build: lib/libgmock_main.a

.PHONY : test/googletest/googlemock/CMakeFiles/gmock_main.dir/build

test/googletest/googlemock/CMakeFiles/gmock_main.dir/clean:
	cd /Users/Pearl/Desktop/frozen_lake/build/test/googletest/googlemock && $(CMAKE_COMMAND) -P CMakeFiles/gmock_main.dir/cmake_clean.cmake
.PHONY : test/googletest/googlemock/CMakeFiles/gmock_main.dir/clean

test/googletest/googlemock/CMakeFiles/gmock_main.dir/depend:
	cd /Users/Pearl/Desktop/frozen_lake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Pearl/Desktop/frozen_lake /Users/Pearl/Desktop/frozen_lake/test/googletest/googlemock /Users/Pearl/Desktop/frozen_lake/build /Users/Pearl/Desktop/frozen_lake/build/test/googletest/googlemock /Users/Pearl/Desktop/frozen_lake/build/test/googletest/googlemock/CMakeFiles/gmock_main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/googletest/googlemock/CMakeFiles/gmock_main.dir/depend

