#include <iostream>
#include "numeric_base.h"
#include "token.h"
#include <sstream>

using namespace std;

class Double
{
	double x;
public:
	Double(void) : x{ 0 } {}
	Double(double _x) : x{ _x } {}
	Double operator+(const Double& _x) { return Double(x + _x.x); }
	Double operator-() const { return Double(-x); }
	Double operator*(const Double& _x) { return Double(x * _x.x); }
	Double operator/(const Double& _x) { return Double(x / _x.x); }
	bool operator==(const Double& _x) { return (x == _x.x); }
	double mod(void) { return (x >= 0 ? x : -x); }
	static Double zero(void) { return Double(); }
	friend istream& operator>>(istream& in, Double& _x) { return (in >> _x.x); }
	friend ostream& operator<<(ostream& out, Double& _x) { return (out << _x.x); }
	static bool can_start_with(char c)
	{
		if ('0' <= c && c <= '9')
			return true;
		if (c == '.')
			return true;
		return false;
	}
};

int main()
{
	token::token_stream<Double> ts(cin, { "+", "-", "*", "/", "sin"});
	return 0;
}