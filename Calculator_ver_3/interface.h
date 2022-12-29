#pragma once

#ifndef INTERFACE
#define INTERFACE

#include "calculator.h"
#include "functions.h"
#include "numbers.h"

class calc_interface
{
public:
	void start(void)
	{
		typedef numbers::Double dbl;
		std::vector<std::vector<std::string>> op_by_prior;
		std::map<std::string, func_base::function<dbl>*> op_table;
		functions::func_list<dbl>::set_data(op_by_prior, op_table);
		std::vector<char> ig_ch = { ' ', '\n' };
		std::vector<char> en_ch = { ';' };
		std::vector<char> ex_ch = { '#' };
		std::vector<std::pair<std::string, std::string>> braces = { {"(", ")"}, {"[", "]"}, {"{", "}"} };
		calc::calculator<dbl> clc(std::cin, std::cout, op_by_prior, braces, ig_ch, en_ch, ex_ch, op_table);
		std::cout << "This is basic grammar-based infix calculator.\n" <<
			"Every line of input must end with ';'.\n" <<
			"Currently only these operations are supported:\n" <<
			"\tsin\n\tcos\n\ttan\n\tcot\n\texp\n\tln\n\tneg (neg(x) is equivalent to -x)\n\t+\n\t-\n\t*\n\t/\n\t^\n" <<
			"In case of error, type ';' in console to flush input.\n" << 
			"Type '#' to stop work.\n";
		clc.main_cycle();
	}
};

#endif