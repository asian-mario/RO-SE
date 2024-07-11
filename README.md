# RO:SE
# ![RO:SE](img/image.png)


## Overview

RO:SE is a high-performance audio library designed to provide advanced audio capabilities for game developers and multimedia applications with ease. With support for 3D sound, RO:SE allows for an immersive audio experience, bringing environments to life with precise sound positioning and movement.

## Installation

### Prerequisites

- **CMake**: Ensure that CMake is installed on your system.
- **Git**: Required for cloning the repository.

### Steps to Install

1. **Clone the Repository**:
    ```
    git clone https://github.com/yourusername/ROSE.git
    cd ROSE
    ```

2. **Build Dependencies**:
    - Navigate to each vendor folder and run CMake:
      ```
      cd vendor/openal
      mkdir build && cd build
      cmake ..
      cmake --build .
      cd ../../..
      
      cd vendor/libsndfile
      mkdir build && cd build
      cmake ..
      cmake --build .
      cd ../../..
      ```

3. **Build RO:SE**:
    - Run CMake on the root vendor folder:
      ```
      mkdir build && cd build
      cmake ..
      cmake --build .
      ```

4. **Copy Libraries**:
    - After building, copy the generated `.lib` files to your project's library directory. The `.lib` files are typically found in the `build` directories of each vendor.

## Usage

To understand how to integrate and use the RO:SE library in your project, refer to the `example_impl.cpp` file. This example demonstrates the basic setup and usage of the library, including initializing the engine, loading sounds, and managing 3D audio sources.

### Key Features

- **3D Sound Support**: RO:SE supports three-dimensional sound, allowing for spatial audio effects that enhance the realism of your applications. Sounds can be positioned anywhere in 3D space, and as the listener moves, the sounds will adjust accordingly to simulate realistic audio dynamics.

## Contributing

Contributions are welcome! If you have any ideas, suggestions, or bug reports, feel free to open an issue or submit a pull request.


