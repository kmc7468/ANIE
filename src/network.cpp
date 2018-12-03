#include <anie/network.hpp>

#include <utility>

namespace anie
{
	network::network(const anie::device& device)
		: device_(device)
	{}
	network::network(network&& network) noexcept
		: device_(std::move(network.device_)), layers_(std::move(network.layers_))
	{}

	network& network::operator=(network&& network) noexcept
	{
		device_ = std::move(network.device_);
		layers_ = std::move(network.layers_);

		return *this;
	}

	anie::device network::device() const noexcept
	{
		return device_;
	}
}