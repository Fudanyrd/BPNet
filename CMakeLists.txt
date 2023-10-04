cmake_minimum_required(VERSION 3.11)
project(main)

add_subdirectory(BPNet)

add_executable(${PROJECT_NAME} fd_max.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/BPNet/include)

target_link_libraries(${PROJECT_NAME} Net)