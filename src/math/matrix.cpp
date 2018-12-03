#include <anie/math/matrix.hpp>

#include <anie/details/kernels.hpp>

#include <cassert>
#include <cstdint>

namespace anie
{
	matrix::matrix(const anie::device& device) noexcept
		: device_(device)
	{}
	matrix::matrix(const anie::device& device, std::size_t size)
		: data_(size * size, device.context()), device_(device), height_(size)
	{}
	matrix::matrix(const anie::device& device, std::size_t width, std::size_t height)
		: data_(width * height, device.context()), device_(device), height_(height)
	{}
	matrix::matrix(const matrix& matrix)
		: data_(matrix.data_), device_(matrix.device_), height_(matrix.height_)
	{}
	matrix::matrix(matrix&& matrix) noexcept
		: data_(std::move(matrix.data_)), device_(std::move(matrix.device_)), height_(matrix.height_)
	{
		matrix.height_ = 0;
	}

	matrix& matrix::operator=(const matrix& matrix)
	{
		assert(device_ == matrix.device_);

		data_ = matrix.data_;
		height_ = matrix.height_;
		return *this;
	}
	matrix& matrix::operator=(matrix&& matrix) noexcept
	{
		assert(device_ == matrix.device_);

		data_ = std::move(matrix.data_);
		height_ = matrix.height_;
		return *this;
	}
	bool matrix::operator==(const matrix& matrix) const
	{
		assert(device_ == matrix.device_);

		return boost::compute::equal(data_.begin(), data_.end(), matrix.data_.begin(), matrix.data_.end(), device_.queue());
	}
	bool matrix::operator!=(const matrix& matrix) const
	{
		assert(device_ == matrix.device_);

		return !boost::compute::equal(data_.begin(), data_.end(), matrix.data_.begin(), matrix.data_.end(), device_.queue());
	}
	matrix matrix::operator*(const matrix& matrix) const
	{
		assert(device_ == matrix.device_);

		const std::size_t width = data_.size() / height_;
		const std::size_t matrix_width = matrix.data_.size() / matrix.height_;

		assert(width == matrix.height_);

		static const std::size_t global_work_size[] = { matrix_width, height_ };

		static boost::compute::program program =
			boost::compute::program::build_with_source(details::kernel_matrix_multiply, device_.context());
		boost::compute::kernel kernel = program.create_kernel("matrix_multiply");

		anie::matrix result(device_, matrix_width, height_);
		kernel.set_arg(0, result.data_);
		kernel.set_arg(1, data_);
		kernel.set_arg(2, matrix.data_);
		kernel.set_arg(3, static_cast<std::uint32_t>(width));
		kernel.set_arg(4, static_cast<std::uint32_t>(matrix_width));

		device_.queue().enqueue_nd_range_kernel(kernel, 2, nullptr, global_work_size, nullptr);
		return result;
	}

	std::size_t matrix::width() const noexcept
	{
		return data_.size() / height_;
	}

	void matrix::copy_to(std::vector<arithemtic_type>& vector) const
	{
		if (vector.size() < data_.size())
		{
			vector.resize(data_.size());
		}

		copy_to(vector.data());
	}

	anie::device matrix::device() const noexcept
	{
		return device_;
	}
	std::size_t matrix::height() const noexcept
	{
		return height_;
	}
}