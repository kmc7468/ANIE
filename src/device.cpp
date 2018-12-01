#include <anie/device.hpp>

namespace anie
{
	device::device(const device_info& device_info)
	{
		boost::compute::device device_info_copied = device_info;
		boost::compute::context context(device_info_copied);
		boost::compute::command_queue queue(context, device_info_copied);

		data_ = std::make_shared<decltype(data_)::element_type>(
			std::make_tuple(std::move(device_info_copied), std::move(context), std::move(queue)));
	}
	device::device(const device& device)
		: data_(device.data_)
	{}
	device::device(device&& device) noexcept
		: data_(std::move(device.data_))
	{}

	device& device::operator=(const device& device)
	{
		data_ = device.data_;
		return *this;
	}
	device& device::operator=(device&& device) noexcept
	{
		data_ = std::move(device.data_);
		return *this;
	}

	void device::reset() noexcept
	{
		data_.reset();
	}
	void device::swap(device& device) noexcept
	{
		data_.swap(device.data_);
	}
	bool device::empty() const noexcept
	{
		return data_ == nullptr;
	}

	const boost::compute::device& device::data() const
	{
		return std::get<0>(*data_);
	}
	const boost::compute::context& device::context() const
	{
		return std::get<1>(*data_);
	}
	const boost::compute::command_queue& device::queue() const
	{
		return std::get<2>(*data_);
	}
	boost::compute::command_queue& device::queue()
	{
		return std::get<2>(*data_);
	}

	std::vector<device_info> get_devices()
	{
		return boost::compute::system::devices();
	}
	device get_default_device()
	{
		static device dev = boost::compute::system::default_device();
		return dev;
	}
}