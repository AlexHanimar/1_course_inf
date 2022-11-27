#pragma once
 
#ifndef TOKEN
#define TOKEN

#include <iostream>
#include <stack>
#include <string>

enum OperType
{
	Sum = '+',
	Diff = '-',
	Mult = '*',
	Div = '/',
	OpBrace = '(',
	ClBrace = ')',
	Endl = ';',
	Exit = 'q'
};

enum NumType
{
	Int = 'i',
	Float = 'd'
};

bool isAllowed(char c);

class Token
{
private:
	char type;
	long double val;
public:
	Token(void);
	Token(char _type);
	Token(char _type, long double _val);
	char tokenType(void) const;
	long double tokenVal(void) const;
	friend std::ostream& operator<<(std::ostream&, Token&);
	friend class TokenStream;
};

const Token nullToken(void);

bool isOper(Token t);
bool isNum(Token t);

class TokenStream
{
private:
	std::stack<Token>* st;
	Token lastAdded;
public:
	TokenStream(void);
	TokenStream(std::stack<Token>&);
	void open(std::stack<Token>&);
	void close(void);
	Token get(void);
	void put(Token t);
	void putBack(void);
};

TokenStream& operator<<(TokenStream& ts, Token& t);
TokenStream& operator>>(TokenStream& ts, Token& t);

std::ostream& operator<<(std::ostream& out, Token& t);

#endif