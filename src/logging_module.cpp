/**
 * (c) 2024 Houssem Guissouma.
 * Licensed under the BSD-3-Clause license.
 *
 * @file icarus-utils/src/logging_module.cpp
 * @brief Implementation of the class LoggingModule.
 */
#include "icarus/utils/logging_module.h"

#include <iostream>

#include "spdlog/sinks/stdout_color_sinks.h"

namespace icarus {

LoggingModule::LoggingModule(const std::string& logger_name, bool is_colored)
	: logger_(spdlog::stdout_color_mt(logger_name)) {
	if (!is_colored) {
		logger_ = std::make_shared<spdlog::logger>(logger_name);
	}
}

LoggingModule::LoggingModule(std::shared_ptr<spdlog::logger> logger)
	: logger_(logger) {}

LoggingModule::~LoggingModule() {
	if (logger_) {
		spdlog::drop(logger_->name());
	}
}

std::shared_ptr<spdlog::logger> LoggingModule::getLogger() const {
	return logger_;
}

void LoggingModule::setLogger(std::shared_ptr<spdlog::logger> logger) {
	logger_ = logger;
}

void LoggingModule::setGlobalLogLevel(spdlog::level::level_enum level) {
	spdlog::apply_all([&](std::shared_ptr<spdlog::logger> logger) {
		logger->set_level(level);
	});
}

} // namespace icarus
