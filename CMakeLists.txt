cmake_minimum_required (VERSION 3.11.4)
project (tmblock)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(include)

if (NOT DEFINED HALIDE_DISTRIB_DIR)
    message(FATAL_ERROR "HALIDE_DISTRIB_DIR is not set")
endif()
include("${HALIDE_DISTRIB_DIR}/halide.cmake")

#find_package(OpenCV REQUIRED core imgcodecs highgui)
find_package(PNG REQUIRED)
find_package(JPEG REQUIRED)
find_package(Threads REQUIRED)

halide_library(tmblock_pre_planar
    SRCS src/pre_generator.cc
    GENERATOR_NAME tmblock_pre
    GENERATOR_ARGS layout=planar
)
halide_library(tmblock_pre_packed
    SRCS src/pre_generator.cc
    GENERATOR_NAME tmblock_pre
    GENERATOR_ARGS layout=packed
)
halide_library(tmblock_post_planar
    SRCS src/post_generator.cc
    GENERATOR_NAME tmblock_post
    GENERATOR_ARGS layout=planar
)
halide_library(tmblock_post_packed
    SRCS src/post_generator.cc
    GENERATOR_NAME tmblock_post
    GENERATOR_ARGS layout=packed
)
halide_library(tmblock_embed_planar
    SRCS src/embed_generator.cc
    GENERATOR_NAME tmblock_embed
    GENERATOR_ARGS layout=planar
)
halide_library(tmblock_embed_packed
    SRCS src/embed_generator.cc
    GENERATOR_NAME tmblock_embed
    GENERATOR_ARGS layout=packed
)

include_directories(${HALIDE_DISTRIB_DIR}/include ${HALIDE_DISTRIB_DIR}/tools)

add_executable(pre cmd/pre.cc)
target_link_libraries(pre PUBLIC tmblock_pre_planar ${PNG_LIBRARIES} ${JPEG_LIBRARIES} Threads::Threads)

add_executable(post cmd/post.cc)
target_link_libraries(post PUBLIC tmblock_post_planar ${PNG_LIBRARIES} ${JPEG_LIBRARIES} Threads::Threads)

add_executable(water cmd/water.cc)
target_link_libraries(water PUBLIC tmblock_embed_planar ${PNG_LIBRARIES} ${JPEG_LIBRARIES} Threads::Threads)

add_library(${CMAKE_PROJECT_NAME} SHARED src/wrapper.cc)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC
    tmblock_pre_planar tmblock_pre_packed
    tmblock_post_planar tmblock_post_packed
    tmblock_embed_planar tmblock_embed_packed)
