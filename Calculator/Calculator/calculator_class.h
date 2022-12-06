#pragma once


#ifndef CALCULATOR
#define CALCULATOR

#include "grammar.h"
#include <math.h>
// f<number_of_args><prior><type>
//sum
void f_bin_3_0(const std::vector<double>& v, double& x)
{
	x = v[0] + v[1];
}
//diff
void f_bin_3_1(const std::vector<double>& v, double& x)
{
	x = v[0] - v[1];
}
//mult
void f_bin_2_0(const std::vector<double>& v, double& x)
{
	x = v[0] * v[1];
}
//div
void f_bin_2_1(const std::vector<double>& v, double& x)
{
	if (v[1] == 0.0)
		throw token_error("division by zero");
	x = v[0] / v[1];
}
//pow
void f_bin_1_0(const std::vector<double>& v, double& x)
{
	if (v[0] < 0)
		throw token_error("error: negative power base");
	if (v[0] == 0 && v[1] < 0)
		throw token_error("error: zero raised to negative power");
	x = pow(v[0], v[1]);
}
//sin
void f_un_0_0(const std::vector<double>& v, double& x)
{
	x = sin(v[0]);
}
//cos
void f_un_0_1(const std::vector<double>& v, double& x)
{
	x = cos(v[0]);
}
//tan
void f_un_0_2(const std::vector<double>& v, double& x)
{
	x = tan(v[0]);
}
//cot
void f_un_0_3(const std::vector<double>& v, double& x)
{
	f_bin_2_1({ cos(v[0]), sin(v[0]) }, x);
}
//exp
void f_un_0_4(const std::vector<double>& v, double& x)
{
	x = exp(v[0]);
}
//negation
void f_un_0_5(const std::vector<double>& v, double& x)
{
	x = -v[0];
}

class Calculator
{
public:
	static void Main(void)
	{
		std::istream* in = &std::cin;
		std::ostream* out = &std::cout;
		std::vector<std::vector<std::string>> _operTable =
		{
			{"sin", "cos", "tan", "cot", "exp", "neg", "(", ")"},
			{"^"},
			{"*", "/"},
			{"+", "-"},
			{";", "#", "help"}
		};
		std::string _ignoredChars = " \n";
		std::map<std::string, void(*)(const std::vector<double>&, double&)> _operMap =
		{
			{"+", f_bin_3_0},
			{"-", f_bin_3_1},
			{"*", f_bin_2_0},
			{"/", f_bin_2_1},
			{"^", f_bin_1_0},
			{"sin", f_un_0_0},
			{"cos", f_un_0_1},
			{"tan", f_un_0_2},
			{"cot", f_un_0_3},
			{"exp", f_un_0_4},
			{"neg", f_un_0_5}
		};
		(*out) << "Available operations: +, -, *, /, ^, sin, cos, tan, cot, exp, neg.\n";
		(*out) << "All request sequences must end with \";\" symbol.\n";
		(*out) << "If you run into a problem and calculator doesn't say ";
		(*out) << "\"Now it should work\"\n";
		(*out) << "please, enter \";\" symbol\n";
		(*out) << "To exit, enter \"#\" symbol." << std::endl;
		Grammar<double> grammar(in, out, _operTable, _ignoredChars, _operMap);
		grammar.cycle();
	}
};

#endif