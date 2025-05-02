file(GLOB_RECURSE THREE_CPP_CORE_TEST_SOURCE ./core *.cpp)

add_executable(ThreeCppTest
        main.test.cpp
        ${THREE_CPP_CORE_TEST_SOURCE})

target_link_libraries(ThreeCppTest
        PUBLIC
        three_cpp
        gtest gtest_main
        gmock gmock_main
)

add_test(NAME ThreeCppTest COMMAND ThreeCppTest)


