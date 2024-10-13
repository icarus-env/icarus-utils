/**
 * (c) 2024 Houssem Guissouma.
 * Licensed under the BSD-3-Clause License.
 *
 * @file tests/src/utils/str_proc_tests.cpp
 * @brief Definition of the test cases of the test suite StringProcTests.
 */
#include <gtest/gtest.h>

// Module under Test
#include "icarus/utils/str_processing.h"

using namespace icarus::utils;

namespace tests {

/**
 * @test Tests the function trimStr for trimming whitespace characters from a string.
 */
TEST(StrProcTests, TrimStr) {
	// Test string with leading and trailing whitespace
	std::string test_str = "  Hello, World!  ";
	ASSERT_EQ(trimStr(test_str), "Hello, World!");

	// Test string with leading whitespace
	test_str = "    Hi";
	ASSERT_EQ(trimStr(test_str), "Hi");

	// Test string with trailing whitespace
	test_str = "Bye    ";
	ASSERT_EQ(trimStr(test_str), "Bye");
	
	// Test string with only whitespaces
	test_str = "    ";
	ASSERT_EQ(trimStr(test_str), "");
}

/**
 * @test Tests the function removeStringsFromVector for removing strings from a vector.
 */
TEST(StrProcTests, RemoveStringsFromVector) {
	// Test data 1
	std::vector<std::string> to_remove = { "Hello", "World" };
	std::vector<std::string> source = { "Hello", "World", "Hi", "Bye" };
	removeStringsFromVector(source, to_remove);
	ASSERT_EQ(source.size(), 2);
	ASSERT_EQ(source[0], "Hi");
	ASSERT_EQ(source[1], "Bye");

	// Test data 2
	to_remove = { "Hi", "Bye" };
	source = { "Bye", "Hello", "World", "Hi", "Bye", "Hi" };
	removeStringsFromVector(source, to_remove);
	ASSERT_EQ(source.size(), 2);
	ASSERT_EQ(source[0], "Hello");
	ASSERT_EQ(source[1], "World");

	// Test data 3
	to_remove = { "Hello", "World", "Hi", "Bye" };
	source = { "Hello", "World", "Hi", "Bye" };
	removeStringsFromVector(source, to_remove);
	ASSERT_EQ(source.size(), 0);
}

/**
 * @test Tests the function printIndentedString for printing a string with indentation.
 */
TEST(StrProcTests, PrintIndentedString) {
	// Test data 1
	std::string message = "Hello, World!";
	std::string indent = "    ";
	testing::internal::CaptureStdout();
	printIndentedString(message, indent);
	std::string output = testing::internal::GetCapturedStdout();
	ASSERT_EQ(output, "    Hello, World!\n");

	// Test data 2
	message = "Hello, World!\nHow are you?";
	indent = "    ";
	testing::internal::CaptureStdout();
	printIndentedString(message, indent);
	output = testing::internal::GetCapturedStdout();
	ASSERT_EQ(output, "    Hello, World!\n    How are you?\n");

	// Test data 3
	message = "Hello, World!\nHow are you?\nI am fine.";
	indent = "    ";
	testing::internal::CaptureStdout();
	printIndentedString(message, indent);
	output = testing::internal::GetCapturedStdout();
	ASSERT_EQ(output, "    Hello, World!\n    How are you?\n    I am fine.\n");
}

/**
 * @test Tests the functions containsWhitespace and containsSpecialChars.
 */
TEST(StrProcTests, StrContainsChars) {
	// Test data 1
	std::string test_str = "Hello, World!";
	ASSERT_TRUE(containsWhitespace(test_str));
	ASSERT_TRUE(containsSpecialChars(test_str));

	// Test data 2
	test_str = "Hello";
	ASSERT_FALSE(containsWhitespace(test_str));
	ASSERT_FALSE(containsSpecialChars(test_str));

	// Test data 3
	test_str = "Hello@?";
	ASSERT_FALSE(containsWhitespace(test_str));
	ASSERT_TRUE(containsSpecialChars(test_str));
}

} // namespace tests
