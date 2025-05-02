add_executable(ThreeCppTest main.test.cpp)

target_link_libraries(ThreeCppTest
        PRIVATE
        gtest
        gtest_main
        gmock
        gmock_main
)

add_test(NAME ThreeCppTest COMMAND ThreeCppTest)


