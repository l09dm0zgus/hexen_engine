//
// Created by vedme on 02.07.2024.
//
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#pragma once

#include "CategoryFormatFlag.hpp"
#include "ValueFormatFlag.hpp"
#include "spdlog/sinks/basic_file_sink.h"
#include <source_location>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include "BufferSink.hpp"

#ifdef NDEBUG
	#define HEXEN_DEFAULT_LOG_CALL(loc, level, msg, ...)                                                                                                  \
		{                                                                                                                                                 \
			hexen::engine::core::logging::Log::getFileLogger()->log(spdlog::source_loc(loc.file, loc.line, SPDLOG_FUNCTION), level, msg, __VA_ARGS__);    \
			hexen::engine::core::logging::Log::getBufferLogger()->log(spdlog::source_loc(loc.file, loc.line, SPDLOG_FUNCTION), level, msg, __VA_ARGS__);  \
			hexen::engine::core::logging::Log::getConsoleLogger()->log(spdlog::source_loc(loc.file, loc.line, SPDLOG_FUNCTION), level, msg, __VA_ARGS__); \
		}

#else
	#define HEXEN_DEFAULT_LOG_CALL(loc, level, msg, ...)                                                                                                  \
		{                                                                                                                                                 \
			hexen::engine::core::logging::Log::getFileLogger()->log(spdlog::source_loc(loc.file, loc.line, SPDLOG_FUNCTION), level, msg, __VA_ARGS__);    \
			hexen::engine::core::logging::Log::getBufferLogger()->log(spdlog::source_loc(loc.file, loc.line, SPDLOG_FUNCTION), level, msg, __VA_ARGS__);  \
		}
#endif
/*#define HEXEN_DEFAULT_LOG_CALL(loc, level, msg, ...)                                                                                                  \
	{                                                                                                                                                 \
		hexen::engine::core::logging::Log::getFileLogger()->log(spdlog::source_loc(loc.file, loc.line, SPDLOG_FUNCTION), level, msg, __VA_ARGS__);    \
		hexen::engine::core::logging::Log::getConsoleLogger()->log(spdlog::source_loc(loc.file, loc.line, SPDLOG_FUNCTION), level, msg, __VA_ARGS__); \
		hexen::engine::core::logging::Log::getBufferLogger()->log(spdlog::source_loc(loc.file, loc.line, SPDLOG_FUNCTION), level, msg, __VA_ARGS__);  \
	}*/

using LogLevel = spdlog::level::level_enum;

namespace hexen::engine::core::logging
{
	//Temp solution

	struct location
	{
		const char *file;
		int line;
	};

	static constexpr const char * coreCategory = "Core";
	static constexpr const char * systemsCategory = "Systems";
	static constexpr const char * graphicsCategory =  "Graphics";
	static constexpr const char * entityCategory = "Entity";
	static constexpr const char * defaultCategory =  "Default";

	class Log
	{
	private:
		static std::shared_ptr<spdlog::logger> consoleLogger;

		static std::shared_ptr<spdlog::logger> fileLogger;

		static std::shared_ptr<spdlog::logger> bufferLogger;

		static std::shared_ptr<hexen::engine::core::logging::RingBuffer<std::string>> logBuffer;

	public:
		static void initialize();

		inline static std::shared_ptr<spdlog::logger> &getConsoleLogger()
		{
			return consoleLogger;
		}

		inline static std::shared_ptr<spdlog::logger> &getFileLogger()
		{
			return fileLogger;
		}

		inline static std::shared_ptr<spdlog::logger> &getBufferLogger()
		{
			return bufferLogger;
		}

		inline static std::shared_ptr<hexen::engine::core::logging::RingBuffer<std::string>> &getLogBuffer()
		{
			return logBuffer;
		}

		template<typename... Args>
		static void call(location loc, const char * category, LogLevel level, std::string const &msg, Args... args)
		{
			HEXEN_DEFAULT_LOG_CALL(loc, level, '\r' + std::string(category) + '\r' + msg, args...)
		}
	};
}// namespace hexen::engine::core::logging

#define HEXEN_LOG_CALL(log_category, log_level, ...)                                                         \
	{                                                                                                        \
		hexen::engine::core::logging::Log::call({__FILE__, __LINE__}, log_category, log_level, __VA_ARGS__); \
	}
