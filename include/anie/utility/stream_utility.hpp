#ifndef ANIE_HEADER_UTILITY_STREAM_UTILITY_HPP
#define ANIE_HEADER_UTILITY_STREAM_UTILITY_HPP
#include <anie/config.hpp>

#include <iostream>
#include <string>
#include <string_view>

namespace anie::utility
{
	ANIE_EXPORT std::string read_string(std::istream& stream);
	ANIE_EXPORT void write_string(std::ostream& stream, const std::string_view& string);
}

#endif