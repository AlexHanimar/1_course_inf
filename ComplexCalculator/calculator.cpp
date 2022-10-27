#include "calculator.h"

Parser::Parser(void) : query{ "" } {}
Parser::Parser(std::string _query) : query{ _query } {}

void Parser::setQuery(std::string _query)
{
	query = _query;
}

std::stack<Token> Parser::tokenize(void)
{
	std::stack<Token> res;
	TokenStream ts(res);
	std::string curWord = "";
	bool dot = false;
	for (char c : query) {
		if (!isAllowed(c)) // skip trash symbols
			continue;
		if (c == '.' && dot) {
			query.clear();
			throw std::string("Incorrect number format");
		}
		if (c == '.') {
			dot = true;
			curWord += c;
			continue;
		}
		if ('0' <= c && c <= '9') {
			curWord += c;
			continue;
		}
		if (!curWord.empty()) {
			long double val = std::stod(curWord);
			curWord.clear();
			char tokenType = NumType::Int;
			if (dot)
				tokenType = NumType::Float;
			Token num(tokenType, val);
			ts << num;
			dot = false;
		}
		char tokenType = c;
		Token op(tokenType);
		ts << op;
	}
	if (!curWord.empty()) {
		long double val = std::stod(curWord);
		curWord.clear();
		char tokenType = NumType::Int;
		if (dot)
			tokenType = NumType::Float;
		Token num(tokenType, val);
		ts << num;
	}
	return res;
}