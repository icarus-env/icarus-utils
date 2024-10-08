/**
 * (c) 2024 Houssem Guissouma.
 * Licensed under the BSD-3-Clause License.
 * 
 * @file tests/src/utils/data_node_tests.cpp
 * @brief Implementation of the fixture DataNodeTests and definition of its test cases.
 */
#include "data_node_tests.h"

// Module under Test
#include "icarus/utils/data_node.h"

#include "project_fixtures.h"

namespace fs = std::filesystem;
using namespace icarus;

namespace tests {

// ================================
// DataNodeTests class
// ================================

fs::path DataNodeTests::results_dir_ = kTestResutDir / "DataNodeTests";

const std::string DataNodeTests::fm_yaml_path_ = (kTestDataDir / "simple_calc_fm.yaml").string();

void DataNodeTests::SetUpTestSuite() {
    if (!fs::exists(results_dir_)) {
        if (fs::create_directories(results_dir_)) {
            std::cout << "Created results directory: " << results_dir_ << std::endl;
        } else {
            std::cout << "Failed to create directory: " << results_dir_ << std::endl;
        }
    }
}

DataNodeTests::DataNodeTests()
        : basic_map_(DataNode::Type::kMap),
          basic_seq_(DataNode::Type::kSeq) {
    // Define data of the basic test map 
    basic_map_["name"] << "Steinbuch";
    basic_map_["nationality"] << "German";
    basic_map_["age"] << 40;
    basic_map_["height"] << 1.78;

    // Define data of the basic test sequence
    basic_seq_[0] << "First element";
    basic_seq_[1] << "Second element";
    basic_seq_[2] << "Third element";
    basic_seq_[3] << "Fourth element";
}

// ================================
// DataNodeTests tests
// ================================

/**
 * @test Checks the reading of YAML files using the class DataNode.
 */
TEST_F(DataNodeTests, ReadFromFile) {
    // Test with the data of the feature model "simple_calculation"
    DataNode fm_spec(fm_yaml_path_);

    // Assertions of the feature model data
    ASSERT_EQ(fm_spec.getNumChildren(), 2);
    ASSERT_TRUE(fm_spec.hasChild("FEATURES"));
    ASSERT_EQ(fm_spec["FEATURES"].getNumChildren(), 6);

    // Add an additional child node
    fm_spec["Child key"] = "Child value";
    ASSERT_EQ(fm_spec.getNumChildren(), 3);
}

/**
 * @test Checks the printing of data nodes to the console.
 */
TEST_F(DataNodeTests, PrintSpec) {
	// Test with the basic test data
    basic_map_.print(DataNode::Format::kYaml);
    basic_map_.print(DataNode::Format::kJson);

    basic_seq_.print(DataNode::Format::kYaml);
    basic_seq_.print(DataNode::Format::kJson);

    // Test with YAML of the feature model "simple_calculation"
    DataNode fm_spec(fm_yaml_path_);
    fm_spec.print();
}

/**
 * @test Checks writing the spec data to a local file.
 */
TEST_F(DataNodeTests, WriteToFile) {
    // Write the basic map to a YAML file
    std::string output_file_path = (results_dir_ / "test_file.yaml").string();
    basic_map_.writeToFile(output_file_path);

    // Read the written YAML file and assert its content
    DataNode read_yaml(output_file_path);
    ASSERT_EQ(basic_map_["name"].as<std::string>(), read_yaml["name"].as<std::string>());
    ASSERT_EQ(basic_map_["age"].as<int>(), read_yaml["age"].as<int>());
}

/**
 * @test Checks the iteration over the children of a node.
 */
TEST_F(DataNodeTests, Iterate) {
    // Test with the data of the feature model "simple_calculation"
    DataNode fm_spec(fm_yaml_path_);

    // Iterate over the children of the node with the key "FEATURES"
    for (const auto& child : fm_spec["FEATURES"]) {
        auto feature_map = child.first();
        feature_map.print();

        ASSERT_TRUE(feature_map.isMap());
        std::cout << "Key: " << feature_map.getKey() << std::endl;

        // Retrieve some fields from the child map
        std::string f_parent = feature_map["parent"].as<std::string>();
        std::cout << "Feature parent: " << f_parent << std::endl;
        auto reqs_seq = feature_map["reqs"];
        reqs_seq.print();
    }
}

} // namespace tests
