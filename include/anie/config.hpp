#ifndef ANIE_HEADER_CONFIG_HPP
#define ANIE_HEADER_CONFIG_HPP

#if defined(ANIE_DYNAMIC) && defined(_MSC_VER)
#	ifdef ANIE_INTERNAL
#		define ANIE_EXPORT __declspec(dllexport)
#	else
#		define ANIE_EXPORT __declspec(dllimport)
#	endif
#else
#	define ANIE_EXPORT
#endif

namespace anie
{
	using arithemtic_type = double;
}

#endif