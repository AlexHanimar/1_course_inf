#include <string>
#include <cmath>
#include "calculator_operations.h"

double calc::sum(double a, double b)
{
	return a + b;
}

double calc::diff(double a, double b)
{
	return a - b;
}

double calc::mult(double a, double b)
{
	return a * b;
}

double calc::div_d(double a, double b)
{
	if (b == 0)
		throw std::string("in calc::div_d: division by zero");
	return a / b;
}

double calc::pow(double a, double b)
{
	if (a < 0)
		throw std::string("in calc::pow: negative power base");
	return std::pow(a, b);
}