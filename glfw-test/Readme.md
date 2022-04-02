# OpenGL hello world

## Installation and usage

### Dependencies:
- glfw
- cmake, g++ (or whatever you want to build it with)
- openGL 3.3
- Eigen

###  Install `glfw`:
  - `sudo apt install xorg-dev`
  - `cd ext`
  - `git clone git clone https://github.com/glfw/glfw.git`
  - `cd glfw`
  - `cmake -S . -B build && cmake --build build -j$(nproc)`
  - Done. More info: https://www.glfw.org/docs/latest/compile.html

### Install packages

```
sudo apt-get install cmake pkg-config g++ build-essentials make \
    libglew-dev libglfw3-dev libglm-dev \
    libglu1-mesa-dev freeglut3-dev mesa-common-dev \
    libeigen3-dev
```

### Build and run

- go to repository root 
- `./build.sh` (needs +x permissions)
OR:
- `cmake -S . -B build && cmake --build build -j$(nproc) && ./build/app`

Tested only on Ubuntu 20.04, so you may have to do some additional work on Windows or Mac

Read the glfw manpages for installation guide and you'll be fine