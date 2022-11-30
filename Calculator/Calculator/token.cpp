#include "token.h"

Token::Token(std::string _type, num_t _val) : type{ _type }, val{ _val } {}

TokenStream::TokenStream(std::istream* _in)
{
	in = _in;
	for (const auto& v : operTable) {
		for (const auto& w : v) {
			typeList.push_back(w);
		}
	}
}

TokenStream& operator>>(TokenStream& ts, Token& t)
{
	if (ts.buffer != nullToken()) {
		t = ts.buffer;
		ts.buffer = nullToken();
		return ts;
	}
	std::string word = "";
	bool isNumber = false;
	bool canBeExtended = true;
	do {
		char c = (*ts.in).get();
		bool ignore = false;
		for (const char& t : ignoredChars)
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
					t = Token(word);
					return ts;
				}
				if (word.size() < w.size() && w.substr(0, word.size()) == word)
					canBeExtended = true;
			}
		}
	} while (canBeExtended);
	throw token_error("syntax error");
	ProcessNumber:
	bool dot = false;
	for (char c : word) {
		if (c == '.') {
			if (dot)
				throw token_error("syntax error");
			dot = true;
		}
	}
	int_t num = 0;
	dot = false;
	int_t den = 1;
	for (char c : word) {
		if (c != '.') {
			num = num * 10 + c - '0';
			if (dot)
				den = den * 10;
		}
		if (c == '.')
			dot = true;
	}
	t = Token("number", base_t(num, den));
	return ts;
}

void TokenStream::putBack(const Token& t)
{
	buffer = t;
}