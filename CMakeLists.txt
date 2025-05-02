cmake_minimum_required(VERSION 3.31)
project(ThreeCpp)

set(CMAKE_CXX_STANDARD 20)

file(GLOB THIRD_PARTY_INCLUDE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/include
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glfw/include)
file(GLOB THIRD_PARTY_LIBRARY_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glfw/lib)
file(GLOB THIRD_PARTY_SHARED_LIBRARY_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glfw/bin/*)
file(GLOB THIRD_PARTY_SOURCE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/src/*)

file(GLOB ASSETS_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/assets)

include_directories(${THIRD_PARTY_INCLUDE_PATH})
link_directories(${THIRD_PARTY_LIBRARY_PATH})

file(COPY ${THIRD_PARTY_SHARED_LIBRARY_PATH} DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${ASSETS_PATH} DESTINATION ${CMAKE_BINARY_DIR})

add_subdirectory(src)
include_directories(src)

add_executable(ThreeCpp main.cpp ${THIRD_PARTY_SOURCE_PATH})
target_link_libraries(ThreeCpp
        PRIVATE
        three_cpp glfw3dll
)

enable_testing()
add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/googletest)
add_subdirectory(test)
