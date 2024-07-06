//
// Created by vedme on 02.07.2024.
//
#include "Log.hpp"
#include "CategoryFormatFlag.hpp"
#include "ValueFormatFlag.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> hexen::engine::core::logging::Log::consoleLogger;
std::shared_ptr<spdlog::logger> hexen::engine::core::logging::Log::fileLogger;

void hexen::engine::core::logging::Log::initialize()
{
	auto formatter = std::make_unique<spdlog::pattern_formatter>();
	formatter->add_flag<CategoryFormatFlag>('K')
			.add_flag<ValueFormatFlag>('V')
			.set_pattern("[%H:%M:%S %z] [%n] [%K] [%l] {%@} %V");
	spdlog::set_formatter(std::move(formatter));
	consoleLogger = spdlog::stderr_color_mt("console");
	fileLogger = spdlog::basic_logger_mt("file", "/logs/log.txt");
	consoleLogger->set_level(spdlog::level::trace);
	fileLogger->set_level(spdlog::level::trace);
}
