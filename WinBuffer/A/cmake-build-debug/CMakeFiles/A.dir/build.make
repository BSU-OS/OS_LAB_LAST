# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

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

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:\Important catalog\Projects\C++\OS\OS_LAB_LAST\WinBuffer\A"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\Important catalog\Projects\C++\OS\OS_LAB_LAST\WinBuffer\A\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles\A.dir\depend.make
# Include the progress variables for this target.
include CMakeFiles\A.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\A.dir\flags.make

CMakeFiles\A.dir\main.cpp.obj: CMakeFiles\A.dir\flags.make
CMakeFiles\A.dir\main.cpp.obj: ..\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\Important catalog\Projects\C++\OS\OS_LAB_LAST\WinBuffer\A\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/A.dir/main.cpp.obj"
	C:\PROGRA~2\MIB055~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\A.dir\main.cpp.obj /FdCMakeFiles\A.dir\ /FS -c "D:\Important catalog\Projects\C++\OS\OS_LAB_LAST\WinBuffer\A\main.cpp"
<<

CMakeFiles\A.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/A.dir/main.cpp.i"
	C:\PROGRA~2\MIB055~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe > CMakeFiles\A.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\Important catalog\Projects\C++\OS\OS_LAB_LAST\WinBuffer\A\main.cpp"
<<

CMakeFiles\A.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/A.dir/main.cpp.s"
	C:\PROGRA~2\MIB055~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\A.dir\main.cpp.s /c "D:\Important catalog\Projects\C++\OS\OS_LAB_LAST\WinBuffer\A\main.cpp"
<<

# Object files for target A
A_OBJECTS = \
"CMakeFiles\A.dir\main.cpp.obj"

# External object files for target A
A_EXTERNAL_OBJECTS =

A.exe: CMakeFiles\A.dir\main.cpp.obj
A.exe: CMakeFiles\A.dir\build.make
A.exe: CMakeFiles\A.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\Important catalog\Projects\C++\OS\OS_LAB_LAST\WinBuffer\A\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable A.exe"
	"D:\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\A.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x86\mt.exe --manifests -- C:\PROGRA~2\MIB055~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\A.dir\objects1.rsp @<<
 /out:A.exe /implib:A.lib /pdb:"D:\Important catalog\Projects\C++\OS\OS_LAB_LAST\WinBuffer\A\cmake-build-debug\A.pdb" /version:0.0 /machine:X86 /debug /INCREMENTAL /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\A.dir\build: A.exe
.PHONY : CMakeFiles\A.dir\build

CMakeFiles\A.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\A.dir\cmake_clean.cmake
.PHONY : CMakeFiles\A.dir\clean

CMakeFiles\A.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" "D:\Important catalog\Projects\C++\OS\OS_LAB_LAST\WinBuffer\A" "D:\Important catalog\Projects\C++\OS\OS_LAB_LAST\WinBuffer\A" "D:\Important catalog\Projects\C++\OS\OS_LAB_LAST\WinBuffer\A\cmake-build-debug" "D:\Important catalog\Projects\C++\OS\OS_LAB_LAST\WinBuffer\A\cmake-build-debug" "D:\Important catalog\Projects\C++\OS\OS_LAB_LAST\WinBuffer\A\cmake-build-debug\CMakeFiles\A.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles\A.dir\depend

