cmake_minimum_required(VERSION 3.1)

set (CMAKE_CXX_STANDARD 11)

option(BENCHMARK_ENABLE_TESTING "Enable testing of the benchmark library." OFF)
if(NOT WIN32)
  add_definitions(-Wno-error)
endif()
add_subdirectory(benchmark EXCLUDE_FROM_ALL)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-march=native" COMPILER_SUPPORTS_MARCH_NATIVE)
if(COMPILER_SUPPORTS_MARCH_NATIVE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
endif()

function(fetch_eigen VERSION NAME)
  if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/eigen-${NAME})
    message("Downloading Eigen ${VERSION} ...")
    file(DOWNLOAD https://bitbucket.org/eigen/eigen/get/${VERSION}.tar.bz2 ${CMAKE_CURRENT_BINARY_DIR}/${VERSION}.tar.bz2)
    execute_process(
      COMMAND ${CMAKE_COMMAND} -E tar xjf ${CMAKE_CURRENT_BINARY_DIR}/${VERSION}.tar.bz2
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    file(GLOB EIGEN_DIR "eigen-eigen-*")
    file(RENAME ${EIGEN_DIR} ${CMAKE_CURRENT_BINARY_DIR}/eigen-${NAME})
    file(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/${VERSION}.tar.bz2)
  endif()
endfunction()

function(build_eigen_bench VERSION NAME)
  fetch_eigen(${VERSION} ${NAME})
  set(EIGEN_DIR ${CMAKE_CURRENT_BINARY_DIR}/eigen-${NAME})
  configure_file(bench.in.cpp ${CMAKE_CURRENT_BINARY_DIR}/bench_${NAME}.cpp)
  add_executable(bench_${NAME} ${CMAKE_CURRENT_BINARY_DIR}/bench_${NAME}.cpp)
  target_include_directories(bench_${NAME} SYSTEM PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/eigen-${NAME})
  target_link_libraries(bench_${NAME} benchmark)
  if(NOT WIN32)
    target_link_libraries(bench_${NAME} pthread)
  endif()
  add_custom_command(TARGET run_benchmark
    COMMAND bench_${NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endfunction()

add_custom_target(run_benchmark)

build_eigen_bench(3.2.8 3_2_8)
build_eigen_bench(3.2.10 3_2_10)
build_eigen_bench(3.3-beta2 3_3_beta)
build_eigen_bench(3.3.4 3_3_4)
build_eigen_bench(3.3 trunk)

