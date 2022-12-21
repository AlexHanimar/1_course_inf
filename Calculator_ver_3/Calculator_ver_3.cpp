#include <iostream>
#include "numeric_base.h"
#include "token.h"
#include <sstream>
#include "calculator.h"
#include "function_base.h"
#include "numbers.h"

using namespace std;

using dbl = numbers::Double;

struct sum : public func_base::function<dbl>
{
	void operator()(const vector<dbl>& v, dbl& x) override
	{
		x = v[0] + v[1];
	}
} _sum;
struct diff : public func_base::function<dbl>
{
	void operator()(const vector<dbl>& v, dbl& x) override
	{
		x = v[0] + (-v[1]);
	}
} _diff;
struct neg : public func_base::function<dbl>
{
	void operator()(const vector<dbl>& v, dbl& x) override
	{
		x = -v[0];
	}
} _neg;
struct mult : public func_base::function<dbl>
{
	void operator()(const vector<dbl>& v, dbl& x)
	{
		x = v[0] * v[1];
	}
} _mult; 
struct div : public func_base::function<dbl>
{
	void operator()(const vector<dbl>& v, dbl& x)
	{
		x = v[0] / v[1];
	}
} _div;

int main()
{
	vector<vector<string>> opr = {{"neg"}, {"*", "/"} , {"+", "-"}};
	map<string, func_base::function<numbers::Double>*> ot = {
		{"neg", &_neg},
		{"+", &_sum}, 
		{"-", &_diff},
		{"*", &_mult},
		{"/", &_div}
	};
	vector<char> igc = { ' ' }, enc = { ';' }, exc = {'#'};
	vector<pair<string, string>> br = { {"(", ")"}, {"[", "]"}, {"\\", "\\"}};
	calc::grammar<dbl> gr(cin, cout, opr, br, igc, enc, exc, ot);
	try {
		dbl x = gr.term({ 3, 2 });
		cout << x << endl;
	}
	catch (exception e) {
		cout << e.what() << endl;
	}
	return 0;
}