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
void Parser::setTokens(std::stack<Token> _tokens)
{
	tokens = LinkedList<Token>();
	while (!_tokens.empty()) {
		Token token = _tokens.top();
		_tokens.pop();
		tokens.pushFront(token);
	}
}

Token Parser::getToken(void)
{
	Token res = tokens.front();
	tokens.popFront();
	return res;
}
void Parser::putToken(Token t)
{
	tokens.pushFront(t);
}
Token Parser::expression(void)
{
	Token left = term();
	Token t = getToken();
	while (1) {
		switch (t.tokenType()) {
		case OperType::Sum:
			left = Sum::eval(std::array<Token, 2>{left, term()});
			t = getToken();
			break;
		case OperType::Diff:
			left = Diff::eval(std::array<Token, 2>{left, term()});
			t = getToken();
			break;
		default:
			if (t.tokenType() != 0)
				putToken(t);
			return left;
		}
	}
}
Token Parser::term(void)
{
	Token left = primary();
	Token t = getToken();
	while (1) {
		switch (t.tokenType()) {
		case OperType::Mult:
			left = Mult::eval(std::array<Token, 2>{left, primary()});
			t = getToken();
			break;
		case OperType::Div:
			left = Div::eval(std::array<Token, 2>{left, primary()});
			t = getToken();
			break;
		default:
			if (t.tokenType() != 0)
				putToken(t);
			return left;
		}
	}
}
Token Parser::primary(void)
{
	Token t = getToken();
	switch (t.tokenType()) {
	case OperType::OpBrace:
	{
		Token d = expression();
		t = getToken();
		if (t.tokenType() != OperType::ClBrace)
			throw "err";
		return d;
	}
	case NumType::Int:
		return t;
	case NumType::Float:
		return t;
	default:
		throw "err";
	}
}

void Parser::closeList(void)
{
	tokens.pushBack(Token(OperType::Endl, 0));
}

Calculator::Calculator(void)
{
	lx = Lexer();
	ps = Parser();
}

void Calculator::mainCycle(void)
{
	std::string str;
	while (1) {
		try {
			std::getline(std::cin, str);
			if (str == "q")
				exit(0);
			lx.setQuery(str);
			ps.setTokens(lx.tokenize());
			ps.closeList();
			std::cout << ps.expression().tokenVal() << std::endl;
		}
		catch (...) {
			std::cout << "something went wrong" << std::endl;
		}
	}
}