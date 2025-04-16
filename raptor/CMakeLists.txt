enable_language(CUDA)
add_subdirectory(core)
add_subdirectory(gallery)
add_subdirectory(util)
add_subdirectory(ruge_stuben)
add_subdirectory(aggregation)
add_subdirectory(multilevel)
add_subdirectory(krylov)
add_subdirectory(profiling)
add_subdirectory(external)
add_subdirectory(kernels)

if(WITH_MPI)
  set(par_SOURCES par_strength.cpp)
else()
  set(par_SOURCES)
endif()

# NCCL
find_package(CUDAToolkit REQUIRED)
option(CLUSTER_MODE "Set to ON if building on a cluster" OFF)
if(CLUSTER_MODE)
  message(STATUS "Building in cluster mode")
  find_path(NCCL_INCLUDE_DIRS nccl.h PATHS $ENV{CONDA_PREFIX}/include)
  find_library(NCCL_LIBRARIES nccl PATHS $ENV{CONDA_PREFIX}/lib)
else()
  message(STATUS "Building in local mode")
  find_path(NCCL_INCLUDE_DIRS nccl.h PATHS /usr/include)
  find_library(NCCL_LIBRARIES nccl PATHS /usr/lib/x86_64-linux-gnu)
endif()

if(NCCL_INCLUDE_DIRS AND NCCL_LIBRARIES)
  message(STATUS "NCCL found!")
  message(STATUS "NCCL Include Dir: ${NCCL_INCLUDE_DIRS}")
  message(STATUS "NCCL Library: ${NCCL_LIBRARIES}")
else()
  message(FATAL_ERROR "❌ NCCL NOT found! Check your installation.")
endif()
# find_package(CUDAToolkit REQUIRED) find_path(NCCL_INCLUDE_DIRS nccl.h PATHS
# /usr/include) find_library(NCCL_LIBRARIES nccl PATHS
# /usr/lib/x86_64-linux-gnu)

add_library(
  raptor
  ${core_SOURCES}
  ${core_HEADERS}
  ${gallery_SOURCES}
  ${gallery_HEADERS}
  ${ext_gallery_HEADERS}
  ${util_SOURCES}
  ${util_HEADERS}
  ${par_SOURCES}
  strength.cpp
  ${ruge_stuben_SOURCES}
  ${ruge_stuben_HEADERS}
  ${kernels_SOURCES}
  ${kernels_HEADERS}
  ${aggregation_SOURCES}
  ${aggregation_HEADERS}
  ${multilevel_SOURCES}
  ${multilevel_HEADERS}
  ${krylov_SOURCES}
  ${krylov_HEADERS}
  ${profile_SOURCES}
  ${profile_HEADERS}
  ${external_SOURCES}
  ${external_HEADERS})

target_link_libraries(
  raptor
  PUBLIC ${MPI_C_LIBRARIES}
         ${MFEM_LIBRARIES}
         ${METIS_LIBRARIES}
         ${HYPRE_LIBRARIES}
         ${MUELU_LIBRARIES}
         ${PETSC_LIBRARIES}
         ${PTSCOTCH_LIBRARIES}
         ${PARMETIS_LIBRARIES}
         ${EXTERNAL_LIBS}
         ${NCCL_LIBRARIES}
         CUDA::cusparse)

target_include_directories(
  raptor
  PUBLIC $<INSTALL_INTERFACE:include> ${NCCL_INCLUDE_DIRS}
         ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES}
         $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>)

include(GNUInstallDirs)
install(
  TARGETS raptor
  EXPORT raptorTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES raptor.hpp DESTINATION "include/raptor")
install(FILES ${core_HEADERS} DESTINATION "include/raptor/core")
install(FILES ${gallery_HEADERS} DESTINATION "include/raptor/gallery")
install(FILES ${ext_gallery_HEADERS}
        DESTINATION "include/raptor/gallery/external")
install(FILES ${util_HEADERS} DESTINATION "include/raptor/util/linalg")
install(FILES ${ext_util_HEADERS}
        DESTINATION "include/raptor/util/linalg/external")
install(FILES ${kernels_HEADERS} DESTINATION "include/raptor/kernels")
install(FILES ${ruge_stuben_HEADERS} DESTINATION "include/raptor/ruge_stuben")
install(FILES ${aggregation_HEADERS} DESTINATION "include/raptor/aggregation")
install(FILES ${multilevel_HEADERS} DESTINATION "include/raptor/multilevel")
install(FILES ${krylov_HEADERS} DESTINATION "include/raptor/krylov")
install(FILES ${profile_HEADERS} DESTINATION "include/raptor/profiling")
install(FILES ${external_HEADERS} DESTINATION "include/raptor/external")
install(
  EXPORT raptorTargets
  FILE raptorTargets.cmake
  NAMESPACE "raptor::"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/raptor)
export(
  EXPORT raptorTargets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/raptorTargets.cmake
  NAMESPACE "raptor::")
export(PACKAGE raptor)

configure_file(
  ${PROJECT_SOURCE_DIR}/config/raptorConfig.cmake.in
  ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/raptorConfig.cmake @ONLY)

install(
  FILES ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/raptorConfig.cmake
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/cmake/raptor)

if(ENABLE_UNIT_TESTS)
  add_subdirectory(tests)
  add_subdirectory(core/tests)
  add_subdirectory(util/tests)
  add_subdirectory(ruge_stuben/tests)
  add_subdirectory(aggregation/tests)
  add_subdirectory(multilevel/tests)
  add_subdirectory(gallery/tests)
  add_subdirectory(krylov/tests)
  add_subdirectory(external/tests)
endif()
