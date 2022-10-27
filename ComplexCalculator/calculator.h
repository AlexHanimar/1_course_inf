#pragma once
#ifndef CALCULATOR
#define CALCULATOR

#include "token.h"
#include "operations.h"

class Parser
{
private:
	std::string query;
public:
	Parser(void);
	Parser(std::string _query);
	void setQuery(std::string _query);
	std::stack<Token> tokenize(void);
};

class Calculator
{

};

#endif