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

#ifdef NDEBUG
	#define HEXEN_DEFAULT_LOG_CALL(loc, level, msg, ...)                                                                                                  \
		{                                                                                                                                                 \
			hexen::engine::core::logging::Log::getFileLogger()->log(spdlog::source_loc(loc.file, loc.line, SPDLOG_FUNCTION), level, msg, __VA_ARGS__);    \
			hexen::engine::core::logging::Log::getConsoleLogger()->log(spdlog::source_loc(loc.file, loc.line, SPDLOG_FUNCTION), level, msg, __VA_ARGS__); \
		}
#else
	#define HEXEN_DEFAULT_LOG_CALL(loc, level, msg, ...)                                                                                               \
		{                                                                                                                                              \
			hexen::engine::core::logging::Log::getFileLogger()->log(spdlog::source_loc(loc.file, loc.line, SPDLOG_FUNCTION), level, msg, __VA_ARGS__); \
		}
#endif

using LogLevel = spdlog::level::level_enum;

namespace hexen::engine::core::logging
{
	//Temp solution

	enum class Category
	{
		core = 0,
		systems = 1,
		graphics = 2,
		entity = 3,
		editor = 4
	};

	struct location
	{
		const char *file;
		int line;
	};

	static constexpr auto coreCategory = std::make_pair<Category, const char *>(Category::core, "Core");
	static constexpr auto systemsCategory = std::make_pair<Category, const char *>(Category::systems, "Systems");
	static constexpr auto graphicsCategory = std::make_pair<Category, const char *>(Category::graphics, "Graphics");
	static constexpr auto entityCategory = std::make_pair<Category, const char *>(Category::entity, "Entity");
	static constexpr auto editorCategory = std::make_pair<Category, const char *>(Category::editor, "Editor");

	class Log
	{
	private:
		static std::shared_ptr<spdlog::logger> consoleLogger;

		static std::shared_ptr<spdlog::logger> fileLogger;

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

		template<typename... Args>
		static void call(location loc, std::pair<Category, const char *> category, LogLevel level, std::string const &msg, Args... args)
		{
			HEXEN_DEFAULT_LOG_CALL(loc, level, '\r' + std::string(category.second) + '\r' + msg, args...)
		}
	};
}// namespace hexen::engine::core::logging

#define HEXEN_LOG_CALL(log_category, log_level, ...)                                                         \
	{                                                                                                        \
		hexen::engine::core::logging::Log::call({__FILE__, __LINE__}, log_category, log_level, __VA_ARGS__); \
	}
