cmake_minimum_required(VERSION 3.10)

project(main)

add_executable(
  main
  src/main.c
  src/kernels.c
  src/utils.c
)

target_link_libraries(
  main
  -lm
  -fopenmp
)

if (BENCH)
  add_definitions(-DBENCH)
endif()

