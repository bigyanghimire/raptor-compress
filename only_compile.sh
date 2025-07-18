clear
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DWITH_MPI=ON -DWITH_DOXYGEN=OFF -DCMAKE_BUILD_TYPE=Debug && \
cmake --build build --parallel $(nproc) 