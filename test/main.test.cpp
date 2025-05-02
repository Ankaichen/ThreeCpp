/**
  ******************************************************************************
  * @file           : main.test.cpp
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 25-5-2
  ******************************************************************************
  */

#include <gtest/gtest.h>

int main(int argc, char *argv[]) {
    system("chcp 65001 > nul");
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::GTEST_FLAG(color) = "yes";
    return RUN_ALL_TESTS();
}
