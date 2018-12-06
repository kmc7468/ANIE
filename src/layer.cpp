#include <anie/layer.hpp>

namespace anie
{
	layer::layer(const anie::device& device) noexcept
		: device_(device)
	{}

	anie::device layer::device() const noexcept
	{
		return device_;
	}
}