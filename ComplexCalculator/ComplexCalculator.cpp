#include <iostream>
#include "calculator.h"

using namespace std;

int main()
{
	Lexer lx("1+(1+1)+1");
	stack<Token> tokens = lx.tokenize();
	Parser ps(tokens);
	ps.printTokenList(cout);
	return 0;
}