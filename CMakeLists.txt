cmake_minimum_required (VERSION 3.11.4)
project (TMBlock)

if (NOT DEFINED HALIDE_DISTRIB_DIR)
    message(FATAL_ERROR "HALIDE_DISTRIB_DIR is not set")
endif()
include("${HALIDE_DISTRIB_DIR}/halide.cmake")

halide_library(tmblock SRCS tmblock_generator.cc)

add_executable(main main.cc)
target_link_libraries(main PUBLIC tmblock)
