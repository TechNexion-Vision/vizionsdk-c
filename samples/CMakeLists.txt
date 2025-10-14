cmake_minimum_required(VERSION 3.10)
project(sample)

# set(VIZIONSDK_C_PREFIX "${vizionsdk_c_dir_path}")
set(VIZIONSDK_C_PREFIX "E:/vizionsdk_c-25.10.1")

list(APPEND CMAKE_PREFIX_PATH ${VIZIONSDK_C_PREFIX})
find_package(vizionsdk_c REQUIRED)

# Add source to this project's executable.
add_executable(sample "sample.c")

target_include_directories(sample PRIVATE ${VIZIONSDK_C_INCLUDE_DIR})

# Link libraries
target_link_libraries(sample
  PRIVATE
  vizionsdk_c::vizionsdk_c
)