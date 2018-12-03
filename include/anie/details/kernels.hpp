#ifndef ANIE_HEADER_DETAILS_KERNERLS_HPP
#define ANIE_HEADER_DETAILS_KERNERLS_HPP
#include <anie/config.hpp>

#include <string_view>

namespace anie::details
{
	ANIE_EXPORT	extern const std::string kernel_matrix_add;
	ANIE_EXPORT	extern const std::string kernel_matrix_sub;
	ANIE_EXPORT extern const std::string kernel_matrix_multiply;
	ANIE_EXPORT extern const std::string kernel_matrix_transpose;
}

#endif