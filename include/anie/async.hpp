#ifndef ANIE_HEADER_ASYNC_HPP
#define ANIE_HEADER_ASYNC_HPP

#include <future>

#define ANIE_ASYNC(expr) (std::async([&](){return(expr);}))
#define ANIE_ASYNC_VOID(expr) (std::async([&](){(expr);}))

#endif