#include <anie/details/kernels.hpp>

#include <boost/compute.hpp>

namespace anie::details
{
	const std::string kernel_matrix_multiply = BOOST_COMPUTE_STRINGIZE_SOURCE(
		__kernel void matrix_multiply(__global double* dest, __global double* src_lhs, __global double* src_rhs,
									  const uint src_lhs_width, const uint src_rhs_width)
		{
			const uint width = get_global_size(0);
			const uint x = get_global_id(0);
			const uint y = get_global_id(1);
			const uint index = y * width + x;
			
			double sum = 0.;

			for (uint i = 0; i < src_lhs_width; ++i)
			{
				sum += src_lhs[src_lhs_width * y + i] * src_rhs[src_rhs_width * i + x];
			}

			dest[index] = sum;
		}
	);
}