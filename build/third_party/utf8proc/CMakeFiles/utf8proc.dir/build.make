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
include third_party/utf8proc/CMakeFiles/utf8proc.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include third_party/utf8proc/CMakeFiles/utf8proc.dir/compiler_depend.make

# Include the progress variables for this target.
include third_party/utf8proc/CMakeFiles/utf8proc.dir/progress.make

# Include the compile flags for this target's objects.
include third_party/utf8proc/CMakeFiles/utf8proc.dir/flags.make

third_party/utf8proc/CMakeFiles/utf8proc.dir/utf8proc.c.o: third_party/utf8proc/CMakeFiles/utf8proc.dir/flags.make
third_party/utf8proc/CMakeFiles/utf8proc.dir/utf8proc.c.o: ../third_party/utf8proc/utf8proc.c
third_party/utf8proc/CMakeFiles/utf8proc.dir/utf8proc.c.o: third_party/utf8proc/CMakeFiles/utf8proc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yangwende/cmu15445/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object third_party/utf8proc/CMakeFiles/utf8proc.dir/utf8proc.c.o"
	cd /home/yangwende/cmu15445/build/third_party/utf8proc && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT third_party/utf8proc/CMakeFiles/utf8proc.dir/utf8proc.c.o -MF CMakeFiles/utf8proc.dir/utf8proc.c.o.d -o CMakeFiles/utf8proc.dir/utf8proc.c.o -c /home/yangwende/cmu15445/third_party/utf8proc/utf8proc.c

third_party/utf8proc/CMakeFiles/utf8proc.dir/utf8proc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/utf8proc.dir/utf8proc.c.i"
	cd /home/yangwende/cmu15445/build/third_party/utf8proc && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/yangwende/cmu15445/third_party/utf8proc/utf8proc.c > CMakeFiles/utf8proc.dir/utf8proc.c.i

third_party/utf8proc/CMakeFiles/utf8proc.dir/utf8proc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/utf8proc.dir/utf8proc.c.s"
	cd /home/yangwende/cmu15445/build/third_party/utf8proc && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/yangwende/cmu15445/third_party/utf8proc/utf8proc.c -o CMakeFiles/utf8proc.dir/utf8proc.c.s

# Object files for target utf8proc
utf8proc_OBJECTS = \
"CMakeFiles/utf8proc.dir/utf8proc.c.o"

# External object files for target utf8proc
utf8proc_EXTERNAL_OBJECTS =

lib/libutf8proc.a: third_party/utf8proc/CMakeFiles/utf8proc.dir/utf8proc.c.o
lib/libutf8proc.a: third_party/utf8proc/CMakeFiles/utf8proc.dir/build.make
lib/libutf8proc.a: third_party/utf8proc/CMakeFiles/utf8proc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yangwende/cmu15445/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library ../../lib/libutf8proc.a"
	cd /home/yangwende/cmu15445/build/third_party/utf8proc && $(CMAKE_COMMAND) -P CMakeFiles/utf8proc.dir/cmake_clean_target.cmake
	cd /home/yangwende/cmu15445/build/third_party/utf8proc && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/utf8proc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
third_party/utf8proc/CMakeFiles/utf8proc.dir/build: lib/libutf8proc.a
.PHONY : third_party/utf8proc/CMakeFiles/utf8proc.dir/build

third_party/utf8proc/CMakeFiles/utf8proc.dir/clean:
	cd /home/yangwende/cmu15445/build/third_party/utf8proc && $(CMAKE_COMMAND) -P CMakeFiles/utf8proc.dir/cmake_clean.cmake
.PHONY : third_party/utf8proc/CMakeFiles/utf8proc.dir/clean

third_party/utf8proc/CMakeFiles/utf8proc.dir/depend:
	cd /home/yangwende/cmu15445/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yangwende/cmu15445 /home/yangwende/cmu15445/third_party/utf8proc /home/yangwende/cmu15445/build /home/yangwende/cmu15445/build/third_party/utf8proc /home/yangwende/cmu15445/build/third_party/utf8proc/CMakeFiles/utf8proc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : third_party/utf8proc/CMakeFiles/utf8proc.dir/depend

