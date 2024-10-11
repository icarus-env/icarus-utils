/**
 * (c) 2024 Houssem Guissouma.
 * Licensed under the MIT License.
 * 
 * @file icarus/utils/str_processing.h
 * @brief Declaration of utility functions for string processing.
 */
#pragma once

#include <string>
#include <vector>

namespace icarus::utils {

/// @addtogroup StringProcessing
/// @{

/**
 * @brief Trims leading and trailing whitespaces from a string.
 * 
 * This function does not modify the input string and creates a new one for the result.
 * 
 * @param str The string to trim.
 * @returns The trimmed string.
 */
std::string trimStr(const std::string& str);

/**
 * @brief Checks if a string contains at least one whitespace between words.
 * 
 * @param str The string to check.
 * @returns True if the string contains whitespace, false otherwise.
 */
bool containsWhitespace(const std::string& str);

/**
 * @brief Checks if a string contains special characters.
 * 
 * Special characters are all characters that are not letters, digits, or underscores.
 * 
 * @param str The string to check.
 * @returns True if the string contains special characters, false otherwise.
 */
bool containsSpecialChars(const std::string& str);

/**
 * @brief Checks if a specific string is contained in a vector of strings.
 * 
 * @param str String to search for.
 * @param str_vec String vector to search in.
 * @returns True if the string is contained in the vector, false otherwise.
 */
bool isInVector(const std::string& str, const std::vector<std::string>& str_vec);

/**
 * @brief Splits a string into a pair of substrings using a given delimiter.
 * 
 * @param input The string to split.
 * @param delimiter The delimiter character(s) to split the string at.
 * @returns Pair of splitted substrings.
 */
std::pair<std::string, std::string> splitString(const std::string& input, 
												const char* delimiter);

/**
 * @brief Removes strings from a source vector that are contained in a second vector.
 * 
 * @param source The vector to remove strings from.
 * @param to_remove The vector containing the strings to remove.
 */
void removeStringsFromVector(std::vector<std::string>& source, 
							 const std::vector<std::string>& to_remove);

/**
 * @brief Prints a string preceded by a given indentation.
 * 
 * The indention is applied to all lines of the string in a consistent manner.
 * 
 * @param message The string to print.
 * @param indent The indentation string.
 */
void printIndentedString(const std::string& message, const std::string& indent);

/** @} */ // group StringProcessing

} // namespace icarus::utils
