# CMakeLists.txt of the library "icarus-utils"

# =====================================
# Library build
# =====================================
set(UTILS_LIB_SOURCES
    "data_node.cpp"
    "logging_module.cpp"
    "str_processing.cpp"
    "system_ops.cpp")

# Find external libraries
find_package(spdlog CONFIG REQUIRED)
find_package(ryml CONFIG REQUIRED)

# Add library (shared)
add_library(icarus-utils SHARED ${UTILS_LIB_SOURCES})
add_library(icarus::utils ALIAS icarus-utils)
target_include_directories(icarus-utils PUBLIC ${ICARUSUTILS_ROOT_DIR}/include)
target_link_libraries(icarus-utils
                      PUBLIC ryml::ryml spdlog::spdlog)

# =====================================
# Add test executable(s)
# =====================================
if(BUILD_TESTING)
	set(TEST_FOLDER ${ICARUSUTILS_ROOT_DIR}/tests/src)
    add_executable(icarus-utils-tests
                   "${TEST_FOLDER}/main.cpp"
                   "${TEST_FOLDER}/data_node_tests.cpp"
                   "${TEST_FOLDER}/log_module_tests.cpp"
                   "${TEST_FOLDER}/str_proc_tests.cpp"
                   "${TEST_FOLDER}/sys_ops_tests.cpp")
    target_link_libraries(icarus-utils-tests
                          PRIVATE icarus::utils GTest::gtest)
    gtest_discover_tests(icarus-utils-tests)
endif()

# =====================================
# Library installation
# =====================================
install(TARGETS icarus-utils
	    RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
# Install linked libraries (.dll/.so)
if (WIN32)
    install(IMPORTED_RUNTIME_ARTIFACTS)
endif()
