/**
 * (c) 2024 Houssem Guissouma.
 * Licensed under the BSD-3-Clause License.
 * 
 * @file utils/src/str_processing.cpp
 * @brief Definition of the helper functions for string processing.
 */
#include "icarus/utils/str_processing.h"

#include <algorithm>
#include <iostream>
#include <sstream>

namespace icarus::utils {

std::string trimStr(const std::string& str) {
    // Find the first non-whitespace character
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) {
        return "";
    }

    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

bool containsWhitespace(const std::string& str) {
    // Find any whitespace character that is not at the beginning or end of the string
    auto it = std::find_if(str.begin(), str.end(), [](unsigned char ch) {
        return std::isspace(ch);
        });

    return it != str.end();
}

bool containsSpecialChars(const std::string& str) {
    return std::find_if(str.begin(), str.end(), [](unsigned char ch) {
        // Allow letters, digits, and underscores
        return !(std::isalnum(ch) || ch == '_' || ch == '-');
        }) != str.end();
}

bool isInVector(const std::string& str, const std::vector<std::string>& str_vec) {
    return std::find(str_vec.begin(), str_vec.end(), str) != str_vec.end();
}

std::pair<std::string, std::string> splitString(const std::string& input, 
                                                const char* delimiter) {
    // Find the position of the delimiter character
    size_t pos = input.find(delimiter);

    // Handle error: no delimiter found in the string
    if (pos == std::string::npos) {
        return std::make_pair("", "");
    }

    // Extract the parts before and after the delimiter
    std::string port_name = input.substr(0, pos);
    std::string field_name = input.substr(pos + 1);

    return std::make_pair(port_name, field_name);
}

void removeStringsFromVector(std::vector<std::string>& source, 
                             const std::vector<std::string>& to_remove) {
    source.erase(
        std::remove_if(source.begin(), source.end(), [&to_remove](const std::string& str) {
            return std::find(to_remove.begin(), to_remove.end(), str) != to_remove.end();
            }),
        source.end()
    );
}

void printIndentedString(const std::string& message, const std::string& indent) {
    std::istringstream stream(message);
    std::string line;
    bool first_line = true;

    while (std::getline(stream, line)) {
        if (first_line) {
            std::cout << indent << line << std::endl;
            first_line = false;
        } else {
            std::cout << std::string(indent.size(), ' ') << line << std::endl;
        }
    }
}

} // namespace icarus::utils
