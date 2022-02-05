# OpenGL hello world

## Installation and usage

- install dependencies
- go to repository root 
- `mkdir build`
- `cd build`
- `cmake ..`
- `make`
- `./app`


## Dependencies

- glfw https://github.com/glfw/glfw
- cmake
- openGL 3.3 
- libeigen3-dev
- 
Tested only on Ubuntu 20.04, so you may have to do some additional work on Windows or Mac

Read the glfw manpages for installation guide and you'll be fine

## TODO

- make portable
- use pre-built binaries ?
-- switching between os'es, different build types (release/debug) is shitty without the source code?
- remove the glfw copypaste fork
