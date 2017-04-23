# Ore
<!--
remove build status until issues sorted out
[![Build Status](https://travis-ci.org/jackgerrits/ore.svg?branch=master)](https://travis-ci.org/jackgerrits/ore)
-->

An OpenGL rendering engine.

This is an in progress port of the engine used in my [other project](https://github.com/jackgerrits/opengl-car-game) to a generic reusable engine.

## Usage
To use this in a project run the following:
```
cmake . && make
```
This produces a shared library, this must be linked as well the headers included. More detailed instructions will be added.

## Windows
In order for a Visual Studio solution to be generated and build correctly the locations of dependencies can be defined on the command line:
```
 cmake . \
 -DGLEW_INCLUDE_DIR=/e/code/glew/include \
 -DGLUT_INCLUDE_DIR=/e/code/freeglut/include \
 -DGLM_INCLUDE_DIR=/e/code/glm \
 -DGLEW_LIBRARY=/e/code/glew/lib/Release/Win32/glew32.lib \
 -DGLUT_LIBRARIES=/e/code/freeglut/lib/freeglut.lib
```
### Dependencies
- [GLM](https://github.com/g-truc/glm/releases)
- [GLUT](http://freeglut.sourceforge.net/index.php#download)
- [GLEW](http://glew.sourceforge.net/index.html)
