/**
 * (c) 2024 Houssem Guissouma.
 * Licensed under the BSD-3-Clause License.
 * 
 * @file tests/src/utils/sys_ops_tests.cpp
 * @brief Definition of the test cases of the test suite SysOpsTests.
 */
#include <filesystem>
#include <string>

#include <gtest/gtest.h>

// Module(s) under Test
#include "icarus/utils/system_ops.h"

#include "project_fixtures.h"

namespace fs = std::filesystem;
using namespace icarus;

namespace tests {

/**
 * @test Tests the function for returning the output of a system command.
 */
TEST(SysOpsTests, SysExeCmd) {
    // Execute an echo command
    std::string cmd = "echo Hello, World!";
    std::string result = utils::execCmd(cmd.c_str());
    ASSERT_EQ(result, "Hello, World!\n");

    // Execute a command that doesn't exist
    cmd = "non_existing_command";
    ASSERT_THROW(utils::execCmd(cmd.c_str()), std::runtime_error);
}

/**
 * @test Tests whether the function getExePath works correctly.
 */
TEST(SysOpsTests, GetExePath) {
    fs::path path = utils::getExePath();

    std::string last_part = path.filename().string();
    #ifdef _WIN32
        ASSERT_EQ(last_part, "icarus-utils-tests.exe");
    #elif __linux__
        ASSERT_EQ(last_part, "icarus-utils-tests");
    #endif
}

/**
 * @test Tests the function for getting the absolute path of a target path.
 */
TEST(SysOpsTests, GetAbsolutePath) {
	// Test with a relative path
	fs::path dir_path = fs::current_path();
	std::string target_path = "test_file.txt";
	fs::path abs_path = utils::getAbsPath(dir_path, target_path);
	ASSERT_EQ(abs_path, dir_path / target_path);

	// Test with an absolute path
	dir_path = fs::path("/home/user");
	// Different OSs have different path separators
	#ifdef _WIN32
		target_path = "C:\\test_file.txt";
	#elif __linux__
		target_path = "/home/user/test_file.txt";
	#endif
	abs_path = utils::getAbsPath(dir_path, target_path);
	ASSERT_EQ(abs_path, fs::path(target_path));
}

/**
 * @test Tests the function for removing the extension from a filename.
 */
TEST(SysOpsTests, RemoveExtension) {
	std::string filename = "test_file.txt";
	ASSERT_EQ(utils::removeExtension(filename), "test_file");

	filename = "test_file";
	ASSERT_EQ(utils::removeExtension(filename), "test_file");

	filename = "test_file.tar.gz";
	ASSERT_EQ(utils::removeExtension(filename), "test_file.tar");
}

/**
 * @test Tests the function for checking the validity of a file of a given extension.
 */
TEST(SysOpsTests, IsValidFile) {
	// Test for an existing file
	std::string yaml_file_path = (kTestDataDir / "abs_value.yaml").string();
	ASSERT_TRUE(utils::isValidFile(yaml_file_path, "yaml"));

	// Test for a non-existing file
	std::string non_existing_file = (kTestDataDir / "non_existing_file.txt").string();
	ASSERT_FALSE(utils::isValidFile(non_existing_file, "txt"));
}

} // namespace tests
