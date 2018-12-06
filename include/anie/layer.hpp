#ifndef ANIE_HEADER_LAYER_HPP
#define ANIE_HEADER_LAYER_HPP
#include <anie/config.hpp>

#include <anie/device.hpp>
#include <anie/math/matrix.hpp>

#include <iostream>
#include <memory>
#include <string_view>

namespace anie
{
	class ANIE_EXPORT layer
	{
	public:
		layer(const layer& layer) = delete;
		layer(layer&& layer) = delete;
		virtual ~layer() = default;

	protected:
		layer(const anie::device& device) noexcept;

	public:
		layer& operator=(const layer& layer) = delete;
		layer& operator=(layer&& layer) = delete;
		bool operator==(const layer& layer) = delete;
		bool operator!=(const layer& layer) = delete;

	public:
		virtual std::string_view name() const noexcept = 0;
		virtual void write(std::ostream& stream) const = 0;
		virtual void read(std::istream& stream) = 0;

		virtual matrix forward(const matrix& z) const = 0;
		virtual matrix backward(const matrix& d) = 0;

	public:
		anie::device device() const noexcept;

	private:
		anie::device device_;
	};

	using layer_ptr = std::shared_ptr<layer>;
}

#endif