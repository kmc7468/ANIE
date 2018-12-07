#ifndef ANIE_HEADER_ACTIVATION_LAYERS_SIGMOID_LAYER_HPP
#define ANIE_HEADER_ACTIVATION_LAYERS_SIGMOID_LAYER_HPP
#include <anie/config.hpp>

#include <anie/activation_layer.hpp>
#include <anie/device.hpp>
#include <anie/layer.hpp>
#include <anie/math/matrix.hpp>

#include <iostream>
#include <string_view>

namespace anie
{
	class ANIE_EXPORT sigmoid_layer final : public activation_layer
	{
	public:
		explicit sigmoid_layer(const anie::device& device) noexcept;
		sigmoid_layer(const sigmoid_layer& layer) = delete;
		sigmoid_layer(sigmoid_layer&& layer) = delete;
		virtual ~sigmoid_layer() override = default;

	public:
		sigmoid_layer& operator=(const sigmoid_layer& layer) = delete;
		sigmoid_layer& operator=(sigmoid_layer&& layer) = delete;
		bool operator==(const sigmoid_layer& layer) = delete;
		bool operator!=(const sigmoid_layer& layer) = delete;

	public:
		virtual std::string_view name() const noexcept override;

		virtual matrix forward(const matrix& z) const override;
		virtual matrix backward(const matrix& d) override;

	private:
		mutable matrix u_;
	};

	class ANIE_EXPORT sigmoid_layer_generator final : public layer_generator
	{
	public:
		sigmoid_layer_generator() noexcept = default;
		sigmoid_layer_generator(const sigmoid_layer_generator& generator) = delete;
		sigmoid_layer_generator(sigmoid_layer_generator&& generator) = delete;
		virtual ~sigmoid_layer_generator() override = default;

	public:
		sigmoid_layer_generator& operator=(const sigmoid_layer_generator& generator) = delete;
		sigmoid_layer_generator& operator=(sigmoid_layer_generator&& generator) = delete;
		bool operator==(const sigmoid_layer_generator& generator) = delete;
		bool operator!=(const sigmoid_layer_generator& generator) = delete;
		virtual layer_ptr operator()(const anie::device& device) const override;
	};

	layer_generator_ptr sigmoid();
	layer_ptr sigmoid(const anie::device& device);
}

#endif