#ifndef ANIE_HEADER_NETWORK_HPP
#define ANIE_HEADER_NETWORK_HPP
#include <anie/config.hpp>

#include <anie/device.hpp>
#include <anie/layer.hpp>

#include <memory>
#include <utility>
#include <vector>

namespace anie
{
	class ANIE_EXPORT network final
	{
	public:
		network(const anie::device& device);
		network(const network& network) = delete;
		network(network&& network) noexcept;
		~network() = default;

	public:
		network& operator=(const network& network) = delete;
		network& operator=(network&& network) noexcept;
		bool operator==(const network& network) = delete;
		bool operator!=(const network& network) = delete;
		network& operator<<(const layer_ptr& layer);
		network& operator<<(layer_ptr&& layer);
		network& operator<<(const layer_generator_ptr& layer);

	public:
		template<typename Layer_, typename... Args_>
		void add_layer(Args_&&... args)
		{
			layers_.push_back(std::make_shared<Layer_>(std::forward<Args_>(args)...));
		}
		void add_layer(const layer_ptr& layer);
		void add_layer(layer_ptr&& layer);
		void add_layer(const layer_generator_ptr& layer);

	public:
		anie::device device() const noexcept;

	private:
		anie::device device_;
		std::vector<layer_ptr> layers_;
	};
}

#endif