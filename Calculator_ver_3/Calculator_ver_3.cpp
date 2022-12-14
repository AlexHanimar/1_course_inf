#include <iostream>
#include "numeric_base.h"
#include "token.h"
#include <sstream>
#include "calculator.h"
#include "function_base.h"
#include "numbers.h"

using namespace std;

int main()
{
	token::token_stream<numbers::Double> ts(cin, { "+", "-", "*", "/", "sin"});
	vector<vector<string>> opr;
	map<string, func_base::function<numbers::Double>*> ot;
	vector<char> igc, enc, exc;
	vector<pair<string, string>> br;
	calc::grammar<numbers::Double> gr(cin, cout, opr, br, igc, enc, exc, ot);
	return 0;
}