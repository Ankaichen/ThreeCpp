add_subdirectory(core)

add_library(three_cpp INTERFACE)

target_link_libraries(three_cpp
        INTERFACE
        three_cpp_core
)