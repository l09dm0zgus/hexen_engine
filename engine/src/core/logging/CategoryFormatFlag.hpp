//
// Created by vedme on 04.07.2024.
//



#pragma once

#include <spdlog/pattern_formatter.h>

namespace hexen::engine::core
{
	class CategoryFormatFlag: public spdlog::custom_flag_formatter
	{
		public:
			void format(const spdlog::details::log_msg &, const std::tm &, spdlog::memory_buf_t &dest) override;

			std::unique_ptr<spdlog::custom_flag_formatter> clone() const override;
	};
}
