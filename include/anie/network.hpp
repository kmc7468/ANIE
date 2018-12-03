#ifndef ANIE_HEADER_NETWORK_HPP
#define ANIE_HEADER_NETWORK_HPP
#include <anie/config.hpp>

#include <anie/device.hpp>
#include <anie/layer.hpp>

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

	public:
		anie::device device() const noexcept;

	private:
		anie::device device_;
		std::vector<layer_ptr> layers_;
	};
}

#endif