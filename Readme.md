# raptor

RAPtor is a general, high performance algebraic multigrid solver.

# CUDA kernels

- CUDA kernels are present in raptor/kernels.
- NCCL types are present in raptor/core/nccl_types.cpp.

# Requirements

- CMake (version 3.27.9 or higher)

- MPI

- CUDA Toolkit

- gcc

# Build Instructions

To compile the AMG solver with support for MPI, CUDA, and optional cluster-specific configurations, use the provided `compile.sh` script. This script configures and builds the project using CMake with parallel compilation enabled. `CLUSTER_MODE` is used to select between local computer and Palmetto cluster. Options are ON and OFF.

1. `./compile.sh <CLUSTER_MODE>`

Note: to test with a hostfile, `hostfile.txt`, use

```
cmake -Bbuild -DWITH_HOSTFILE=ON -DHOSTFILE=<full path to>/hostfile.txt
cmake --build build --parallel

```

# Full Example

From the `examples` directory:

```
mpirun -n 4 ./example
```
