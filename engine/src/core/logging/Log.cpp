//
// Created by vedme on 02.07.2024.
//
#include "Log.hpp"
#include "CategoryFormatFlag.hpp"
#include "ValueFormatFlag.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "BufferSink.hpp"

std::shared_ptr<spdlog::logger> hexen::engine::core::logging::Log::consoleLogger;
std::shared_ptr<spdlog::logger> hexen::engine::core::logging::Log::fileLogger;
std::shared_ptr<spdlog::logger> hexen::engine::core::logging::Log::bufferLogger;
std::shared_ptr<hexen::engine::core::logging::RingBuffer<std::string>>  hexen::engine::core::logging::Log::logBuffer;

void hexen::engine::core::logging::Log::initialize()
{
	auto formatter = std::make_unique<spdlog::pattern_formatter>();
	formatter->add_flag<CategoryFormatFlag>('K')
			.add_flag<ValueFormatFlag>('V')
			.set_pattern("[%H:%M:%S %z] [%n] [%K] [%l] {%@} %V");

	spdlog::set_formatter(std::move(formatter));

	spdlog::set_level(LogLevel::trace);

	consoleLogger = spdlog::stderr_color_mt("console");

	fileLogger = spdlog::basic_logger_mt("file", "./logs/log.txt");

	auto buffSink = std::make_shared<sinks::buffer_sink_mt>();
	logBuffer = buffSink->getFormated();
	bufferLogger = std::make_shared<spdlog::logger>("bufferLogger", buffSink);

}
