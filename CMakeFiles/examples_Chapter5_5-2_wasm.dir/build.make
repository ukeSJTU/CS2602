# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/runner/work/CS2602/CS2602

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/runner/work/CS2602/CS2602/build

# Include any dependencies generated for this target.
include CMakeFiles/examples_Chapter5_5-2_wasm.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/examples_Chapter5_5-2_wasm.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/examples_Chapter5_5-2_wasm.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/examples_Chapter5_5-2_wasm.dir/flags.make

CMakeFiles/examples_Chapter5_5-2_wasm.dir/codegen:
.PHONY : CMakeFiles/examples_Chapter5_5-2_wasm.dir/codegen

CMakeFiles/examples_Chapter5_5-2_wasm.dir/src/examples/Chapter5/5-2/main.cpp.o: CMakeFiles/examples_Chapter5_5-2_wasm.dir/flags.make
CMakeFiles/examples_Chapter5_5-2_wasm.dir/src/examples/Chapter5/5-2/main.cpp.o: CMakeFiles/examples_Chapter5_5-2_wasm.dir/includes_CXX.rsp
CMakeFiles/examples_Chapter5_5-2_wasm.dir/src/examples/Chapter5/5-2/main.cpp.o: /home/runner/work/CS2602/CS2602/src/examples/Chapter5/5-2/main.cpp
CMakeFiles/examples_Chapter5_5-2_wasm.dir/src/examples/Chapter5/5-2/main.cpp.o: CMakeFiles/examples_Chapter5_5-2_wasm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/runner/work/CS2602/CS2602/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/examples_Chapter5_5-2_wasm.dir/src/examples/Chapter5/5-2/main.cpp.o"
	/home/runner/work/CS2602/CS2602/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/examples_Chapter5_5-2_wasm.dir/src/examples/Chapter5/5-2/main.cpp.o -MF CMakeFiles/examples_Chapter5_5-2_wasm.dir/src/examples/Chapter5/5-2/main.cpp.o.d -o CMakeFiles/examples_Chapter5_5-2_wasm.dir/src/examples/Chapter5/5-2/main.cpp.o -c /home/runner/work/CS2602/CS2602/src/examples/Chapter5/5-2/main.cpp

CMakeFiles/examples_Chapter5_5-2_wasm.dir/src/examples/Chapter5/5-2/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/examples_Chapter5_5-2_wasm.dir/src/examples/Chapter5/5-2/main.cpp.i"
	/home/runner/work/CS2602/CS2602/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/runner/work/CS2602/CS2602/src/examples/Chapter5/5-2/main.cpp > CMakeFiles/examples_Chapter5_5-2_wasm.dir/src/examples/Chapter5/5-2/main.cpp.i

CMakeFiles/examples_Chapter5_5-2_wasm.dir/src/examples/Chapter5/5-2/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/examples_Chapter5_5-2_wasm.dir/src/examples/Chapter5/5-2/main.cpp.s"
	/home/runner/work/CS2602/CS2602/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/runner/work/CS2602/CS2602/src/examples/Chapter5/5-2/main.cpp -o CMakeFiles/examples_Chapter5_5-2_wasm.dir/src/examples/Chapter5/5-2/main.cpp.s

# Object files for target examples_Chapter5_5-2_wasm
examples_Chapter5_5__2_wasm_OBJECTS = \
"CMakeFiles/examples_Chapter5_5-2_wasm.dir/src/examples/Chapter5/5-2/main.cpp.o"

# External object files for target examples_Chapter5_5-2_wasm
examples_Chapter5_5__2_wasm_EXTERNAL_OBJECTS =

examples_Chapter5_5-2_wasm.html: CMakeFiles/examples_Chapter5_5-2_wasm.dir/src/examples/Chapter5/5-2/main.cpp.o
examples_Chapter5_5-2_wasm.html: CMakeFiles/examples_Chapter5_5-2_wasm.dir/build.make
examples_Chapter5_5-2_wasm.html: CMakeFiles/examples_Chapter5_5-2_wasm.dir/objects1.rsp
examples_Chapter5_5-2_wasm.html: CMakeFiles/examples_Chapter5_5-2_wasm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/runner/work/CS2602/CS2602/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable examples_Chapter5_5-2_wasm.html"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/examples_Chapter5_5-2_wasm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/examples_Chapter5_5-2_wasm.dir/build: examples_Chapter5_5-2_wasm.html
.PHONY : CMakeFiles/examples_Chapter5_5-2_wasm.dir/build

CMakeFiles/examples_Chapter5_5-2_wasm.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/examples_Chapter5_5-2_wasm.dir/cmake_clean.cmake
.PHONY : CMakeFiles/examples_Chapter5_5-2_wasm.dir/clean

CMakeFiles/examples_Chapter5_5-2_wasm.dir/depend:
	cd /home/runner/work/CS2602/CS2602/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/runner/work/CS2602/CS2602 /home/runner/work/CS2602/CS2602 /home/runner/work/CS2602/CS2602/build /home/runner/work/CS2602/CS2602/build /home/runner/work/CS2602/CS2602/build/CMakeFiles/examples_Chapter5_5-2_wasm.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/examples_Chapter5_5-2_wasm.dir/depend

