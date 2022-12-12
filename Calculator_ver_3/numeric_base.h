#pragma once

#ifndef NUMERIC_BASE
#define NUMERIC_BASE

#include <concepts>
#include <iostream>

namespace numeric_base {

	template<typename T>
	concept io_compatible = requires(std::istream in, std::ostream out, T a) {
		{in >> a};
		{out << a};
	};

	template<typename T>
	concept num_type = io_compatible<T> && requires(T a, T b, char c) {
		{a + b}                -> std::same_as<T>;
		{-a}                   -> std::same_as<T>;
		{a * b}                -> std::same_as<T>;
		{a / b}                -> std::same_as<T>;
		{a.mod()}              -> std::convertible_to<double>;
		{T::zero()}            -> std::same_as<T>;
		{a == b}               -> std::same_as<bool>;
		{T::can_start_with(c)} -> std::same_as<bool>;
	};

}

#endif