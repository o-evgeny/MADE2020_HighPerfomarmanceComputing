cmake_minimum_required(VERSION 3.17)
set(CMAKE_CUDA_COMPILER "/usr/local/cuda/bin/nvcc")
project(pic_master CUDA)

set(CMAKE_CUDA_STANDARD 11)

add_executable(pic_master main.cu template.cu median.cu histogram.cu)

set_target_properties(pic_master PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

find_package(OpenCV REQUIRED)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})