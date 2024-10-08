/**
 * (c) 2024 Houssem Guissouma.
 * Licensed under the BSD-3-Clause license.
 * 
 * @file tests/src/helpers/main.cpp
 * @brief Main function for the test suites of the library "icarus_helpers".
 */
#include <gtest/gtest.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
