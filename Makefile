# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_COMMAND = /home/linuxbrew/.linuxbrew/Cellar/cmake/3.22.2/bin/cmake

# The command to remove a file.
RM = /home/linuxbrew/.linuxbrew/Cellar/cmake/3.22.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /workspace/ft_containers

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspace/ft_containers

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/home/linuxbrew/.linuxbrew/Cellar/cmake/3.22.2/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/home/linuxbrew/.linuxbrew/Cellar/cmake/3.22.2/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /workspace/ft_containers/CMakeFiles /workspace/ft_containers//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /workspace/ft_containers/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named ft_containers

# Build rule for target.
ft_containers: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 ft_containers
.PHONY : ft_containers

# fast build rule for target.
ft_containers/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ft_containers.dir/build.make CMakeFiles/ft_containers.dir/build
.PHONY : ft_containers/fast

test/main.o: test/main.cpp.o
.PHONY : test/main.o

# target to build an object file
test/main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ft_containers.dir/build.make CMakeFiles/ft_containers.dir/test/main.cpp.o
.PHONY : test/main.cpp.o

test/main.i: test/main.cpp.i
.PHONY : test/main.i

# target to preprocess a source file
test/main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ft_containers.dir/build.make CMakeFiles/ft_containers.dir/test/main.cpp.i
.PHONY : test/main.cpp.i

test/main.s: test/main.cpp.s
.PHONY : test/main.s

# target to generate assembly for a file
test/main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ft_containers.dir/build.make CMakeFiles/ft_containers.dir/test/main.cpp.s
.PHONY : test/main.cpp.s

test/test_vector.o: test/test_vector.cpp.o
.PHONY : test/test_vector.o

# target to build an object file
test/test_vector.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ft_containers.dir/build.make CMakeFiles/ft_containers.dir/test/test_vector.cpp.o
.PHONY : test/test_vector.cpp.o

test/test_vector.i: test/test_vector.cpp.i
.PHONY : test/test_vector.i

# target to preprocess a source file
test/test_vector.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ft_containers.dir/build.make CMakeFiles/ft_containers.dir/test/test_vector.cpp.i
.PHONY : test/test_vector.cpp.i

test/test_vector.s: test/test_vector.cpp.s
.PHONY : test/test_vector.s

# target to generate assembly for a file
test/test_vector.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ft_containers.dir/build.make CMakeFiles/ft_containers.dir/test/test_vector.cpp.s
.PHONY : test/test_vector.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... ft_containers"
	@echo "... test/main.o"
	@echo "... test/main.i"
	@echo "... test/main.s"
	@echo "... test/test_vector.o"
	@echo "... test/test_vector.i"
	@echo "... test/test_vector.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

