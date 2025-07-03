clear
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DWITH_MPI=ON -DWITH_DOXYGEN=OFF && \
cmake --build build --parallel $(nproc) &&
clear && \
mpirun -n 2  build/examples/benchmark_amg
# mpirun -n 2 build/examples/benchmark_amg | grep -c 'MPI Send'
# cd build
# cmake .. -DWITH_MPI=ON  # Only if you changed config
# cmake --build . --parallel $(nproc)
# mpirun -n 2  build/examples/benchmark_amg