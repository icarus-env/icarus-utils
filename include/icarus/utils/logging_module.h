/**
 * (c) 2024 Houssem Guissouma.
 * Licensed under the BSD-3-Clause license.
 *
 * @file include/icarus/utils/logging_module.h
 * @brief Definition of the class LoggingModule.
 */
#pragma once

#include <memory>
#include <string>

#include <spdlog/spdlog.h>

namespace icarus {

/**
 * @brief Module of the ICARUS environment with logging capabilities.
 */
class LoggingModule {
public:
	/**
	 * @brief Creates a logging module with a given configuration.
	 * 
	 * @param logger_name Name of the logger.
	 * @param is_colored (optional) Flag to enable colored output.
	 */
	LoggingModule(const std::string& logger_name, bool is_colored = true);

	/**
	 * @brief Creates a logging module from an existing logger.
	 * 
	 * @param logger Shared pointer to the existing logger.
	 */
	explicit LoggingModule(std::shared_ptr<spdlog::logger> logger);

	/**
	 * @brief Destroys the logging module and drops the spdlog logger from the global registry.
	 */
	~LoggingModule();

	/**
	 * @brief Returns the logger of the module.
	 * 
	 * @return Shared pointer to the logger of the module.
	 */
	std::shared_ptr<spdlog::logger> getLogger() const;

	/**
	 * @brief Sets the logger of the GUI module.
	 * 
	 * @param logger Logger to be set as shared pointer.
	 */
	void setLogger(std::shared_ptr<spdlog::logger> logger);

	/**
	 * @brief Sets the log level of all loggers in the running program.
	 * 
	 * @param level Log level to be set.
	 */
	static void setGlobalLogLevel(spdlog::level::level_enum level);

protected:
	/// spdlog logger of the module.
	std::shared_ptr<spdlog::logger> logger_ = nullptr;
};

} // namespace icarus