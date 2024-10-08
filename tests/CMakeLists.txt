# CMakeLists.txt of the test executable "icarus-utils-tests"
if(BUILD_TESTING)
    add_executable(icarus-utils-tests
                   "src/main.cpp"
                   "src/data_node_tests.cpp"
                   "src/str_proc_tests.cpp"
                   "src/sys_ops_tests.cpp")
    target_link_libraries(icarus-utils-tests
                          PRIVATE icarus::utils GTest::gtest)
    gtest_discover_tests(icarus-utils-tests)
endif()