Template to run benchmarks across multiple versions of Eigen
==

This repository can serve as a template to run benchmarks across multiple versions of Eigen.

Requirements
--

- CMake >= 3.1
- Any C++ compiler

Edit the benchmark code
--

Change the code in `bench.in.cpp` and rebuild the code. Look at google benchmark documentation for advanced features.

Add/Remove an Eigen version
--

Simply edit `CMakeLists.txt` and add/remove versions as you see fit.

### A note on trunk

To update the trunk version, remove the `eigen-trunk` folder in your build directory and run cmake again.
