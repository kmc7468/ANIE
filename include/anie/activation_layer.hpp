#ifndef ANIE_HEADER_ACTIVATION_LAYER_HPP
#define ANIE_HEADER_ACTIVATION_LAYER_HPP
#include <anie/config.hpp>

#include <anie/device.hpp>
#include <anie/layer.hpp>

#include <iostream>

namespace anie
{
	class ANIE_EXPORT activation_layer : public layer
	{
	public:
		activation_layer(const activation_layer& layer) = delete;
		activation_layer(activation_layer&& layer) = delete;
		virtual ~activation_layer() override = default;

	protected:
		activation_layer(const anie::device& device) noexcept;

	public:
		activation_layer& operator=(const activation_layer& layer) = delete;
		activation_layer& operator=(activation_layer&& layer) = delete;
		bool operator==(const activation_layer& layer) = delete;
		bool operator!=(const activation_layer& layer) = delete;

	public:
		virtual void write(std::ostream& stream) const override;
		virtual void read(std::istream& stream) override;
	};
}

#endif