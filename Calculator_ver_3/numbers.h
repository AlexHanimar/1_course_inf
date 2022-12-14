#pragma once

#ifndef NUMBERS
#define NUMBERS

#include <iostream>

namespace numbers {

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
		friend std::istream& operator>>(std::istream& in, Double& _x) { return (in >> _x.x); }
		friend std::ostream& operator<<(std::ostream& out, Double& _x) { return (out << _x.x); }
		static bool can_start_with(char c)
		{
			if ('0' <= c && c <= '9')
				return true;
			if (c == '.')
				return true;
			return false;
		}
	};
}

#endif