#include "operations.h"

Token Sum::eval(const std::array<Token, 2>& arr)
{
	if (!isNum(arr[0]) || !isNum(arr[1]))
		throw "err";
	char resType = NumType::Int;
	if ((arr[0].tokenType() == NumType::Float) || (arr[1].tokenType() == NumType::Float))
		resType = NumType::Float;
	return Token(resType, arr[0].tokenVal() + arr[1].tokenVal());
}
Token Diff::eval(const std::array<Token, 2>& arr)
{
	if (!isNum(arr[0]) || !isNum(arr[1]))
		throw "err";
	char resType = NumType::Int;
	if ((arr[0].tokenType() == NumType::Float) || (arr[1].tokenType() == NumType::Float))
		resType = NumType::Float;
	return Token(resType, arr[0].tokenVal() - arr[1].tokenVal());
}
Token Mult::eval(const std::array<Token, 2>& arr)
{
	if (!isNum(arr[0]) || !isNum(arr[1]))
		throw "err";
	char resType = NumType::Int;
	if ((arr[0].tokenType() == NumType::Float) || (arr[1].tokenType() == NumType::Float))
		resType = NumType::Float;
	return Token(resType, arr[0].tokenVal() * arr[1].tokenVal());
}
Token Div::eval(const std::array<Token, 2>& arr)
{
	if (!isNum(arr[0]) || !isNum(arr[1]))
		throw "err";
	if (arr[0].tokenVal() == 0.0)
		throw "err";
	char resType = NumType::Int;
	if ((arr[0].tokenType() == NumType::Float) || (arr[1].tokenType() == NumType::Float))
		resType = NumType::Float;
	long double resVal;
	if (resType == NumType::Int)
		resVal = int(arr[0].tokenVal()) / int(arr[1].tokenVal());
	else
		resVal = arr[0].tokenVal() / arr[1].tokenVal();
	return Token(resType, resVal);
}