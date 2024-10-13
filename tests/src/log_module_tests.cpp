/**
 * (c) 2024 Houssem Guissouma.
 * Licensed under the BSD-3-Clause License.
 *
 * @file tests/src/log_module_tests.cpp
 * @brief Implementation of the fixture LogModuleTests and definition of its test cases.
 */
#include <memory>

#include <gtest/gtest.h>
#include <spdlog/sinks/null_sink.h>

// Module under test
#include "icarus/utils/logging_module.h"


namespace icarus {

/**
 * @brief Fixture for testing the LoggingModule class.
 */
class LogModuleTests : public ::testing::Test {
protected:
    // Setup method for initializing resources
    void SetUp() override {
        // Create a logger with a null sink to prevent actual output
        auto null_sink = std::make_shared<spdlog::sinks::null_sink_mt>();
        mock_logger = std::make_shared<spdlog::logger>("mock_logger", null_sink);
        logger_name = "test_logger";
    }

    // Teardown method for cleaning up resources
    void TearDown() override {
        // Drop the logger from spdlog registry
        spdlog::drop(logger_name);
        spdlog::drop("mock_logger");
    }

    std::shared_ptr<spdlog::logger> mock_logger;
    std::string logger_name;
};

// Test the constructor that takes a logger name
TEST_F(LogModuleTests, ConstructorWithLoggerName) {
    // Test default colored output
    LoggingModule logging_module(logger_name);
    EXPECT_NE(logging_module.getLogger(), nullptr);
    EXPECT_EQ(logging_module.getLoggerName(), logger_name);
}

// Test the constructor that takes an existing logger
TEST_F(LogModuleTests, ConstructorWithExistingLogger) {
    LoggingModule logging_module(mock_logger);
    EXPECT_EQ(logging_module.getLogger(), mock_logger);
    EXPECT_EQ(logging_module.getLoggerName(), "mock_logger");
}

// Test setting a logger
TEST_F(LogModuleTests, SetLogger) {
    LoggingModule logging_module(logger_name);
    logging_module.setLogger(mock_logger);
    EXPECT_EQ(logging_module.getLogger(), mock_logger);
    EXPECT_EQ(logging_module.getLoggerName(), "mock_logger");
}

/**
 * @test Tests the setting of the global log level.
 */
TEST_F(LogModuleTests, SetGlobalLogLevel) {
    LoggingModule::setGlobalLogLevel(spdlog::level::debug);

    // Check if the global log level was set correctly
    EXPECT_EQ(spdlog::default_logger()->level(), spdlog::level::debug);
}

// Test logger is dropped from the global registry on destruction
TEST_F(LogModuleTests, LoggerDroppedOnDestruction) {
    {
        LoggingModule logging_module(logger_name);
        EXPECT_NE(spdlog::get(logger_name), nullptr);
    }
    // After destruction, the logger should be dropped from the registry
    EXPECT_EQ(spdlog::get(logger_name), nullptr);
}

} // namespace icarus
