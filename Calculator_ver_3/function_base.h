#pragma once

#ifndef FUNC_BASE
#define FUNC_BASE

#include <concepts>
#include <vector>

namespace func_base {

	class function_error : public std::runtime_error
	{
	public:
		function_error(const char* msg) : std::runtime_error(msg) {}
	};

	template<typename T, typename Q>
	concept func_type = requires(T a, const std::vector<Q>&v, Q & b)
	{
		{a(v, b)};
	};

	template<typename T>
	class function
	{
	public:
		virtual void operator()(const std::vector<T>&, T&) = 0;
	};

}

#endif