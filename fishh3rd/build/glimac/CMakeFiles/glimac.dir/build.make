# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_SOURCE_DIR = /home/eric/F34/fishh3rd

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/eric/F34/fishh3rd/build

# Include any dependencies generated for this target.
include glimac/CMakeFiles/glimac.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include glimac/CMakeFiles/glimac.dir/compiler_depend.make

# Include the progress variables for this target.
include glimac/CMakeFiles/glimac.dir/progress.make

# Include the compile flags for this target's objects.
include glimac/CMakeFiles/glimac.dir/flags.make

glimac/CMakeFiles/glimac.dir/src/Cone.cpp.o: glimac/CMakeFiles/glimac.dir/flags.make
glimac/CMakeFiles/glimac.dir/src/Cone.cpp.o: /home/eric/F34/fishh3rd/glimac/src/Cone.cpp
glimac/CMakeFiles/glimac.dir/src/Cone.cpp.o: glimac/CMakeFiles/glimac.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eric/F34/fishh3rd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object glimac/CMakeFiles/glimac.dir/src/Cone.cpp.o"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT glimac/CMakeFiles/glimac.dir/src/Cone.cpp.o -MF CMakeFiles/glimac.dir/src/Cone.cpp.o.d -o CMakeFiles/glimac.dir/src/Cone.cpp.o -c /home/eric/F34/fishh3rd/glimac/src/Cone.cpp

glimac/CMakeFiles/glimac.dir/src/Cone.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glimac.dir/src/Cone.cpp.i"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/eric/F34/fishh3rd/glimac/src/Cone.cpp > CMakeFiles/glimac.dir/src/Cone.cpp.i

glimac/CMakeFiles/glimac.dir/src/Cone.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glimac.dir/src/Cone.cpp.s"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/eric/F34/fishh3rd/glimac/src/Cone.cpp -o CMakeFiles/glimac.dir/src/Cone.cpp.s

glimac/CMakeFiles/glimac.dir/src/Geometry.cpp.o: glimac/CMakeFiles/glimac.dir/flags.make
glimac/CMakeFiles/glimac.dir/src/Geometry.cpp.o: /home/eric/F34/fishh3rd/glimac/src/Geometry.cpp
glimac/CMakeFiles/glimac.dir/src/Geometry.cpp.o: glimac/CMakeFiles/glimac.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eric/F34/fishh3rd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object glimac/CMakeFiles/glimac.dir/src/Geometry.cpp.o"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT glimac/CMakeFiles/glimac.dir/src/Geometry.cpp.o -MF CMakeFiles/glimac.dir/src/Geometry.cpp.o.d -o CMakeFiles/glimac.dir/src/Geometry.cpp.o -c /home/eric/F34/fishh3rd/glimac/src/Geometry.cpp

glimac/CMakeFiles/glimac.dir/src/Geometry.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glimac.dir/src/Geometry.cpp.i"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/eric/F34/fishh3rd/glimac/src/Geometry.cpp > CMakeFiles/glimac.dir/src/Geometry.cpp.i

glimac/CMakeFiles/glimac.dir/src/Geometry.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glimac.dir/src/Geometry.cpp.s"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/eric/F34/fishh3rd/glimac/src/Geometry.cpp -o CMakeFiles/glimac.dir/src/Geometry.cpp.s

glimac/CMakeFiles/glimac.dir/src/Image.cpp.o: glimac/CMakeFiles/glimac.dir/flags.make
glimac/CMakeFiles/glimac.dir/src/Image.cpp.o: /home/eric/F34/fishh3rd/glimac/src/Image.cpp
glimac/CMakeFiles/glimac.dir/src/Image.cpp.o: glimac/CMakeFiles/glimac.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eric/F34/fishh3rd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object glimac/CMakeFiles/glimac.dir/src/Image.cpp.o"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT glimac/CMakeFiles/glimac.dir/src/Image.cpp.o -MF CMakeFiles/glimac.dir/src/Image.cpp.o.d -o CMakeFiles/glimac.dir/src/Image.cpp.o -c /home/eric/F34/fishh3rd/glimac/src/Image.cpp

glimac/CMakeFiles/glimac.dir/src/Image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glimac.dir/src/Image.cpp.i"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/eric/F34/fishh3rd/glimac/src/Image.cpp > CMakeFiles/glimac.dir/src/Image.cpp.i

glimac/CMakeFiles/glimac.dir/src/Image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glimac.dir/src/Image.cpp.s"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/eric/F34/fishh3rd/glimac/src/Image.cpp -o CMakeFiles/glimac.dir/src/Image.cpp.s

glimac/CMakeFiles/glimac.dir/src/Program.cpp.o: glimac/CMakeFiles/glimac.dir/flags.make
glimac/CMakeFiles/glimac.dir/src/Program.cpp.o: /home/eric/F34/fishh3rd/glimac/src/Program.cpp
glimac/CMakeFiles/glimac.dir/src/Program.cpp.o: glimac/CMakeFiles/glimac.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eric/F34/fishh3rd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object glimac/CMakeFiles/glimac.dir/src/Program.cpp.o"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT glimac/CMakeFiles/glimac.dir/src/Program.cpp.o -MF CMakeFiles/glimac.dir/src/Program.cpp.o.d -o CMakeFiles/glimac.dir/src/Program.cpp.o -c /home/eric/F34/fishh3rd/glimac/src/Program.cpp

glimac/CMakeFiles/glimac.dir/src/Program.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glimac.dir/src/Program.cpp.i"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/eric/F34/fishh3rd/glimac/src/Program.cpp > CMakeFiles/glimac.dir/src/Program.cpp.i

glimac/CMakeFiles/glimac.dir/src/Program.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glimac.dir/src/Program.cpp.s"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/eric/F34/fishh3rd/glimac/src/Program.cpp -o CMakeFiles/glimac.dir/src/Program.cpp.s

glimac/CMakeFiles/glimac.dir/src/SDLWindowManager.cpp.o: glimac/CMakeFiles/glimac.dir/flags.make
glimac/CMakeFiles/glimac.dir/src/SDLWindowManager.cpp.o: /home/eric/F34/fishh3rd/glimac/src/SDLWindowManager.cpp
glimac/CMakeFiles/glimac.dir/src/SDLWindowManager.cpp.o: glimac/CMakeFiles/glimac.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eric/F34/fishh3rd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object glimac/CMakeFiles/glimac.dir/src/SDLWindowManager.cpp.o"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT glimac/CMakeFiles/glimac.dir/src/SDLWindowManager.cpp.o -MF CMakeFiles/glimac.dir/src/SDLWindowManager.cpp.o.d -o CMakeFiles/glimac.dir/src/SDLWindowManager.cpp.o -c /home/eric/F34/fishh3rd/glimac/src/SDLWindowManager.cpp

glimac/CMakeFiles/glimac.dir/src/SDLWindowManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glimac.dir/src/SDLWindowManager.cpp.i"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/eric/F34/fishh3rd/glimac/src/SDLWindowManager.cpp > CMakeFiles/glimac.dir/src/SDLWindowManager.cpp.i

glimac/CMakeFiles/glimac.dir/src/SDLWindowManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glimac.dir/src/SDLWindowManager.cpp.s"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/eric/F34/fishh3rd/glimac/src/SDLWindowManager.cpp -o CMakeFiles/glimac.dir/src/SDLWindowManager.cpp.s

glimac/CMakeFiles/glimac.dir/src/Shader.cpp.o: glimac/CMakeFiles/glimac.dir/flags.make
glimac/CMakeFiles/glimac.dir/src/Shader.cpp.o: /home/eric/F34/fishh3rd/glimac/src/Shader.cpp
glimac/CMakeFiles/glimac.dir/src/Shader.cpp.o: glimac/CMakeFiles/glimac.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eric/F34/fishh3rd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object glimac/CMakeFiles/glimac.dir/src/Shader.cpp.o"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT glimac/CMakeFiles/glimac.dir/src/Shader.cpp.o -MF CMakeFiles/glimac.dir/src/Shader.cpp.o.d -o CMakeFiles/glimac.dir/src/Shader.cpp.o -c /home/eric/F34/fishh3rd/glimac/src/Shader.cpp

glimac/CMakeFiles/glimac.dir/src/Shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glimac.dir/src/Shader.cpp.i"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/eric/F34/fishh3rd/glimac/src/Shader.cpp > CMakeFiles/glimac.dir/src/Shader.cpp.i

glimac/CMakeFiles/glimac.dir/src/Shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glimac.dir/src/Shader.cpp.s"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/eric/F34/fishh3rd/glimac/src/Shader.cpp -o CMakeFiles/glimac.dir/src/Shader.cpp.s

glimac/CMakeFiles/glimac.dir/src/Sphere.cpp.o: glimac/CMakeFiles/glimac.dir/flags.make
glimac/CMakeFiles/glimac.dir/src/Sphere.cpp.o: /home/eric/F34/fishh3rd/glimac/src/Sphere.cpp
glimac/CMakeFiles/glimac.dir/src/Sphere.cpp.o: glimac/CMakeFiles/glimac.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eric/F34/fishh3rd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object glimac/CMakeFiles/glimac.dir/src/Sphere.cpp.o"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT glimac/CMakeFiles/glimac.dir/src/Sphere.cpp.o -MF CMakeFiles/glimac.dir/src/Sphere.cpp.o.d -o CMakeFiles/glimac.dir/src/Sphere.cpp.o -c /home/eric/F34/fishh3rd/glimac/src/Sphere.cpp

glimac/CMakeFiles/glimac.dir/src/Sphere.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glimac.dir/src/Sphere.cpp.i"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/eric/F34/fishh3rd/glimac/src/Sphere.cpp > CMakeFiles/glimac.dir/src/Sphere.cpp.i

glimac/CMakeFiles/glimac.dir/src/Sphere.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glimac.dir/src/Sphere.cpp.s"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/eric/F34/fishh3rd/glimac/src/Sphere.cpp -o CMakeFiles/glimac.dir/src/Sphere.cpp.s

glimac/CMakeFiles/glimac.dir/src/VAO_VBO.cpp.o: glimac/CMakeFiles/glimac.dir/flags.make
glimac/CMakeFiles/glimac.dir/src/VAO_VBO.cpp.o: /home/eric/F34/fishh3rd/glimac/src/VAO_VBO.cpp
glimac/CMakeFiles/glimac.dir/src/VAO_VBO.cpp.o: glimac/CMakeFiles/glimac.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eric/F34/fishh3rd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object glimac/CMakeFiles/glimac.dir/src/VAO_VBO.cpp.o"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT glimac/CMakeFiles/glimac.dir/src/VAO_VBO.cpp.o -MF CMakeFiles/glimac.dir/src/VAO_VBO.cpp.o.d -o CMakeFiles/glimac.dir/src/VAO_VBO.cpp.o -c /home/eric/F34/fishh3rd/glimac/src/VAO_VBO.cpp

glimac/CMakeFiles/glimac.dir/src/VAO_VBO.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glimac.dir/src/VAO_VBO.cpp.i"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/eric/F34/fishh3rd/glimac/src/VAO_VBO.cpp > CMakeFiles/glimac.dir/src/VAO_VBO.cpp.i

glimac/CMakeFiles/glimac.dir/src/VAO_VBO.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glimac.dir/src/VAO_VBO.cpp.s"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/eric/F34/fishh3rd/glimac/src/VAO_VBO.cpp -o CMakeFiles/glimac.dir/src/VAO_VBO.cpp.s

glimac/CMakeFiles/glimac.dir/src/assets.cpp.o: glimac/CMakeFiles/glimac.dir/flags.make
glimac/CMakeFiles/glimac.dir/src/assets.cpp.o: /home/eric/F34/fishh3rd/glimac/src/assets.cpp
glimac/CMakeFiles/glimac.dir/src/assets.cpp.o: glimac/CMakeFiles/glimac.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eric/F34/fishh3rd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object glimac/CMakeFiles/glimac.dir/src/assets.cpp.o"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT glimac/CMakeFiles/glimac.dir/src/assets.cpp.o -MF CMakeFiles/glimac.dir/src/assets.cpp.o.d -o CMakeFiles/glimac.dir/src/assets.cpp.o -c /home/eric/F34/fishh3rd/glimac/src/assets.cpp

glimac/CMakeFiles/glimac.dir/src/assets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glimac.dir/src/assets.cpp.i"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/eric/F34/fishh3rd/glimac/src/assets.cpp > CMakeFiles/glimac.dir/src/assets.cpp.i

glimac/CMakeFiles/glimac.dir/src/assets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glimac.dir/src/assets.cpp.s"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/eric/F34/fishh3rd/glimac/src/assets.cpp -o CMakeFiles/glimac.dir/src/assets.cpp.s

glimac/CMakeFiles/glimac.dir/src/boids.cpp.o: glimac/CMakeFiles/glimac.dir/flags.make
glimac/CMakeFiles/glimac.dir/src/boids.cpp.o: /home/eric/F34/fishh3rd/glimac/src/boids.cpp
glimac/CMakeFiles/glimac.dir/src/boids.cpp.o: glimac/CMakeFiles/glimac.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eric/F34/fishh3rd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object glimac/CMakeFiles/glimac.dir/src/boids.cpp.o"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT glimac/CMakeFiles/glimac.dir/src/boids.cpp.o -MF CMakeFiles/glimac.dir/src/boids.cpp.o.d -o CMakeFiles/glimac.dir/src/boids.cpp.o -c /home/eric/F34/fishh3rd/glimac/src/boids.cpp

glimac/CMakeFiles/glimac.dir/src/boids.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glimac.dir/src/boids.cpp.i"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/eric/F34/fishh3rd/glimac/src/boids.cpp > CMakeFiles/glimac.dir/src/boids.cpp.i

glimac/CMakeFiles/glimac.dir/src/boids.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glimac.dir/src/boids.cpp.s"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/eric/F34/fishh3rd/glimac/src/boids.cpp -o CMakeFiles/glimac.dir/src/boids.cpp.s

glimac/CMakeFiles/glimac.dir/src/element.cpp.o: glimac/CMakeFiles/glimac.dir/flags.make
glimac/CMakeFiles/glimac.dir/src/element.cpp.o: /home/eric/F34/fishh3rd/glimac/src/element.cpp
glimac/CMakeFiles/glimac.dir/src/element.cpp.o: glimac/CMakeFiles/glimac.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eric/F34/fishh3rd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object glimac/CMakeFiles/glimac.dir/src/element.cpp.o"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT glimac/CMakeFiles/glimac.dir/src/element.cpp.o -MF CMakeFiles/glimac.dir/src/element.cpp.o.d -o CMakeFiles/glimac.dir/src/element.cpp.o -c /home/eric/F34/fishh3rd/glimac/src/element.cpp

glimac/CMakeFiles/glimac.dir/src/element.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glimac.dir/src/element.cpp.i"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/eric/F34/fishh3rd/glimac/src/element.cpp > CMakeFiles/glimac.dir/src/element.cpp.i

glimac/CMakeFiles/glimac.dir/src/element.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glimac.dir/src/element.cpp.s"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/eric/F34/fishh3rd/glimac/src/element.cpp -o CMakeFiles/glimac.dir/src/element.cpp.s

glimac/CMakeFiles/glimac.dir/src/fish.cpp.o: glimac/CMakeFiles/glimac.dir/flags.make
glimac/CMakeFiles/glimac.dir/src/fish.cpp.o: /home/eric/F34/fishh3rd/glimac/src/fish.cpp
glimac/CMakeFiles/glimac.dir/src/fish.cpp.o: glimac/CMakeFiles/glimac.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eric/F34/fishh3rd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object glimac/CMakeFiles/glimac.dir/src/fish.cpp.o"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT glimac/CMakeFiles/glimac.dir/src/fish.cpp.o -MF CMakeFiles/glimac.dir/src/fish.cpp.o.d -o CMakeFiles/glimac.dir/src/fish.cpp.o -c /home/eric/F34/fishh3rd/glimac/src/fish.cpp

glimac/CMakeFiles/glimac.dir/src/fish.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glimac.dir/src/fish.cpp.i"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/eric/F34/fishh3rd/glimac/src/fish.cpp > CMakeFiles/glimac.dir/src/fish.cpp.i

glimac/CMakeFiles/glimac.dir/src/fish.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glimac.dir/src/fish.cpp.s"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/eric/F34/fishh3rd/glimac/src/fish.cpp -o CMakeFiles/glimac.dir/src/fish.cpp.s

glimac/CMakeFiles/glimac.dir/src/inputs.cpp.o: glimac/CMakeFiles/glimac.dir/flags.make
glimac/CMakeFiles/glimac.dir/src/inputs.cpp.o: /home/eric/F34/fishh3rd/glimac/src/inputs.cpp
glimac/CMakeFiles/glimac.dir/src/inputs.cpp.o: glimac/CMakeFiles/glimac.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eric/F34/fishh3rd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object glimac/CMakeFiles/glimac.dir/src/inputs.cpp.o"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT glimac/CMakeFiles/glimac.dir/src/inputs.cpp.o -MF CMakeFiles/glimac.dir/src/inputs.cpp.o.d -o CMakeFiles/glimac.dir/src/inputs.cpp.o -c /home/eric/F34/fishh3rd/glimac/src/inputs.cpp

glimac/CMakeFiles/glimac.dir/src/inputs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glimac.dir/src/inputs.cpp.i"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/eric/F34/fishh3rd/glimac/src/inputs.cpp > CMakeFiles/glimac.dir/src/inputs.cpp.i

glimac/CMakeFiles/glimac.dir/src/inputs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glimac.dir/src/inputs.cpp.s"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/eric/F34/fishh3rd/glimac/src/inputs.cpp -o CMakeFiles/glimac.dir/src/inputs.cpp.s

glimac/CMakeFiles/glimac.dir/src/tiny_obj_loader.cpp.o: glimac/CMakeFiles/glimac.dir/flags.make
glimac/CMakeFiles/glimac.dir/src/tiny_obj_loader.cpp.o: /home/eric/F34/fishh3rd/glimac/src/tiny_obj_loader.cpp
glimac/CMakeFiles/glimac.dir/src/tiny_obj_loader.cpp.o: glimac/CMakeFiles/glimac.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eric/F34/fishh3rd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object glimac/CMakeFiles/glimac.dir/src/tiny_obj_loader.cpp.o"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT glimac/CMakeFiles/glimac.dir/src/tiny_obj_loader.cpp.o -MF CMakeFiles/glimac.dir/src/tiny_obj_loader.cpp.o.d -o CMakeFiles/glimac.dir/src/tiny_obj_loader.cpp.o -c /home/eric/F34/fishh3rd/glimac/src/tiny_obj_loader.cpp

glimac/CMakeFiles/glimac.dir/src/tiny_obj_loader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glimac.dir/src/tiny_obj_loader.cpp.i"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/eric/F34/fishh3rd/glimac/src/tiny_obj_loader.cpp > CMakeFiles/glimac.dir/src/tiny_obj_loader.cpp.i

glimac/CMakeFiles/glimac.dir/src/tiny_obj_loader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glimac.dir/src/tiny_obj_loader.cpp.s"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/eric/F34/fishh3rd/glimac/src/tiny_obj_loader.cpp -o CMakeFiles/glimac.dir/src/tiny_obj_loader.cpp.s

glimac/CMakeFiles/glimac.dir/src/trackBallCamera.cpp.o: glimac/CMakeFiles/glimac.dir/flags.make
glimac/CMakeFiles/glimac.dir/src/trackBallCamera.cpp.o: /home/eric/F34/fishh3rd/glimac/src/trackBallCamera.cpp
glimac/CMakeFiles/glimac.dir/src/trackBallCamera.cpp.o: glimac/CMakeFiles/glimac.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eric/F34/fishh3rd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object glimac/CMakeFiles/glimac.dir/src/trackBallCamera.cpp.o"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT glimac/CMakeFiles/glimac.dir/src/trackBallCamera.cpp.o -MF CMakeFiles/glimac.dir/src/trackBallCamera.cpp.o.d -o CMakeFiles/glimac.dir/src/trackBallCamera.cpp.o -c /home/eric/F34/fishh3rd/glimac/src/trackBallCamera.cpp

glimac/CMakeFiles/glimac.dir/src/trackBallCamera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glimac.dir/src/trackBallCamera.cpp.i"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/eric/F34/fishh3rd/glimac/src/trackBallCamera.cpp > CMakeFiles/glimac.dir/src/trackBallCamera.cpp.i

glimac/CMakeFiles/glimac.dir/src/trackBallCamera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glimac.dir/src/trackBallCamera.cpp.s"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/eric/F34/fishh3rd/glimac/src/trackBallCamera.cpp -o CMakeFiles/glimac.dir/src/trackBallCamera.cpp.s

glimac/CMakeFiles/glimac.dir/src/walls.cpp.o: glimac/CMakeFiles/glimac.dir/flags.make
glimac/CMakeFiles/glimac.dir/src/walls.cpp.o: /home/eric/F34/fishh3rd/glimac/src/walls.cpp
glimac/CMakeFiles/glimac.dir/src/walls.cpp.o: glimac/CMakeFiles/glimac.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eric/F34/fishh3rd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object glimac/CMakeFiles/glimac.dir/src/walls.cpp.o"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT glimac/CMakeFiles/glimac.dir/src/walls.cpp.o -MF CMakeFiles/glimac.dir/src/walls.cpp.o.d -o CMakeFiles/glimac.dir/src/walls.cpp.o -c /home/eric/F34/fishh3rd/glimac/src/walls.cpp

glimac/CMakeFiles/glimac.dir/src/walls.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glimac.dir/src/walls.cpp.i"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/eric/F34/fishh3rd/glimac/src/walls.cpp > CMakeFiles/glimac.dir/src/walls.cpp.i

glimac/CMakeFiles/glimac.dir/src/walls.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glimac.dir/src/walls.cpp.s"
	cd /home/eric/F34/fishh3rd/build/glimac && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/eric/F34/fishh3rd/glimac/src/walls.cpp -o CMakeFiles/glimac.dir/src/walls.cpp.s

# Object files for target glimac
glimac_OBJECTS = \
"CMakeFiles/glimac.dir/src/Cone.cpp.o" \
"CMakeFiles/glimac.dir/src/Geometry.cpp.o" \
"CMakeFiles/glimac.dir/src/Image.cpp.o" \
"CMakeFiles/glimac.dir/src/Program.cpp.o" \
"CMakeFiles/glimac.dir/src/SDLWindowManager.cpp.o" \
"CMakeFiles/glimac.dir/src/Shader.cpp.o" \
"CMakeFiles/glimac.dir/src/Sphere.cpp.o" \
"CMakeFiles/glimac.dir/src/VAO_VBO.cpp.o" \
"CMakeFiles/glimac.dir/src/assets.cpp.o" \
"CMakeFiles/glimac.dir/src/boids.cpp.o" \
"CMakeFiles/glimac.dir/src/element.cpp.o" \
"CMakeFiles/glimac.dir/src/fish.cpp.o" \
"CMakeFiles/glimac.dir/src/inputs.cpp.o" \
"CMakeFiles/glimac.dir/src/tiny_obj_loader.cpp.o" \
"CMakeFiles/glimac.dir/src/trackBallCamera.cpp.o" \
"CMakeFiles/glimac.dir/src/walls.cpp.o"

# External object files for target glimac
glimac_EXTERNAL_OBJECTS =

glimac/libglimac.a: glimac/CMakeFiles/glimac.dir/src/Cone.cpp.o
glimac/libglimac.a: glimac/CMakeFiles/glimac.dir/src/Geometry.cpp.o
glimac/libglimac.a: glimac/CMakeFiles/glimac.dir/src/Image.cpp.o
glimac/libglimac.a: glimac/CMakeFiles/glimac.dir/src/Program.cpp.o
glimac/libglimac.a: glimac/CMakeFiles/glimac.dir/src/SDLWindowManager.cpp.o
glimac/libglimac.a: glimac/CMakeFiles/glimac.dir/src/Shader.cpp.o
glimac/libglimac.a: glimac/CMakeFiles/glimac.dir/src/Sphere.cpp.o
glimac/libglimac.a: glimac/CMakeFiles/glimac.dir/src/VAO_VBO.cpp.o
glimac/libglimac.a: glimac/CMakeFiles/glimac.dir/src/assets.cpp.o
glimac/libglimac.a: glimac/CMakeFiles/glimac.dir/src/boids.cpp.o
glimac/libglimac.a: glimac/CMakeFiles/glimac.dir/src/element.cpp.o
glimac/libglimac.a: glimac/CMakeFiles/glimac.dir/src/fish.cpp.o
glimac/libglimac.a: glimac/CMakeFiles/glimac.dir/src/inputs.cpp.o
glimac/libglimac.a: glimac/CMakeFiles/glimac.dir/src/tiny_obj_loader.cpp.o
glimac/libglimac.a: glimac/CMakeFiles/glimac.dir/src/trackBallCamera.cpp.o
glimac/libglimac.a: glimac/CMakeFiles/glimac.dir/src/walls.cpp.o
glimac/libglimac.a: glimac/CMakeFiles/glimac.dir/build.make
glimac/libglimac.a: glimac/CMakeFiles/glimac.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/eric/F34/fishh3rd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Linking CXX static library libglimac.a"
	cd /home/eric/F34/fishh3rd/build/glimac && $(CMAKE_COMMAND) -P CMakeFiles/glimac.dir/cmake_clean_target.cmake
	cd /home/eric/F34/fishh3rd/build/glimac && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glimac.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
glimac/CMakeFiles/glimac.dir/build: glimac/libglimac.a
.PHONY : glimac/CMakeFiles/glimac.dir/build

glimac/CMakeFiles/glimac.dir/clean:
	cd /home/eric/F34/fishh3rd/build/glimac && $(CMAKE_COMMAND) -P CMakeFiles/glimac.dir/cmake_clean.cmake
.PHONY : glimac/CMakeFiles/glimac.dir/clean

glimac/CMakeFiles/glimac.dir/depend:
	cd /home/eric/F34/fishh3rd/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/eric/F34/fishh3rd /home/eric/F34/fishh3rd/glimac /home/eric/F34/fishh3rd/build /home/eric/F34/fishh3rd/build/glimac /home/eric/F34/fishh3rd/build/glimac/CMakeFiles/glimac.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : glimac/CMakeFiles/glimac.dir/depend

