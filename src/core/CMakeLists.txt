file(GLOB_RECURSE THREE_CPP_CORE_SOURCE ./ *.cpp)
add_library(three_cpp_core
        ${THREE_CPP_CORE_SOURCE})