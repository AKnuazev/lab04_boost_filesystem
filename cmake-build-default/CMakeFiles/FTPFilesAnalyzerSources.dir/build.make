# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /opt/clion-2019.2.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2019.2.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/anton/AKnuazev/labs/lab04_boost_filesystem

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anton/AKnuazev/labs/lab04_boost_filesystem/cmake-build-default

# Include any dependencies generated for this target.
include CMakeFiles/FTPFilesAnalyzerSources.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/FTPFilesAnalyzerSources.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FTPFilesAnalyzerSources.dir/flags.make

CMakeFiles/FTPFilesAnalyzerSources.dir/sources/FTPFilesAnalyzer.cpp.o: CMakeFiles/FTPFilesAnalyzerSources.dir/flags.make
CMakeFiles/FTPFilesAnalyzerSources.dir/sources/FTPFilesAnalyzer.cpp.o: ../sources/FTPFilesAnalyzer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anton/AKnuazev/labs/lab04_boost_filesystem/cmake-build-default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/FTPFilesAnalyzerSources.dir/sources/FTPFilesAnalyzer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FTPFilesAnalyzerSources.dir/sources/FTPFilesAnalyzer.cpp.o -c /home/anton/AKnuazev/labs/lab04_boost_filesystem/sources/FTPFilesAnalyzer.cpp

CMakeFiles/FTPFilesAnalyzerSources.dir/sources/FTPFilesAnalyzer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FTPFilesAnalyzerSources.dir/sources/FTPFilesAnalyzer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anton/AKnuazev/labs/lab04_boost_filesystem/sources/FTPFilesAnalyzer.cpp > CMakeFiles/FTPFilesAnalyzerSources.dir/sources/FTPFilesAnalyzer.cpp.i

CMakeFiles/FTPFilesAnalyzerSources.dir/sources/FTPFilesAnalyzer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FTPFilesAnalyzerSources.dir/sources/FTPFilesAnalyzer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anton/AKnuazev/labs/lab04_boost_filesystem/sources/FTPFilesAnalyzer.cpp -o CMakeFiles/FTPFilesAnalyzerSources.dir/sources/FTPFilesAnalyzer.cpp.s

# Object files for target FTPFilesAnalyzerSources
FTPFilesAnalyzerSources_OBJECTS = \
"CMakeFiles/FTPFilesAnalyzerSources.dir/sources/FTPFilesAnalyzer.cpp.o"

# External object files for target FTPFilesAnalyzerSources
FTPFilesAnalyzerSources_EXTERNAL_OBJECTS =

libFTPFilesAnalyzerSources.a: CMakeFiles/FTPFilesAnalyzerSources.dir/sources/FTPFilesAnalyzer.cpp.o
libFTPFilesAnalyzerSources.a: CMakeFiles/FTPFilesAnalyzerSources.dir/build.make
libFTPFilesAnalyzerSources.a: CMakeFiles/FTPFilesAnalyzerSources.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anton/AKnuazev/labs/lab04_boost_filesystem/cmake-build-default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libFTPFilesAnalyzerSources.a"
	$(CMAKE_COMMAND) -P CMakeFiles/FTPFilesAnalyzerSources.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FTPFilesAnalyzerSources.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/FTPFilesAnalyzerSources.dir/build: libFTPFilesAnalyzerSources.a

.PHONY : CMakeFiles/FTPFilesAnalyzerSources.dir/build

CMakeFiles/FTPFilesAnalyzerSources.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/FTPFilesAnalyzerSources.dir/cmake_clean.cmake
.PHONY : CMakeFiles/FTPFilesAnalyzerSources.dir/clean

CMakeFiles/FTPFilesAnalyzerSources.dir/depend:
	cd /home/anton/AKnuazev/labs/lab04_boost_filesystem/cmake-build-default && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anton/AKnuazev/labs/lab04_boost_filesystem /home/anton/AKnuazev/labs/lab04_boost_filesystem /home/anton/AKnuazev/labs/lab04_boost_filesystem/cmake-build-default /home/anton/AKnuazev/labs/lab04_boost_filesystem/cmake-build-default /home/anton/AKnuazev/labs/lab04_boost_filesystem/cmake-build-default/CMakeFiles/FTPFilesAnalyzerSources.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/FTPFilesAnalyzerSources.dir/depend

