#include <anie/details/kernels.hpp>

#include <boost/compute.hpp>

namespace anie::details
{
	const std::string kernel_matrix_add = BOOST_COMPUTE_STRINGIZE_SOURCE(
		__kernel void matrix_add(__global double* lhs, __global const double* rhs,
								 const uint width)
		{
			const uint y = get_global_id(0);
			
			for (uint i = 0; i < width; ++i)
			{
				lhs[width * y + i] += rhs[width * y + i];
			}
		}
	);
	const std::string kernel_matrix_sub = BOOST_COMPUTE_STRINGIZE_SOURCE(
		__kernel void matrix_sub(__global double* lhs, __global const double* rhs,
								 const uint width)
		{
			const uint y = get_global_id(0);

			for (uint i = 0; i < width; ++i)
			{
				lhs[width * y + i] -= rhs[width * y + i];
			}
		}
	);
	const std::string kernel_matrix_multiply = BOOST_COMPUTE_STRINGIZE_SOURCE(
		__kernel void matrix_multiply(__global double* dest, __global const double* src_lhs, __global const double* src_rhs,
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
	const std::string kernel_matrix_transpose = BOOST_COMPUTE_STRINGIZE_SOURCE(
		__kernel void matrix_transpose(__global double* dest, __global const double* src,
								 const uint src_width, const uint src_height)
		{
			const uint y = get_global_id(0);

			for (uint i = 0; i < src_width; ++i)
			{
				dest[i * src_height + y] = src[y * src_width + i];
			}
		}
	);
}