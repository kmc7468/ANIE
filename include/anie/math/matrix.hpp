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
		using iterator = boost::compute::vector<arithemtic_type>::iterator;
		using const_iterator = boost::compute::vector<arithemtic_type>::const_iterator;
		using reverse_iterator = boost::compute::vector<arithemtic_type>::reverse_iterator;
		using const_reverse_iterator = boost::compute::vector<arithemtic_type>::const_reverse_iterator;

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
		matrix operator+(const matrix& matrix) const;
		matrix operator-(const matrix& matrix) const;
		matrix operator*(const matrix& matrix) const;
		matrix& operator+=(const matrix& matrix);
		matrix& operator-=(const matrix& matrix);

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
		void copy_from(const std::vector<arithemtic_type>& vector);
		template<typename Iterator_>
		void copy_from(Iterator_ start, Iterator_ end)
		{
			boost::compute::copy(start, end, data_.begin(), device_.queue());
		}

		matrix transpose() const;

		iterator begin();
		const_iterator begin() const;
		const_iterator cbegin() const;
		iterator end();
		const_iterator end() const;
		const_iterator cend() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		const_reverse_iterator crbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;
		const_reverse_iterator crend() const;

	public:
		anie::device device() const noexcept;
		std::size_t height() const noexcept;

	private:
		boost::compute::vector<arithemtic_type> data_;
		anie::device device_;
		std::size_t height_;
	};
}

#endif