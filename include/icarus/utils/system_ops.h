/**
 * (c) 2024 Houssem Guissouma.
 * Licensed under the MIT License.
 *
 * @file icarus/utils/system_ops.h
 * @brief Declaration of utility functions for basic system operations.
 */
#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace icarus::utils {

/// @addtogroup SystemOps
/// @{

/**
 * @brief Gets the path of the current running executable.
 *
 * @returns Full path of the current executable.
 * @throws std::runtime_error If the path could not be determined.
 */
std::filesystem::path getExePath();

/**
 * @brief Returns the path of the directory containing the current executable.
 *
 * @returns Full path of the directory containing the current executable.
 */
std::filesystem::path getBinDir();

/**
 * @brief Opens a file with the default application associated with its file type.
 *
 * @param file_path Path of the file to open as string.
 */
void openFile(const std::string& file_path);

/**
 * @brief Executes a system command and returns its output as a string.
 *
 * @param cmd Input command as char array.
 * @returns Output of the command as string.
 * @throws std::runtime_error If the process pipe could not be opened or the command failed.
 */
std::string execCmd(const char* cmd);

/**
 * @brief Gets the absolute path of a relative or absolute target path.
 *
 * @param dir_path Source directory path, used as reference for a relative target path.
 * @param target_path Target path (relative to the source directory or absolute).
 * @returns Absolute path of the target path.
 */
std::filesystem::path getAbsPath(const std::filesystem::path& dir_path,
			         const std::string& target_path);

/**
 * @brief Removes the extension from a given filename.
 *
 * @param filename Input filename.
 * @returns Filename without the extension.
 */
std::string removeExtension(const std::string& filename);

/**
 * @brief Gets the content of a file as a string.
 *
 * @param file_path Path of the file to read.
 * @returns Content of the file as a string.
 * @throws std::runtime_error If the file could not be read.
 */
std::string getFileContent(const std::string& file_path);

/**
 * @brief Merges the content of multiple files into a single string and returns it.
 *
 * @param file_paths Paths of the files to merge.
 * @returns Merged content of the files as a string.
 */
std::string getMergedContent(const std::vector<std::string>& file_paths);

/**
 * @brief Writes a string to a local file.
 *
 * @param str Input string to write.
 * @param file_path Path of the file to write the string to.
 */
void writeStrToFile(const std::string& str, const std::string& file_path);

/**
 * @brief Checks if a file at a given path is a valid file with a specified extension.
 *
 * @param file_path Path of the file to check.
 * @param extension Extension of the file to check for, e.g., "txt" or "yaml".
 * @returns True if the file exists and has the correct extension, false otherwise.
 */
bool isValidFile(const std::string& file_path, const std::string& extension);

/** @} */ // group SystemOps

} // namespace icarus::utils
