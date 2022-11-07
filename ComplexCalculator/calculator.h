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
	void normalizeList(void);
	Token processList(Node<Token>*);
};

class Calculator
{

};

#endif