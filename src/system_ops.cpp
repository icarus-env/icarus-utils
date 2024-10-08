/**
 * (c) 2024 Houssem Guissouma.
 * Licensed under the BSD-3-Clause License.
 * 
 * @file utils/src/system_ops.cpp
 * @brief Definition of the helper functions for basic system operations.
 */
#include "icarus/utils/system_ops.h"

#ifdef _WIN32
    #include <windows.h>
#elif __linux__
	#include <limits.h>
	#include <unistd.h>
#endif
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace fs = std::filesystem;

namespace icarus::utils {

fs::path getExePath() {
    // Different implementation for each OS
    #ifdef _WIN32
        wchar_t exe_path_buffer[MAX_PATH];
        DWORD length = GetModuleFileNameW(NULL, exe_path_buffer, MAX_PATH);
    #elif __linux__
        char exe_path_buffer[PATH_MAX];
        ssize_t length = readlink("/proc/self/exe", exe_path_buffer, sizeof(exe_path_buffer) - 1);
        exe_path_buffer[length] = '\0';  // Null-terminate the string
    #endif

    if (length == -1) {
        throw std::runtime_error("Executable path couldn't be determined.");
    }
    return fs::path(exe_path_buffer);
}

fs::path getBinDir() {
    return getExePath().parent_path();
}

void openFile(const std::string& file_path) {
    std::string command;

    #ifdef _WIN32
        command = "start " + file_path;
    #elif __linux__
        command = "xdg-open " + file_path;
    #else
        std::cerr << "Platform not supported" << std::endl;
        return;
    #endif

    // Execute the system command and check for success
    int ret = system(command.c_str());
    if (ret != 0) {
        std::cerr << "Failed to open file: " << file_path 
                  << " with return code: " << ret << std::endl;
    }
}

std::string execCmd(const char* cmd) {
    #ifdef _WIN32
        FILE* pipe = _popen(cmd, "r");
    #elif __linux__
        FILE* pipe = popen(cmd, "r");
    #else
        std::cerr << "Unsupported operating system!" << std::endl;
        std::exit(-1);
    #endif

    if (!pipe) {
        throw std::runtime_error("Opening process pipe failed!");
    }

    std::string result;  // Initialize string variable to store the output

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

    #ifdef _WIN32
        int return_code = _pclose(pipe);
    #else
        int return_code = pclose(pipe);
    #endif

    if (return_code != 0) {
        throw std::runtime_error("Command execution failed or command not found!");
    }

    return result;
}

fs::path getAbsPath(const std::filesystem::path& dir_path, 
                         const std::string& target_path) {
    fs::path abs_target_path = fs::path(target_path);
	if (abs_target_path.is_relative()) {
		return fs::absolute(dir_path / abs_target_path);
	}
	return fs::absolute(abs_target_path);
}

std::string removeExtension(const std::string& filename) {
    size_t last_dot = filename.find_last_of('.');
    if (last_dot == std::string::npos) {
        // No extension found
        return filename;
    }
    return filename.substr(0, last_dot);
}

std::string getFileContent(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for reading: " + file_path);
    }

    std::string content((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());
    return content;
}

std::string getMergedContent(const std::vector<std::string>& file_paths) {
    std::string merged_content;
    for (const auto& file_path : file_paths) {
        merged_content += getFileContent(file_path) + "\n";
    }
    return merged_content;
}

void writeStrToFile(const std::string& str, const std::string& file_path) {
    std::ofstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing: " + file_path);
    }
    file << str;
    file.close();
}

bool isValidFile(const std::string& file_path, const std::string& extension) {
    if (!std::filesystem::exists(file_path)) {
        std::cerr << "File does not exist: \"" << file_path << "\"" << std::endl;
        return false;
    }
    else {
        if (std::filesystem::is_directory(file_path)) {
            std::cerr << "The path is a directory: \"" << file_path << "\"" << std::endl;
            return false;
        }
        if (file_path.substr(file_path.find_last_of(".") + 1) != extension) {
            std::cerr << "File does not have the correct extension: \"" 
                      << file_path << "\"" << std::endl;
            return false;
        }
    }
    return true;
}

} // namespace icarus::utils
