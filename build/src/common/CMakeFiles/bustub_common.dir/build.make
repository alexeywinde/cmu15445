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
CMAKE_SOURCE_DIR = /home/yangwende/cmu15445/cmu15445

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yangwende/cmu15445/cmu15445/build

# Include any dependencies generated for this target.
include src/common/CMakeFiles/bustub_common.dir/depend.make

# Include the progress variables for this target.
include src/common/CMakeFiles/bustub_common.dir/progress.make

# Include the compile flags for this target's objects.
include src/common/CMakeFiles/bustub_common.dir/flags.make

src/common/CMakeFiles/bustub_common.dir/bustub_instance.cpp.o: src/common/CMakeFiles/bustub_common.dir/flags.make
src/common/CMakeFiles/bustub_common.dir/bustub_instance.cpp.o: ../src/common/bustub_instance.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yangwende/cmu15445/cmu15445/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/common/CMakeFiles/bustub_common.dir/bustub_instance.cpp.o"
	cd /home/yangwende/cmu15445/cmu15445/build/src/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bustub_common.dir/bustub_instance.cpp.o -c /home/yangwende/cmu15445/cmu15445/src/common/bustub_instance.cpp

src/common/CMakeFiles/bustub_common.dir/bustub_instance.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bustub_common.dir/bustub_instance.cpp.i"
	cd /home/yangwende/cmu15445/cmu15445/build/src/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yangwende/cmu15445/cmu15445/src/common/bustub_instance.cpp > CMakeFiles/bustub_common.dir/bustub_instance.cpp.i

src/common/CMakeFiles/bustub_common.dir/bustub_instance.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bustub_common.dir/bustub_instance.cpp.s"
	cd /home/yangwende/cmu15445/cmu15445/build/src/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yangwende/cmu15445/cmu15445/src/common/bustub_instance.cpp -o CMakeFiles/bustub_common.dir/bustub_instance.cpp.s

src/common/CMakeFiles/bustub_common.dir/config.cpp.o: src/common/CMakeFiles/bustub_common.dir/flags.make
src/common/CMakeFiles/bustub_common.dir/config.cpp.o: ../src/common/config.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yangwende/cmu15445/cmu15445/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/common/CMakeFiles/bustub_common.dir/config.cpp.o"
	cd /home/yangwende/cmu15445/cmu15445/build/src/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bustub_common.dir/config.cpp.o -c /home/yangwende/cmu15445/cmu15445/src/common/config.cpp

src/common/CMakeFiles/bustub_common.dir/config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bustub_common.dir/config.cpp.i"
	cd /home/yangwende/cmu15445/cmu15445/build/src/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yangwende/cmu15445/cmu15445/src/common/config.cpp > CMakeFiles/bustub_common.dir/config.cpp.i

src/common/CMakeFiles/bustub_common.dir/config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bustub_common.dir/config.cpp.s"
	cd /home/yangwende/cmu15445/cmu15445/build/src/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yangwende/cmu15445/cmu15445/src/common/config.cpp -o CMakeFiles/bustub_common.dir/config.cpp.s

src/common/CMakeFiles/bustub_common.dir/util/string_util.cpp.o: src/common/CMakeFiles/bustub_common.dir/flags.make
src/common/CMakeFiles/bustub_common.dir/util/string_util.cpp.o: ../src/common/util/string_util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yangwende/cmu15445/cmu15445/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/common/CMakeFiles/bustub_common.dir/util/string_util.cpp.o"
	cd /home/yangwende/cmu15445/cmu15445/build/src/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bustub_common.dir/util/string_util.cpp.o -c /home/yangwende/cmu15445/cmu15445/src/common/util/string_util.cpp

src/common/CMakeFiles/bustub_common.dir/util/string_util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bustub_common.dir/util/string_util.cpp.i"
	cd /home/yangwende/cmu15445/cmu15445/build/src/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yangwende/cmu15445/cmu15445/src/common/util/string_util.cpp > CMakeFiles/bustub_common.dir/util/string_util.cpp.i

src/common/CMakeFiles/bustub_common.dir/util/string_util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bustub_common.dir/util/string_util.cpp.s"
	cd /home/yangwende/cmu15445/cmu15445/build/src/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yangwende/cmu15445/cmu15445/src/common/util/string_util.cpp -o CMakeFiles/bustub_common.dir/util/string_util.cpp.s

bustub_common: src/common/CMakeFiles/bustub_common.dir/bustub_instance.cpp.o
bustub_common: src/common/CMakeFiles/bustub_common.dir/config.cpp.o
bustub_common: src/common/CMakeFiles/bustub_common.dir/util/string_util.cpp.o
bustub_common: src/common/CMakeFiles/bustub_common.dir/build.make

.PHONY : bustub_common

# Rule to build all files generated by this target.
src/common/CMakeFiles/bustub_common.dir/build: bustub_common

.PHONY : src/common/CMakeFiles/bustub_common.dir/build

src/common/CMakeFiles/bustub_common.dir/clean:
	cd /home/yangwende/cmu15445/cmu15445/build/src/common && $(CMAKE_COMMAND) -P CMakeFiles/bustub_common.dir/cmake_clean.cmake
.PHONY : src/common/CMakeFiles/bustub_common.dir/clean

src/common/CMakeFiles/bustub_common.dir/depend:
	cd /home/yangwende/cmu15445/cmu15445/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yangwende/cmu15445/cmu15445 /home/yangwende/cmu15445/cmu15445/src/common /home/yangwende/cmu15445/cmu15445/build /home/yangwende/cmu15445/cmu15445/build/src/common /home/yangwende/cmu15445/cmu15445/build/src/common/CMakeFiles/bustub_common.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/common/CMakeFiles/bustub_common.dir/depend

