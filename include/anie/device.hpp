#ifndef ANIE_HEADER_DEVICE_HPP
#define ANIE_HEADER_DEVICE_HPP
#include <anie/config.hpp>

#include <memory>
#include <tuple>
#include <boost/compute.hpp>
#include <CL/cl.h>

namespace anie
{
	using device_info = boost::compute::device;

	class ANIE_EXPORT device final
	{
	public:
		device() noexcept = default;
		device(const device_info& device_info);
		device(const device& device);
		device(device&& device) noexcept;
		~device() = default;

	public:
		device& operator=(const device& device);
		device& operator=(device&& device) noexcept;
		bool operator==(const device& device) = delete;
		bool operator!=(const device& device) = delete;

	public:
		void reset() noexcept;
		void swap(device& device) noexcept;
		bool empty() const noexcept;

	public:
		const boost::compute::device& data() const;
		const boost::compute::context& context() const;
		const boost::compute::command_queue& queue() const;
		boost::compute::command_queue& queue();

	private:
		std::shared_ptr<std::tuple<boost::compute::device, boost::compute::context, boost::compute::command_queue>> data_;
	};
}

#endif