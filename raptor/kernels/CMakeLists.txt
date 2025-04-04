set(CMAKE_INCLUDE_CURRENT_DIR ON)
enable_language(CUDA)
set(kernels_HEADERS
    kernels/kernel.cuh
    PARENT_SCOPE)
set(kernels_SOURCES
    kernels/kernel.cu
    PARENT_SCOPE)
