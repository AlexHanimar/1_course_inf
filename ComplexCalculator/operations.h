#pragma once
#ifndef OPERATIONS
#define OPERATIONS

#include "token.h"
#include <cmath>
#include <array>

template<size_t argc>
class Operation
{
public:
	static Token eval(const std::array<Token, argc>& arr);
};

class BinaryOperation : Operation<2> {};

class Sum : BinaryOperation
{
public:
	static Token eval(const std::array<Token, 2>& arr);
}; 
class Diff : BinaryOperation
{
public:
	static Token eval(const std::array<Token, 2>& arr);
};
class Mult : BinaryOperation
{
public:
	static Token eval(const std::array<Token, 2>& arr);
};
class Div : BinaryOperation
{
public:
	static Token eval(const std::array<Token, 2>& arr);
};

#endif
