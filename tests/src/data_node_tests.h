/**
 * (c) 2024 Houssem Guissouma.
 * Licensed under the BSD-3-Clause License.
 * 
 * @file tests/src/utils/data_node_tests.h
 * @brief Definition of the test fixture DataNodeTests.
 */
#pragma once

#include <filesystem>

#include <gtest/gtest.h>

#include "icarus/utils/data_node.h"

namespace tests {

/**
* @brief Fixture for testing the YAML processing functions.
*/
class DataNodeTests : public ::testing::Test {
protected:
    /**
     * @brief Sets up the test suite by creating the results subdirectory if missing.
     */
    static void SetUpTestSuite();

    /**
     * @brief Constructs a fixture test case and initializes the basic data map and sequence.
     */
    DataNodeTests();

    /// Basic data map for testing.
    icarus::DataNode basic_map_;
    /// Basic data sequence for testing.
    icarus::DataNode basic_seq_;

    /// Path of the test results subdirectory.
    static std::filesystem::path results_dir_;

    /// Path of feature model YAML file to be tested
    const static std::string fm_yaml_path_;
};

} // namespace tests
