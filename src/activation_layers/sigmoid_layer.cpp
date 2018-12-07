#include <anie/activation_layers/sigmoid_layer.hpp>

#include <cassert>
#include <memory>
#include <boost/compute.hpp>

namespace anie
{
	sigmoid_layer::sigmoid_layer(const anie::device& device) noexcept
		: activation_layer(device), u_(device)
	{}

	std::string_view sigmoid_layer::name() const noexcept
	{
		return "Sigmoid";
	}

	matrix sigmoid_layer::forward(const matrix& z) const
	{
		assert(device() == z.device());

		static BOOST_COMPUTE_FUNCTION(arithemtic_type, sigmoid, (const double x),
		{
			return 1. / (1. + exp(-x));
		});
		
		matrix result(z);
		boost::compute::transform(result.begin(), result.end(), result.begin(), sigmoid, device().queue());

		u_ = z;
		return result;
	}
	matrix sigmoid_layer::backward(const matrix& d)
	{
		assert(device() == d.device());

		static BOOST_COMPUTE_FUNCTION(arithemtic_type, dsigmoid, (const double x),
		{
			const double y = 1. / (1. + exp(-x));
			return y * (1. - y);
		});

		matrix result(u_);
		boost::compute::transform(result.begin(), result.end(), result.begin(), dsigmoid, device().queue());
				
		return result;
	}
}

namespace anie
{
	layer_ptr sigmoid_layer_generator::operator()(const anie::device& device) const
	{
		return std::make_shared<sigmoid_layer>(device);
	}

	layer_generator_ptr sigmoid()
	{
		return std::make_shared<sigmoid_layer_generator>();
	}
	layer_ptr sigmoid(const anie::device& device)
	{
		return std::make_shared<sigmoid_layer>(device);
	}
}