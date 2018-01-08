cmake_minimum_required (VERSION 3.11.4)
project (TMBlock)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if (NOT DEFINED HALIDE_DISTRIB_DIR)
    message(FATAL_ERROR "HALIDE_DISTRIB_DIR is not set")
endif()
include("${HALIDE_DISTRIB_DIR}/halide.cmake")

#find_package(OpenCV REQUIRED core imgcodecs highgui)
find_package(PNG REQUIRED)
find_package(JPEG REQUIRED)
find_package(Threads REQUIRED)

halide_library(tmblock SRCS tmblock_generator.cc)

include_directories(${HALIDE_DISTRIB_DIR}/include ${HALIDE_DISTRIB_DIR}/tools)

add_executable(main main.cc)
target_link_libraries(main PUBLIC tmblock ${PNG_LIBRARIES} ${JPEG_LIBRARIES} Threads::Threads)
