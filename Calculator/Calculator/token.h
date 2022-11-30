#pragma once

#ifndef TOKEN
#define TOKEN

#include "complex.h"
#include "rational.h"
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <iostream>

using int_t = int64_t;
using base_t = Rational<int_t>;
using num_t = Complex<base_t>;

class token_error : public std::runtime_error
{
public:
	token_error(const char* msg) : std::runtime_error(msg) {}
};

extern std::vector<std::vector<std::string> > operTable;
extern std::string ignoredChars;

struct Token
{
	std::string type;
	num_t val;
	Token(std::string _type, num_t _val = base_t(1));
	Token(void) = default;
	bool operator==(const Token& other) const = default;
	const Token& operator=(const Token& other)
	{
		type = other.type;
		val = other.val;
		return *this;
	}
};

const inline Token nullToken(void)
{
	return Token("", base_t(0));
}

class TokenStream
{
private:
	Token buffer;
	std::istream *in;
	std::vector<std::string> typeList;
public:
	TokenStream(std::istream* _in);
	friend TokenStream& operator>>(TokenStream& ts, Token& t);
	void putBack(const Token& t);
};

#endif