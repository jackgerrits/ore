# An OpenGL Rendering Engine
![Build and test](https://github.com/jackgerrits/ore/workflows/Build%20and%20test/badge.svg?branch=master)


This is an in progress port of the engine used in my [other project](https://github.com/jackgerrits/opengl-car-game) to a generic reusable engine. It follows the entity-component-system design.

## Dependencies

### Ubuntu/Debian
```sh
apt-get install libglfw3-dev libglm-dev
```
### Vcpkg on Windows
```sh
vcpkg install --triplet x64-windows glfw3 glm
```
See [Vcpkg docs](https://github.com/Microsoft/vcpkg/blob/master/docs/users/integration.md#with-cmake) for how to get CMake to pick these up.

## Build
```
mkdir build
cmake ..
make
```
