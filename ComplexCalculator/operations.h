#pragma once
#ifndef OPERATIONS
#define OPERATIONS

#include "token.h"
#include <cmath>

class Operation
{
protected:
	std::stack<Token> args;
public:
	Operation(void);
	Operation(std::stack<Token>&);
	Operation(std::initializer_list<Token>&);
	void setArgs(std::stack<Token>&);
	void setArgs(std::initializer_list<Token>&);
	virtual Token exec(void) = 0;
};

class UnaryOperation : public Operation
{
public:
	UnaryOperation(std::stack<Token>&);
	UnaryOperation(std::initializer_list<Token>&);
	virtual Token exec(void) = 0;
};

class BinaryOperation : public Operation
{
public:
	BinaryOperation(std::stack<Token>&);
	BinaryOperation(std::initializer_list<Token>&);
	virtual Token exec(void) = 0;
};

class Sum : public BinaryOperation
{
public:
	Token exec(void);
};
class Diff : public BinaryOperation
{
public:
	Token exec(void);
};
class Mult : public BinaryOperation
{
public:
	Token exec(void);
};
class Div : public BinaryOperation
{
public:
	Token exec(void);
};

#endif
