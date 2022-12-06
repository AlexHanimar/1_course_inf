#pragma once

#ifndef NUMERIC_BASE
#define NUMERIC_BASE

#include <concepts>

template<typename T>
concept NumBase = requires(T a, T b, double c)
{
	{a + b}		->	std::convertible_to<T>;
	{a - b}		->	std::convertible_to<T>;
	{a * b}		->	std::convertible_to<T>;
	{a / b}		->	std::convertible_to<T>;
	{a == b}	->	std::convertible_to<bool>;
	//{double(a)}	->	std::same_as<double>;
	
	//{T(c)}		->	std::convertible_to<T>;
};

template<typename T>
concept CompNumBase = NumBase<T> && requires(T a, T b)
{
	{a < b}		->	std::convertible_to<bool>;
};

template<typename T>
concept IntNumBase = CompNumBase<T> && requires (T a, T b)
{
	{a % b}		->	std::convertible_to<T>;
};

class numeric_error : public std::runtime_error {
public:
	numeric_error(const char* msg) : std::runtime_error(msg) {}
};

#endif