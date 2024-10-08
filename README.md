
# General description

The repository contains simple solution for the test task for CADEXCHANGER with the next requirements:

Design a small program in C++ that would implement support of 3D curves hierarchy.
1. Support a few types of 3D geometric curves – circles, ellipses and 3D helixes. (Simplified
definitions are below). Each curve should be able to return a 3D point and a first derivative (3D
vector) per parameter t along the curve.
2. Populate a container (e.g. vector or list) of objects of these types created in random manner with
random parameters.
3. Print coordinates of points and derivatives of all curves in the container at t=PI/4.
4. Populate a second container that would contain only circles from the first container. Make sure the
second container shares (i.e. not clones) circles of the first one, e.g. via pointers.
5. Sort the second container in the ascending order of circles’ radii. That is, the first element has the
smallest radius, the last - the greatest.
6. Compute the total sum of radii of all curves in the second container.
(*) Additional optional requirements:
7. Split implementation into a library of curves (.dll or .so) and executable which uses API of this
library.
8. Implement computation of the total sum of radii using parallel computations (e.g. OpenMP or Intel
TBB library).
Requirements to the implementation:
1. The implementation must use virtual methods.
2. Has neither explicit memory deallocation nor memory leaks.
3. Curves must be physically correct (e.g. radii must be positive).
4. Containers and sorting must be implemented using STL (C++ Standard Template Library).
5. The implementation may use constructs of C++11 or higher.
6. The code must compile with any compiler of your choice (gcc, Visual C++, etc).

The program had written by Alexey Vilensky.
The program consits from separate parts: curves library (default with dynamic linkage, but user can specify it by cmake CLI) which implements some basic curves operations, structures and executable file ctask which impements necessary operations according to the technical requirements.
The building requires conan package manager and cmake.

# Requirements

+ C++ compiler which supports C++20 standard
+ cmake>=3.20
+ conan>=2.6.0

# Building

For program building run several commands in shell

    conan profile detect --force
    conan install . --output-folder=build --build=missing
    cmake --preset conan-release
    cmake --build build/

The building process tested with the next configurations: /n

/n
macos arm clang config

    [settings]
    arch=armv8
    build_type=Release
    compiler=apple-clang
    compiler.cppstd=gnu17
    compiler.libcxx=libc++
    compiler.version=14
    os=Macos


Ubuntu x86_64 gcc config

    [settings]
    arch=x86_64
    build_type=Release
    compiler=gcc
    compiler.cppstd=gnu17
    compiler.libcxx=libstdc++11
    compiler.version=11
    os=Linux

# Execution

For execution purpose run several commands in shell

    cd build && ./ctask
