project(Net)

add_library(${PROJECT_NAME} STATIC BPNet.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)
