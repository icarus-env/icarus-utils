/**
 * (c) 2024 Houssem Guissouma.
 * Licensed under the BSD-3-Clause License.
 * 
 * @file tests/project_fixtures.h
 * @brief Defines constants of directory paths for test data and results.
 */
#pragma once

#include <filesystem>

#include "test_paths.h"

namespace tests {

const std::filesystem::path kTestDataDir(kTestDataDirCMake);
const std::filesystem::path kTestResutDir(kTestResutDirCMake);

} // namespace tests
