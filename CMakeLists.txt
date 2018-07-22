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

halide_library(tmblock_pre SRCS src/pre_tmblock_generator.cc)
halide_library(tmblock_post SRCS src/post_tmblock_generator.cc)
halide_library(watermark SRCS src/watermark_generator.cc)

include_directories(${HALIDE_DISTRIB_DIR}/include ${HALIDE_DISTRIB_DIR}/tools)

add_executable(pre cmd/pre.cc)
target_link_libraries(pre PUBLIC tmblock_pre ${PNG_LIBRARIES} ${JPEG_LIBRARIES} Threads::Threads)

add_executable(post cmd/post.cc)
target_link_libraries(post PUBLIC tmblock_post ${PNG_LIBRARIES} ${JPEG_LIBRARIES} Threads::Threads)

add_executable(water cmd/water.cc)
target_link_libraries(water PUBLIC watermark ${PNG_LIBRARIES} ${JPEG_LIBRARIES} Threads::Threads)
