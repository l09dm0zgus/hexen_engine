//
// Created by vedme on 04.07.2024.
//

#pragma once

#include <spdlog/pattern_formatter.h>

namespace hexen::engine::core
{
	class ValueFormatFlag: public spdlog::custom_flag_formatter
	{
		void format(const spdlog::details::log_msg &, const std::tm &, spdlog::memory_buf_t &dest) override;

		[[nodiscard]] std::unique_ptr<spdlog::custom_flag_formatter> clone() const override;
	};
}
