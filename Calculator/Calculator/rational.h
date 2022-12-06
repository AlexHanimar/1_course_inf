#pragma once

#ifndef RATIONAL
#define RATIONAL

#include <concepts>
#include <stdexcept>
#include <iostream>
#include "numeric_base.h"

template<IntNumBase T>
class Rational
{
private:
	T num;
	T den;
	struct GCD 
	{
		T operator()(T a, T b)
		{
			if (a < b)
				return operator()(b, a);
			if (b == 0)
				return a;
			return operator()(b, a % b);
		}
	} gcd;
public:

	// using narrowing conversion to check if number is whole, so disabling warning about it 
#pragma warning(push)
#pragma warning(disable:4244)
	Rational(double x) 
	{
		T _den = 1;
		while (T(x) != x) {
			_den = _den * 10;
			x = x * 10;
		}
		T _num = x;
		num = x;
		den = _den;
		T d = gcd(num, den);
		num = num / d;
		den = den / d;
	}
#pragma warning(pop)

	Rational(T _num = 0, T _den = 1) {
		if (_den == 0) throw numeric_error("division_by_zero");
		T _gcd = gcd(_num, _den);
		num = _num / _gcd;
		den = _den / _gcd;
	}
	Rational(const Rational& other) :
		num{ other.num }, 
		den{ other.den } {
	}
	Rational(Rational&& other) :
		num{ std::move(other.num) }, 
		den{ std::move(other.den) } {}
	
	~Rational(void) = default;
	
	// conversion from double

	const Rational& operator=(const Rational& other)
	{
		if (this == &other)
			return *this;
		num = other.num;
		den = other.den;
		return *this;
	}
	const Rational& operator=(Rational&& other)
	{
		if (this == &other)
			return *this;
		num = std::move(other.num);
		den = std::move(other.den);
		return *this;
	}
	const Rational& operator=(const T& other)
	{
		num = other;
		den = 1;
		return *this;
	}

	bool operator==(const Rational& other) const
	{
		return (num == other.num && den == other.den);
	}
	bool operator<(const Rational& other) const
	{
		return (num * other.den < other.num* den);
	}

	Rational operator*(const Rational& other) const
	{
		return Rational(num * other.num, den * other.den);
	}
	Rational operator/(const Rational& other) const
	{
		if (other == Rational(0.0))
			throw numeric_error("division_by_zero");
		return Rational(num * other.den, den * other.num);
	}
	Rational operator+(const Rational& other) const
	{
		T tden = den * other.den;
		T tnum1 = num * other.den;
		T tnum2 = den * other.num;
		return Rational(tnum1 + tnum2, tden);
	}
	Rational operator-(void) const
	{
		return Rational(-num, den);
	}
	Rational operator-(const Rational& other) const
	{
		return (*this) + (-other);
	}

	friend std::ostream& operator<<(std::ostream& out, const Rational& number)
	{
		out << number.num;
		if (!(number.den == 1))
			out << '/' << number.den;
		return out;
	}

	bool isWhole(void) { return (den == 1); }

	operator double()
	{
		return double(num) / double(den);
	}
};

#endif
