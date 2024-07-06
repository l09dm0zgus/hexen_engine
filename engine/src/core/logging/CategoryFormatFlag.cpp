//
// Created by vedme on 04.07.2024.
//
#include "CategoryFormatFlag.hpp"
#include <algorithm>
#include <string_view>
#include <spdlog/details/fmt_helper.h>

void hexen::engine::core::CategoryFormatFlag::format(const spdlog::details::log_msg &l, const tm &, spdlog::memory_buf_t &dest)
{
	std::string_view log = l.payload.data();
	log = log.substr(0, l.payload.size());
	if (auto it = log.find('\r', 1); log[0] == '\r' && it != std::string_view::npos)
	{
		auto str = log.substr(1, it - 1);
		spdlog::details::fmt_helper::append_string_view(str, dest);
	}
}
std::unique_ptr<spdlog::custom_flag_formatter> hexen::engine::core::CategoryFormatFlag::clone() const
{
	return std::make_unique<CategoryFormatFlag>();
}
