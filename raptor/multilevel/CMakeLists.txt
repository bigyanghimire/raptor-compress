# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_subdirectory(cuda)
# Create a variable called core_SOURCES containing all .cpp files:
if(WITH_MPI)
  set(par_multilevel_HEADERS multilevel/par_level.hpp
                             multilevel/par_multilevel.hpp)
  set(par_multilevel_SOURCES)
else()
  set(par_multilevel_HEADERS "")
  set(par_multilevel_SOURCES "")
endif()

set(multilevel_HEADERS
    multilevel/level.hpp multilevel/multilevel.hpp multilevel/cuda/par_multilevel_cuda.cuh ${ml_cuda_HEADERS}
    ${par_multilevel_HEADERS}
    PARENT_SCOPE)

set(multilevel_SOURCES
    ${ml_cuda_SOURCES} ${par_multilevel_SOURCES} multilevel/cuda/par_multilevel_cuda.cu
    PARENT_SCOPE)

# With CUDA

set(multilevel_cuda_HEADERS
    ${ml_cuda_HEADERS} multilevel/cuda/par_multilevel_cuda.cuh
    PARENT_SCOPE)

set(multilevel_cuda_SOURCES
    ${ml_cuda_SOURCES} multilevel/cuda/par_multilevel_cuda.cuh
    PARENT_SCOPE)
