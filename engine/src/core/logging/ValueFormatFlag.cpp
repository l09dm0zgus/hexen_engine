//
// Created by vedme on 04.07.2024.
//

#include "ValueFormatFlag.hpp"
#include <spdlog/details/fmt_helper.h>

void hexen::engine::core::ValueFormatFlag::format(const spdlog::details::log_msg &l, const std::tm &, spdlog::memory_buf_t &dest)
{
	std::string_view log = l.payload.data();
	log = log.substr(0, l.payload.size());
	if (auto it = log.find('\r', 1); log[0] == '\r' && it != std::string_view::npos)
	{
		auto str = log.substr(it + 1);
		spdlog::details::fmt_helper::append_string_view(str, dest);
	}
	else
	{
		spdlog::details::fmt_helper::append_string_view(log, dest);
	}
}
std::unique_ptr<spdlog::custom_flag_formatter> hexen::engine::core::ValueFormatFlag::clone() const
{
	return std::make_unique<ValueFormatFlag>();
}