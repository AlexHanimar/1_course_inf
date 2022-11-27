#pragma once
#ifndef CALCULATOR
#define CALCULATOR

#include "token.h"
#include "operations.h"
#include "linked_list.h"

class Lexer
{
private:
	std::string query;
public:
	Lexer(void);
	Lexer(std::string);
	void setQuery(std::string);
	std::stack<Token> tokenize(void);
};

class Parser
{
private:
	LinkedList<Token> tokens;
public:
	Parser(void);
	Parser(std::stack<Token>);
	void printTokenList(std::ostream&);
	void setTokens(std::stack<Token>);

	void closeList(void);

	Token getToken(void);
	void putToken(Token t);
	Token expression(void);
	Token term(void);
	Token primary(void);
};

class Calculator
{
private:
	Lexer lx;
	Parser ps;
public:
	Calculator(void);
	void mainCycle(void);
};

#endif