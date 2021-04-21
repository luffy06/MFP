cmake_minimum_required(VERSION 3.12)
project(MF VERSION 1.0 LANGUAGES CXX)

# specify c/c++ standard
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif(NOT CMAKE_CXX_STANDARD)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(LIB_DIR "${PROJECT_SOURCE_DIR}/lib")

include_directories(
  ${SRC_DIR}
)

add_subdirectory(${LIB_DIR}/or-tools)

add_executable(spfa "${SRC_DIR}/test_spfa.cc")
add_executable(mf "${SRC_DIR}/test_mf.cc")
add_executable(gen "${SRC_DIR}/data_gen.cc")
add_executable(run "${SRC_DIR}/main.cc")
target_link_libraries(run ortools::ortools)
