# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.29

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Projects\C++\App1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Projects\C++\App1\build

# Include any dependencies generated for this target.
include Libs/CommandLine/CMakeFiles/commandline.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Libs/CommandLine/CMakeFiles/commandline.dir/compiler_depend.make

# Include the progress variables for this target.
include Libs/CommandLine/CMakeFiles/commandline.dir/progress.make

# Include the compile flags for this target's objects.
include Libs/CommandLine/CMakeFiles/commandline.dir/flags.make

Libs/CommandLine/CMakeFiles/commandline.dir/src/windows_impl.cpp.obj: Libs/CommandLine/CMakeFiles/commandline.dir/flags.make
Libs/CommandLine/CMakeFiles/commandline.dir/src/windows_impl.cpp.obj: Libs/CommandLine/CMakeFiles/commandline.dir/includes_CXX.rsp
Libs/CommandLine/CMakeFiles/commandline.dir/src/windows_impl.cpp.obj: D:/Projects/C++/App1/Libs/CommandLine/src/windows_impl.cpp
Libs/CommandLine/CMakeFiles/commandline.dir/src/windows_impl.cpp.obj: Libs/CommandLine/CMakeFiles/commandline.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Projects\C++\App1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Libs/CommandLine/CMakeFiles/commandline.dir/src/windows_impl.cpp.obj"
	cd /d D:\Projects\C++\App1\build\Libs\CommandLine && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Libs/CommandLine/CMakeFiles/commandline.dir/src/windows_impl.cpp.obj -MF CMakeFiles\commandline.dir\src\windows_impl.cpp.obj.d -o CMakeFiles\commandline.dir\src\windows_impl.cpp.obj -c D:\Projects\C++\App1\Libs\CommandLine\src\windows_impl.cpp

Libs/CommandLine/CMakeFiles/commandline.dir/src/windows_impl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/commandline.dir/src/windows_impl.cpp.i"
	cd /d D:\Projects\C++\App1\build\Libs\CommandLine && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Projects\C++\App1\Libs\CommandLine\src\windows_impl.cpp > CMakeFiles\commandline.dir\src\windows_impl.cpp.i

Libs/CommandLine/CMakeFiles/commandline.dir/src/windows_impl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/commandline.dir/src/windows_impl.cpp.s"
	cd /d D:\Projects\C++\App1\build\Libs\CommandLine && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Projects\C++\App1\Libs\CommandLine\src\windows_impl.cpp -o CMakeFiles\commandline.dir\src\windows_impl.cpp.s

Libs/CommandLine/CMakeFiles/commandline.dir/src/linux_impl.cpp.obj: Libs/CommandLine/CMakeFiles/commandline.dir/flags.make
Libs/CommandLine/CMakeFiles/commandline.dir/src/linux_impl.cpp.obj: Libs/CommandLine/CMakeFiles/commandline.dir/includes_CXX.rsp
Libs/CommandLine/CMakeFiles/commandline.dir/src/linux_impl.cpp.obj: D:/Projects/C++/App1/Libs/CommandLine/src/linux_impl.cpp
Libs/CommandLine/CMakeFiles/commandline.dir/src/linux_impl.cpp.obj: Libs/CommandLine/CMakeFiles/commandline.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Projects\C++\App1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object Libs/CommandLine/CMakeFiles/commandline.dir/src/linux_impl.cpp.obj"
	cd /d D:\Projects\C++\App1\build\Libs\CommandLine && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Libs/CommandLine/CMakeFiles/commandline.dir/src/linux_impl.cpp.obj -MF CMakeFiles\commandline.dir\src\linux_impl.cpp.obj.d -o CMakeFiles\commandline.dir\src\linux_impl.cpp.obj -c D:\Projects\C++\App1\Libs\CommandLine\src\linux_impl.cpp

Libs/CommandLine/CMakeFiles/commandline.dir/src/linux_impl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/commandline.dir/src/linux_impl.cpp.i"
	cd /d D:\Projects\C++\App1\build\Libs\CommandLine && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Projects\C++\App1\Libs\CommandLine\src\linux_impl.cpp > CMakeFiles\commandline.dir\src\linux_impl.cpp.i

Libs/CommandLine/CMakeFiles/commandline.dir/src/linux_impl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/commandline.dir/src/linux_impl.cpp.s"
	cd /d D:\Projects\C++\App1\build\Libs\CommandLine && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Projects\C++\App1\Libs\CommandLine\src\linux_impl.cpp -o CMakeFiles\commandline.dir\src\linux_impl.cpp.s

Libs/CommandLine/CMakeFiles/commandline.dir/src/backends/InteractiveBackend.cpp.obj: Libs/CommandLine/CMakeFiles/commandline.dir/flags.make
Libs/CommandLine/CMakeFiles/commandline.dir/src/backends/InteractiveBackend.cpp.obj: Libs/CommandLine/CMakeFiles/commandline.dir/includes_CXX.rsp
Libs/CommandLine/CMakeFiles/commandline.dir/src/backends/InteractiveBackend.cpp.obj: D:/Projects/C++/App1/Libs/CommandLine/src/backends/InteractiveBackend.cpp
Libs/CommandLine/CMakeFiles/commandline.dir/src/backends/InteractiveBackend.cpp.obj: Libs/CommandLine/CMakeFiles/commandline.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Projects\C++\App1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object Libs/CommandLine/CMakeFiles/commandline.dir/src/backends/InteractiveBackend.cpp.obj"
	cd /d D:\Projects\C++\App1\build\Libs\CommandLine && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Libs/CommandLine/CMakeFiles/commandline.dir/src/backends/InteractiveBackend.cpp.obj -MF CMakeFiles\commandline.dir\src\backends\InteractiveBackend.cpp.obj.d -o CMakeFiles\commandline.dir\src\backends\InteractiveBackend.cpp.obj -c D:\Projects\C++\App1\Libs\CommandLine\src\backends\InteractiveBackend.cpp

Libs/CommandLine/CMakeFiles/commandline.dir/src/backends/InteractiveBackend.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/commandline.dir/src/backends/InteractiveBackend.cpp.i"
	cd /d D:\Projects\C++\App1\build\Libs\CommandLine && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Projects\C++\App1\Libs\CommandLine\src\backends\InteractiveBackend.cpp > CMakeFiles\commandline.dir\src\backends\InteractiveBackend.cpp.i

Libs/CommandLine/CMakeFiles/commandline.dir/src/backends/InteractiveBackend.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/commandline.dir/src/backends/InteractiveBackend.cpp.s"
	cd /d D:\Projects\C++\App1\build\Libs\CommandLine && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Projects\C++\App1\Libs\CommandLine\src\backends\InteractiveBackend.cpp -o CMakeFiles\commandline.dir\src\backends\InteractiveBackend.cpp.s

Libs/CommandLine/CMakeFiles/commandline.dir/src/backends/Backend.cpp.obj: Libs/CommandLine/CMakeFiles/commandline.dir/flags.make
Libs/CommandLine/CMakeFiles/commandline.dir/src/backends/Backend.cpp.obj: Libs/CommandLine/CMakeFiles/commandline.dir/includes_CXX.rsp
Libs/CommandLine/CMakeFiles/commandline.dir/src/backends/Backend.cpp.obj: D:/Projects/C++/App1/Libs/CommandLine/src/backends/Backend.cpp
Libs/CommandLine/CMakeFiles/commandline.dir/src/backends/Backend.cpp.obj: Libs/CommandLine/CMakeFiles/commandline.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Projects\C++\App1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object Libs/CommandLine/CMakeFiles/commandline.dir/src/backends/Backend.cpp.obj"
	cd /d D:\Projects\C++\App1\build\Libs\CommandLine && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Libs/CommandLine/CMakeFiles/commandline.dir/src/backends/Backend.cpp.obj -MF CMakeFiles\commandline.dir\src\backends\Backend.cpp.obj.d -o CMakeFiles\commandline.dir\src\backends\Backend.cpp.obj -c D:\Projects\C++\App1\Libs\CommandLine\src\backends\Backend.cpp

Libs/CommandLine/CMakeFiles/commandline.dir/src/backends/Backend.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/commandline.dir/src/backends/Backend.cpp.i"
	cd /d D:\Projects\C++\App1\build\Libs\CommandLine && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Projects\C++\App1\Libs\CommandLine\src\backends\Backend.cpp > CMakeFiles\commandline.dir\src\backends\Backend.cpp.i

Libs/CommandLine/CMakeFiles/commandline.dir/src/backends/Backend.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/commandline.dir/src/backends/Backend.cpp.s"
	cd /d D:\Projects\C++\App1\build\Libs\CommandLine && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Projects\C++\App1\Libs\CommandLine\src\backends\Backend.cpp -o CMakeFiles\commandline.dir\src\backends\Backend.cpp.s

Libs/CommandLine/CMakeFiles/commandline.dir/src/commandline.cpp.obj: Libs/CommandLine/CMakeFiles/commandline.dir/flags.make
Libs/CommandLine/CMakeFiles/commandline.dir/src/commandline.cpp.obj: Libs/CommandLine/CMakeFiles/commandline.dir/includes_CXX.rsp
Libs/CommandLine/CMakeFiles/commandline.dir/src/commandline.cpp.obj: D:/Projects/C++/App1/Libs/CommandLine/src/commandline.cpp
Libs/CommandLine/CMakeFiles/commandline.dir/src/commandline.cpp.obj: Libs/CommandLine/CMakeFiles/commandline.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Projects\C++\App1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object Libs/CommandLine/CMakeFiles/commandline.dir/src/commandline.cpp.obj"
	cd /d D:\Projects\C++\App1\build\Libs\CommandLine && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Libs/CommandLine/CMakeFiles/commandline.dir/src/commandline.cpp.obj -MF CMakeFiles\commandline.dir\src\commandline.cpp.obj.d -o CMakeFiles\commandline.dir\src\commandline.cpp.obj -c D:\Projects\C++\App1\Libs\CommandLine\src\commandline.cpp

Libs/CommandLine/CMakeFiles/commandline.dir/src/commandline.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/commandline.dir/src/commandline.cpp.i"
	cd /d D:\Projects\C++\App1\build\Libs\CommandLine && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Projects\C++\App1\Libs\CommandLine\src\commandline.cpp > CMakeFiles\commandline.dir\src\commandline.cpp.i

Libs/CommandLine/CMakeFiles/commandline.dir/src/commandline.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/commandline.dir/src/commandline.cpp.s"
	cd /d D:\Projects\C++\App1\build\Libs\CommandLine && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Projects\C++\App1\Libs\CommandLine\src\commandline.cpp -o CMakeFiles\commandline.dir\src\commandline.cpp.s

Libs/CommandLine/CMakeFiles/commandline.dir/src/backends/BufferedBackend.cpp.obj: Libs/CommandLine/CMakeFiles/commandline.dir/flags.make
Libs/CommandLine/CMakeFiles/commandline.dir/src/backends/BufferedBackend.cpp.obj: Libs/CommandLine/CMakeFiles/commandline.dir/includes_CXX.rsp
Libs/CommandLine/CMakeFiles/commandline.dir/src/backends/BufferedBackend.cpp.obj: D:/Projects/C++/App1/Libs/CommandLine/src/backends/BufferedBackend.cpp
Libs/CommandLine/CMakeFiles/commandline.dir/src/backends/BufferedBackend.cpp.obj: Libs/CommandLine/CMakeFiles/commandline.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Projects\C++\App1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object Libs/CommandLine/CMakeFiles/commandline.dir/src/backends/BufferedBackend.cpp.obj"
	cd /d D:\Projects\C++\App1\build\Libs\CommandLine && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Libs/CommandLine/CMakeFiles/commandline.dir/src/backends/BufferedBackend.cpp.obj -MF CMakeFiles\commandline.dir\src\backends\BufferedBackend.cpp.obj.d -o CMakeFiles\commandline.dir\src\backends\BufferedBackend.cpp.obj -c D:\Projects\C++\App1\Libs\CommandLine\src\backends\BufferedBackend.cpp

Libs/CommandLine/CMakeFiles/commandline.dir/src/backends/BufferedBackend.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/commandline.dir/src/backends/BufferedBackend.cpp.i"
	cd /d D:\Projects\C++\App1\build\Libs\CommandLine && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Projects\C++\App1\Libs\CommandLine\src\backends\BufferedBackend.cpp > CMakeFiles\commandline.dir\src\backends\BufferedBackend.cpp.i

Libs/CommandLine/CMakeFiles/commandline.dir/src/backends/BufferedBackend.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/commandline.dir/src/backends/BufferedBackend.cpp.s"
	cd /d D:\Projects\C++\App1\build\Libs\CommandLine && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Projects\C++\App1\Libs\CommandLine\src\backends\BufferedBackend.cpp -o CMakeFiles\commandline.dir\src\backends\BufferedBackend.cpp.s

# Object files for target commandline
commandline_OBJECTS = \
"CMakeFiles/commandline.dir/src/windows_impl.cpp.obj" \
"CMakeFiles/commandline.dir/src/linux_impl.cpp.obj" \
"CMakeFiles/commandline.dir/src/backends/InteractiveBackend.cpp.obj" \
"CMakeFiles/commandline.dir/src/backends/Backend.cpp.obj" \
"CMakeFiles/commandline.dir/src/commandline.cpp.obj" \
"CMakeFiles/commandline.dir/src/backends/BufferedBackend.cpp.obj"

# External object files for target commandline
commandline_EXTERNAL_OBJECTS =

Libs/CommandLine/libcommandline.a: Libs/CommandLine/CMakeFiles/commandline.dir/src/windows_impl.cpp.obj
Libs/CommandLine/libcommandline.a: Libs/CommandLine/CMakeFiles/commandline.dir/src/linux_impl.cpp.obj
Libs/CommandLine/libcommandline.a: Libs/CommandLine/CMakeFiles/commandline.dir/src/backends/InteractiveBackend.cpp.obj
Libs/CommandLine/libcommandline.a: Libs/CommandLine/CMakeFiles/commandline.dir/src/backends/Backend.cpp.obj
Libs/CommandLine/libcommandline.a: Libs/CommandLine/CMakeFiles/commandline.dir/src/commandline.cpp.obj
Libs/CommandLine/libcommandline.a: Libs/CommandLine/CMakeFiles/commandline.dir/src/backends/BufferedBackend.cpp.obj
Libs/CommandLine/libcommandline.a: Libs/CommandLine/CMakeFiles/commandline.dir/build.make
Libs/CommandLine/libcommandline.a: Libs/CommandLine/CMakeFiles/commandline.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\Projects\C++\App1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX static library libcommandline.a"
	cd /d D:\Projects\C++\App1\build\Libs\CommandLine && $(CMAKE_COMMAND) -P CMakeFiles\commandline.dir\cmake_clean_target.cmake
	cd /d D:\Projects\C++\App1\build\Libs\CommandLine && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\commandline.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Libs/CommandLine/CMakeFiles/commandline.dir/build: Libs/CommandLine/libcommandline.a
.PHONY : Libs/CommandLine/CMakeFiles/commandline.dir/build

Libs/CommandLine/CMakeFiles/commandline.dir/clean:
	cd /d D:\Projects\C++\App1\build\Libs\CommandLine && $(CMAKE_COMMAND) -P CMakeFiles\commandline.dir\cmake_clean.cmake
.PHONY : Libs/CommandLine/CMakeFiles/commandline.dir/clean

Libs/CommandLine/CMakeFiles/commandline.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Projects\C++\App1 D:\Projects\C++\App1\Libs\CommandLine D:\Projects\C++\App1\build D:\Projects\C++\App1\build\Libs\CommandLine D:\Projects\C++\App1\build\Libs\CommandLine\CMakeFiles\commandline.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : Libs/CommandLine/CMakeFiles/commandline.dir/depend

