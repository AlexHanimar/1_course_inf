#include "calculator.h"

Lexer::Lexer(void) : query{ "" } {}
Lexer::Lexer(std::string _query) : query{ _query } {}

void Lexer::setQuery(std::string _query)
{
	query = _query;
}
std::stack<Token> Lexer::tokenize(void)
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

Parser::Parser(void) : tokens{ LinkedList<Token>() } {}
Parser::Parser(std::stack<Token> _tokens)
{
	tokens = LinkedList<Token>();
	while (!_tokens.empty()) {
		Token token = _tokens.top();
		_tokens.pop();
		tokens.pushFront(token);
	}
}
void Parser::printTokenList(std::ostream& out)
{
	tokens.printList(out);
}
void Parser::normalizeList(void)
{
	Node<Token>* cur = tokens.begin()->next;
	while (cur != tokens.end()) {
		switch (cur->val.tokenType())
		{
		case NumType::Float:case NumType::Int:
			if (cur->next != tokens.end() && isNum(cur->next->val))
				throw std::string("Incorrect format");
			break;
			// обработать операции: поглотить минусы
			// напр. ('i', 2) ('*', 0) ('-', 0) ('i', 1) -> ('i', 2) ('*', 0) ('i', -1)
		}
	}
}
Token Parser::processList(Node<Token>* begin)
{
	if (begin == tokens.end())
		return nullToken();

	return nullToken();
}