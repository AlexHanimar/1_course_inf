#pragma once

#ifndef NUMERIC_BASE
#define NUMERIC_BASE

#include <concepts>

template<typename T>
concept NumBase = requires(T a, T b)
{
	{a + b}		->	std::convertible_to<T>;
	{a - b}		->	std::convertible_to<T>;
	{a * b}		->	std::convertible_to<T>;
	{a / b}		->	std::convertible_to<T>;
	{1}			->	std::convertible_to<T>;
	{0}			->	std::convertible_to<T>;
	{a < b}		->	std::convertible_to<bool>;
	{a == b}	->	std::convertible_to<bool>;
};

template<typename T>
concept IntNumBase = NumBase<T> && requires (T a, T b)
{
	{a % b}		->	std::convertible_to<T>;
};

class numeric_error : public std::runtime_error {
public:
	numeric_error(const char* msg) : std::runtime_error(msg) {}
};

#endif