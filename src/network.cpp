#include <anie/network.hpp>

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
	network& network::operator<<(const layer_ptr& layer)
	{
		return add_layer(layer), *this;
	}
	network& network::operator<<(layer_ptr&& layer)
	{
		return add_layer(std::move(layer)), *this;
	}
	network& network::operator<<(const layer_generator_ptr& layer)
	{
		return add_layer(layer), *this;
	}

	void network::add_layer(const layer_ptr& layer)
	{
		layers_.push_back(layer);
	}
	void network::add_layer(layer_ptr&& layer)
	{
		layers_.push_back(std::move(layer));
	}
	void network::add_layer(const layer_generator_ptr& layer)
	{
		layers_.push_back((*layer)(device_));
	}

	anie::device network::device() const noexcept
	{
		return device_;
	}
}