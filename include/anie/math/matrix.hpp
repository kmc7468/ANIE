#ifndef ANIE_HEADER_MATH_MATRIX_HPP
#define ANIE_HEADER_MATH_MATRIX_HPP
#include <anie/config.hpp>

#include <anie/device.hpp>

#include <cstddef>
#include <vector>
#include <boost/compute.hpp>

namespace anie
{
	class ANIE_EXPORT matrix final
	{
	public:
		explicit matrix(const anie::device& device) noexcept;
		matrix(const anie::device& device, std::size_t size);
		matrix(const anie::device& device, std::size_t width, std::size_t height);
		matrix(const matrix& matrix);
		matrix(matrix&& matrix) noexcept;
		~matrix() = default;

	public:
		matrix& operator=(const matrix& matrix);
		matrix& operator=(matrix&& matrix) noexcept;
		bool operator==(const matrix& matrix) const;
		bool operator!=(const matrix& matrix) const;
		matrix operator*(const matrix& matrix) const;

	public:
		std::size_t width() const noexcept;

		void copy_to(std::vector<arithemtic_type>& vector) const;
		template<typename Iterator_>
		void copy_to(Iterator_ start) const
		{
			copy_to(start, data_.size());
		}
		template<typename Iterator_>
		void copy_to(Iterator_ start, std::size_t size) const
		{
			boost::compute::copy(data_.begin(), data_.begin() + size, start, device_.queue());
		}

	public:
		anie::device device() const noexcept;
		std::size_t height() const noexcept;

	public:
		boost::compute::vector<arithemtic_type> data_;
		anie::device device_;
		std::size_t height_;
	};
}

#endif