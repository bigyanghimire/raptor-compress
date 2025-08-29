$mode=$1
#cmake -B build -Werror=dev --warn-uninitialized  -DWITH_MPI=ON && \
cmake -B build -DWITH_MPI=ON -DCLUSTER_MODE=$1 -DWITH_CUDA=$2 && \
cmake --build build --parallel $(nproc) -- VERBOSE=1 &&
clear && \
mpirun -n 1  build/examples/example
# mpirun -n 1  build/examples/benchmark_amg