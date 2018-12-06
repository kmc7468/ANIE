#include <anie/activation_layer.hpp>

#include <anie/utility/stream_utility.hpp>

#include <cassert>

namespace anie
{
	activation_layer::activation_layer(const anie::device& device) noexcept
		: layer(device)
	{}

	void activation_layer::write(std::ostream& stream) const
	{
		utility::write_string(stream, name());
	}
	void activation_layer::read(std::istream&)
	{}
}