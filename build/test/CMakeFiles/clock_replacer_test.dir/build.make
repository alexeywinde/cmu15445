# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yangwende/cmu15445

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yangwende/cmu15445/build

# Include any dependencies generated for this target.
include test/CMakeFiles/clock_replacer_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/clock_replacer_test.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/clock_replacer_test.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/clock_replacer_test.dir/flags.make

test/CMakeFiles/clock_replacer_test.dir/buffer/clock_replacer_test.cpp.o: test/CMakeFiles/clock_replacer_test.dir/flags.make
test/CMakeFiles/clock_replacer_test.dir/buffer/clock_replacer_test.cpp.o: ../test/buffer/clock_replacer_test.cpp
test/CMakeFiles/clock_replacer_test.dir/buffer/clock_replacer_test.cpp.o: test/CMakeFiles/clock_replacer_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yangwende/cmu15445/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/clock_replacer_test.dir/buffer/clock_replacer_test.cpp.o"
	cd /home/yangwende/cmu15445/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/clock_replacer_test.dir/buffer/clock_replacer_test.cpp.o -MF CMakeFiles/clock_replacer_test.dir/buffer/clock_replacer_test.cpp.o.d -o CMakeFiles/clock_replacer_test.dir/buffer/clock_replacer_test.cpp.o -c /home/yangwende/cmu15445/test/buffer/clock_replacer_test.cpp

test/CMakeFiles/clock_replacer_test.dir/buffer/clock_replacer_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clock_replacer_test.dir/buffer/clock_replacer_test.cpp.i"
	cd /home/yangwende/cmu15445/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yangwende/cmu15445/test/buffer/clock_replacer_test.cpp > CMakeFiles/clock_replacer_test.dir/buffer/clock_replacer_test.cpp.i

test/CMakeFiles/clock_replacer_test.dir/buffer/clock_replacer_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clock_replacer_test.dir/buffer/clock_replacer_test.cpp.s"
	cd /home/yangwende/cmu15445/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yangwende/cmu15445/test/buffer/clock_replacer_test.cpp -o CMakeFiles/clock_replacer_test.dir/buffer/clock_replacer_test.cpp.s

# Object files for target clock_replacer_test
clock_replacer_test_OBJECTS = \
"CMakeFiles/clock_replacer_test.dir/buffer/clock_replacer_test.cpp.o"

# External object files for target clock_replacer_test
clock_replacer_test_EXTERNAL_OBJECTS =

test/clock_replacer_test: test/CMakeFiles/clock_replacer_test.dir/buffer/clock_replacer_test.cpp.o
test/clock_replacer_test: test/CMakeFiles/clock_replacer_test.dir/build.make
test/clock_replacer_test: lib/libbustub.a
test/clock_replacer_test: lib/libgtest.a
test/clock_replacer_test: lib/libgmock_main.a
test/clock_replacer_test: lib/libbustub_murmur3.a
test/clock_replacer_test: lib/libduckdb_pg_query.a
test/clock_replacer_test: lib/libfmtd.a
test/clock_replacer_test: lib/libfort.a
test/clock_replacer_test: lib/libgmock.a
test/clock_replacer_test: lib/libgtest.a
test/clock_replacer_test: test/CMakeFiles/clock_replacer_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yangwende/cmu15445/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable clock_replacer_test"
	cd /home/yangwende/cmu15445/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/clock_replacer_test.dir/link.txt --verbose=$(VERBOSE)
	cd /home/yangwende/cmu15445/build/test && /usr/bin/cmake -D TEST_TARGET=clock_replacer_test -D TEST_EXECUTABLE=/home/yangwende/cmu15445/build/test/clock_replacer_test -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/home/yangwende/cmu15445/build/test -D "TEST_EXTRA_ARGS=--gtest_color=auto;--gtest_output=xml:/home/yangwende/cmu15445/build/test/clock_replacer_test.xml;--gtest_catch_exceptions=0" -D "TEST_PROPERTIES=TIMEOUT;120" -D TEST_PREFIX= -D TEST_SUFFIX= -D TEST_FILTER= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=clock_replacer_test_TESTS -D CTEST_FILE=/home/yangwende/cmu15445/build/test/clock_replacer_test[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=120 -D TEST_XML_OUTPUT_DIR= -P /usr/share/cmake-3.22/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
test/CMakeFiles/clock_replacer_test.dir/build: test/clock_replacer_test
.PHONY : test/CMakeFiles/clock_replacer_test.dir/build

test/CMakeFiles/clock_replacer_test.dir/clean:
	cd /home/yangwende/cmu15445/build/test && $(CMAKE_COMMAND) -P CMakeFiles/clock_replacer_test.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/clock_replacer_test.dir/clean

test/CMakeFiles/clock_replacer_test.dir/depend:
	cd /home/yangwende/cmu15445/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yangwende/cmu15445 /home/yangwende/cmu15445/test /home/yangwende/cmu15445/build /home/yangwende/cmu15445/build/test /home/yangwende/cmu15445/build/test/CMakeFiles/clock_replacer_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/clock_replacer_test.dir/depend

