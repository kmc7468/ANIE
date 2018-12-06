#include <anie/utility/stream_utility.hpp>

#include <cstdint>

namespace anie::utility
{
	ANIE_EXPORT std::string read_string(std::istream& stream)
	{
		std::string result;
		std::uint64_t length;
		
		stream.read(reinterpret_cast<char*>(&length), sizeof(length));
		result.resize(length);
		stream.read(result.data(), static_cast<std::streamsize>(length));

		return result;
	}
	ANIE_EXPORT void write_string(std::ostream& stream, const std::string_view& string)
	{
		const std::uint64_t length = static_cast<std::uint64_t>(string.size());
		
		stream.write(reinterpret_cast<const char*>(&length), sizeof(length));
		stream.write(string.data(), static_cast<std::streamsize>(length));
	}
}