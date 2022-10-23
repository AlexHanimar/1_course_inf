#include "operations.h"

Operation::Operation(void) {}
Operation::Operation(std::stack<Token>& st) : args{ st } {}
Operation::Operation(std::initializer_list<Token>& l) : args{ l } {}
void Operation::setArgs(std::stack<Token>& st) { args = st; }
void Operation::setArgs(std::initializer_list<Token>& l) { args = std::stack<Token>{ l }; }

UnaryOperation::UnaryOperation(std::stack<Token>& st)
{
	if (st.size() != 1) {
		throw std::string("Incorrect number of arguments : expected 1 Tokens, got " + std::to_string(st.size()));
	}
	args = st;
}

UnaryOperation::UnaryOperation(std::initializer_list<Token>& l)
{
	if (l.size() != 1) {
		throw std::string("Incorrect number of arguments : expected 1 Tokens, got " + std::to_string(l.size()));
	}
	args = std::stack<Token>{l};
}

BinaryOperation::BinaryOperation(std::stack<Token>& st)
{
	if (st.size() != 2) {
		throw std::string("Incorrect number of arguments : expected 2 Tokens, got " + std::to_string(st.size()));
	}
	args = st;
}

BinaryOperation::BinaryOperation(std::initializer_list<Token>& l)
{
	if (l.size() != 2) {
		throw std::string("Incorrect number of arguments : expected 2 Tokens, got " + std::to_string(l.size()));
	}
	args = std::stack<Token>{ l };
}

Token Sum::exec(void)
{
	TokenStream ts(args);
	char resType = NumType::Int;
	Token arg1, arg2;
	ts >> arg2 >> arg1;
	switch (arg1.tokenType()) {
	case NumType::Float:
		resType = NumType::Float;
		break;
	case NumType::Int:
		break;
	default:
		throw std::string("Incorrect type : expected NumType, got " + arg1.tokenType());
	}
	switch (arg2.tokenType()) {
	case NumType::Float:
		resType = NumType::Float;
		break;
	case NumType::Int:
		break;
	default:
		throw std::string("Incorrect type : expected NumType, got " + arg2.tokenType());
	}
	switch (resType) {
	case NumType::Float:
		return Token(resType, arg1.tokenVal() + arg2.tokenVal());
	case NumType::Int:
		return Token(resType, floor(arg1.tokenVal()) + floor(arg2.tokenVal()));
	default:
		throw std::string("Something went wrong");
	}
}
Token Diff::exec(void)
{
	TokenStream ts(args);
	char resType = NumType::Int;
	Token arg1, arg2;
	ts >> arg2 >> arg1;
	switch (arg1.tokenType()) {
	case NumType::Float:
		resType = NumType::Float;
		break;
	case NumType::Int:
		break;
	default:
		throw std::string("Incorrect type : expected NumType, got " + arg1.tokenType());
	}
	switch (arg2.tokenType()) {
	case NumType::Float:
		resType = NumType::Float;
		break;
	case NumType::Int:
		break;
	default:
		throw std::string("Incorrect type : expected NumType, got " + arg2.tokenType());
	}
	switch (resType) {
	case NumType::Float:
		return Token(resType, arg1.tokenVal() - arg2.tokenVal());
	case NumType::Int:
		return Token(resType, floor(arg1.tokenVal()) - floor(arg2.tokenVal()));
	default:
		throw std::string("Something went wrong");
	}
}
Token Mult::exec(void)
{
	TokenStream ts(args);
	char resType = NumType::Int;
	Token arg1, arg2;
	ts >> arg2 >> arg1;
	switch (arg1.tokenType()) {
	case NumType::Float:
		resType = NumType::Float;
		break;
	case NumType::Int:
		break;
	default:
		throw std::string("Incorrect type : expected NumType, got " + arg1.tokenType());
	}
	switch (arg2.tokenType()) {
	case NumType::Float:
		resType = NumType::Float;
		break;
	case NumType::Int:
		break;
	default:
		throw std::string("Incorrect type : expected NumType, got " + arg2.tokenType());
	}
	switch (resType) {
	case NumType::Float:
		return Token(resType, arg1.tokenVal() * arg2.tokenVal());
	case NumType::Int:
		return Token(resType, floor(arg1.tokenVal()) * floor(arg2.tokenVal()));
	default:
		throw std::string("Something went wrong");
	}
}
Token Div::exec(void)
{
	TokenStream ts(args);
	char resType = NumType::Int;
	Token arg1, arg2;
	ts >> arg2 >> arg1;
	switch (arg1.tokenType()) {
	case NumType::Float:
		resType = NumType::Float;
		break;
	case NumType::Int:
		break;
	default:
		throw std::string("Incorrect type : expected NumType, got " + arg1.tokenType());
	}
	switch (arg2.tokenType()) {
	case NumType::Float:
		resType = NumType::Float;
		break;
	case NumType::Int:
		break;
	default:
		throw std::string("Incorrect type : expected NumType, got " + arg2.tokenType());
	}
	if (arg2.tokenVal() == 0) {
		throw std::string("Division by zero");
	}
	switch (resType) {
	case NumType::Float:
		return Token(resType, arg1.tokenVal() / arg2.tokenVal());
	case NumType::Int:
		return Token(resType, int(arg1.tokenVal()) / int(arg2.tokenVal()));
	default:
		throw std::string("Something went wrong");
	}
}