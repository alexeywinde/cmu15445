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

# Utility rule file for check-clang-tidy-p0.

# Include the progress variables for this target.
include CMakeFiles/check-clang-tidy-p0.dir/progress.make

CMakeFiles/check-clang-tidy-p0:
	../build_support/run_clang_tidy.py -clang-tidy-binary CLANG_TIDY_BIN-NOTFOUND -p /home/yangwende/cmu15445/cmu15445/build src/primer/p0_trie.cpp

check-clang-tidy-p0: CMakeFiles/check-clang-tidy-p0
check-clang-tidy-p0: CMakeFiles/check-clang-tidy-p0.dir/build.make

.PHONY : check-clang-tidy-p0

# Rule to build all files generated by this target.
CMakeFiles/check-clang-tidy-p0.dir/build: check-clang-tidy-p0

.PHONY : CMakeFiles/check-clang-tidy-p0.dir/build

CMakeFiles/check-clang-tidy-p0.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/check-clang-tidy-p0.dir/cmake_clean.cmake
.PHONY : CMakeFiles/check-clang-tidy-p0.dir/clean

CMakeFiles/check-clang-tidy-p0.dir/depend:
	cd /home/yangwende/cmu15445/cmu15445/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yangwende/cmu15445/cmu15445 /home/yangwende/cmu15445/cmu15445 /home/yangwende/cmu15445/cmu15445/build /home/yangwende/cmu15445/cmu15445/build /home/yangwende/cmu15445/cmu15445/build/CMakeFiles/check-clang-tidy-p0.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/check-clang-tidy-p0.dir/depend

