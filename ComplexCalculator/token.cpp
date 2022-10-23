#include "token.h"

Token::Token(void) : type{ '\0' }, val{ 0 } {}
Token::Token(char _type) : type{ _type }, val{ 0 } {}
Token::Token(char _type, long double _val) : type{ _type }, val{ _val } {}

char Token::tokenType(void)
{
	return type;
}

long double Token::tokenVal(void)
{
	return val;
}

TokenStream::TokenStream(void) : lastAdded{ Token() }, st{ nullptr } {}
TokenStream::TokenStream(std::stack<Token>& _st) : st{ &_st } {}
Token TokenStream::get(void)
{
	if (!st) {
		throw std::string("No stream source");
	}
	if (st->empty()) {
		throw std::string("TokenStream empty");
	}
	Token res = st->top();
	st->pop();
	return res;
}
void TokenStream::put(Token t)
{
	if (!st) {
		throw std::string("No stream source");
	}
	st->push(t); 
	lastAdded = t;
}
void TokenStream::putBack(void)
{
	if (!st) {
		throw std::string("No stream source");
	}
	if (lastAdded.type == '\0') {
		throw std::string("TokenStream : nothing to put back");
	}
	st->push(lastAdded);
	lastAdded = Token();
}

void TokenStream::open(std::stack<Token>& st)
{
	this->st = &st;
}

void TokenStream::close(void)
{
	this->st = nullptr;
}

TokenStream& operator<<(TokenStream& ts, Token& t)
{
	ts.put(t);
	return ts;
}

TokenStream& operator>>(TokenStream& ts, Token& t)
{
	t = ts.get();
	return ts;
}

std::ostream& operator<<(std::ostream& out, Token& t)
{
	return out << '(' << t.type << '|' << t.val << ')';
}