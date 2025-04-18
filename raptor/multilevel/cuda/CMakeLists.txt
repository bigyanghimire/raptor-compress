# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(ml_cuda_HEADERS
    multilevel/cuda/par_multilevel_cuda.cuh
    PARENT_SCOPE)

set(ml_cuda_SOURCES
    multilevel/cuda/par_multilevel_cuda.cu
    PARENT_SCOPE)
