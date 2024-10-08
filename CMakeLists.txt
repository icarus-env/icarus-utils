# CMakeLists.txt of the project "icarus-utils"
cmake_minimum_required(VERSION 3.22)

# =======================================================
# vcpkg configuration (must be before project())
# =======================================================
get_filename_component(VCPKG_ROOT "$ENV{VCPKG_ROOT}" ABSOLUTE)
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

option(BUILD_TESTING "Install test dependencies")
if(BUILD_TESTING)
    list(APPEND VCPKG_MANIFEST_FEATURES "test")
endif()

# ========================================
# Project configuration
# ========================================
project(icarus-utils
        DESCRIPTION "General-purpose modules for abstraction and utility used in the ICARUS environment.")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(ICARUS-UTILS_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Directories for build output and installation
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# ========================================
# Test configuration
# ========================================
if(BUILD_TESTING)
    include(CTest)
    find_package(GTest CONFIG REQUIRED)
    include(GoogleTest)

    # Code coverage is only supported by GCC
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        add_compile_options(--coverage)
        add_link_options(--coverage)
    endif()

    # Configure test data path and results directory
    set(TEST_DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests/test_data")
    set(TEST_RESULT_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_results")
    file(MAKE_DIRECTORY ${TEST_RESULT_DIR})
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/tests/test_paths.h.in 
                   ${CMAKE_CURRENT_SOURCE_DIR}/tests/src/test_paths.h)
endif()

# =====================================
# Add component(s)
# =====================================
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

# =====================================
# Add test executable(s)
# =====================================
if(BUILD_TESTING)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif()
