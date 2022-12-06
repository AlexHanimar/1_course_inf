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

/*using int_t = int64_t;
using base_t = Rational<int_t>;
using num_t = Complex<base_t>;*/

class token_error : public std::runtime_error
{
public:
	token_error(const char* msg) : std::runtime_error(msg) {}
};

template<NumBase num_t>
struct Token
{
	std::string type;
	num_t val;
	Token(double _val, std::string _type = "number") : type{_type}, val{_val} {}
	Token(std::string _type, num_t _val = num_t(0.0)) : type{ _type }, val{ _val } {}
	Token(void) = default;
	const Token& operator=(const Token& other)
	{
		type = other.type;
		val = other.val;
		return *this;
	}
	bool operator==(const Token& other) const = default;
	friend std::ostream& operator<<(std::ostream& out, const Token& t)
	{
		out << '<' << t.type << '|' << t.val << '>';
		return out;
	}
	static Token nullToken(void) { return Token(""); }
};

template<NumBase num_t>
class TokenStream
{
private:
	Token<num_t> buffer;
	std::istream *in;
	std::vector<std::string> typeList;
	std::string ignoredChars;
public:
	void putBack(const Token<num_t>& t)
	{
		buffer = t;
	}
	TokenStream(void) : in{ nullptr } {}
	TokenStream(std::istream* _in,
		const std::vector<std::vector<std::string> >& operTable,
		const std::string& _ignoredChars)
	{
		in = _in;
		ignoredChars = _ignoredChars;
		for (const auto& v : operTable) {
			for (const auto& w : v) {
				typeList.push_back(w);
			}
		}
		buffer = Token<num_t>::nullToken();
	}
	friend TokenStream& operator>>(TokenStream& ts, Token<num_t>& t)
	{
		if (ts.buffer != Token<num_t>::nullToken()) {
			t = ts.buffer;
			ts.buffer = Token<num_t>::nullToken();
			return ts;
		}
		std::string word = "";
		bool isNumber = false;
		bool canBeExtended = true;
		do {
			char c = (*ts.in).get();
			bool ignore = false;
			for (const char& t : ts.ignoredChars)
				ignore = ignore || (t == c);
			if (ignore)
				continue;
		Condition:
			if (isNumber) {
				if (('0' <= c && c <= '9') || c == '.') {
					word.push_back(c);
				}
				else {
					(*ts.in).putback(c);
					goto ProcessNumber;
				}
			}
			else {
				if (('0' <= c && c <= '9') || c == '.') {
					if (word.size() == 0) {
						isNumber = true;
						goto Condition;
					}
					throw token_error("syntax error");
				}
				word.push_back(c);
				canBeExtended = false;
				for (const auto& w : ts.typeList) {
					if (word == w) {
						t = Token<num_t>(word);
						return ts;
					}
					if (word.size() < w.size() && w.substr(0, word.size()) == word)
						canBeExtended = true;
				}
			}
		} while (canBeExtended);
		throw token_error("syntax error: unknown identifier");
	ProcessNumber:
		double x = std::stod(word);
		t = Token<num_t>(x);
		return ts;
	}
};

#endif