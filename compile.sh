cmake -B build -DWITH_MPI=ON && \
cmake --build build --parallel -- VERBOSE=1 
# clear && \
# mpirun -n 5  build/examples/benchmark_setup
