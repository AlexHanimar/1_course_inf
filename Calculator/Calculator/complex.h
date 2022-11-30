#pragma once

#ifndef COMPLEX
#define COMPLEX

#include <concepts>
#include <stdexcept>
#include <iostream>
#include "numeric_base.h"

template<NumBase T>
class Complex
{
private:
	T re;
	T im;
public:
	Complex(void) : re{ 0 }, im{ 0 } {}
	Complex(T _re) : re{ _re }, im{ 0 } {}
	Complex(T _re, T _im) : re{ _re }, im{ _im } {}
	Complex(const Complex& other) : re{ other.re }, im{ other.im } {};
	Complex(Complex&& other) : re{ std::move(other.re) }, im{ std::move(other.im) } {}
	
	~Complex(void) = default;
	
	const Complex& operator=(const Complex& other)
	{
		if (this == &other)
			return *this;
		re = other.re;
		im = other.im;
		return *this;
	}
	const Complex& operator=(Complex&& other)
	{
		if (this == &other)
			return *this;
		re = std::move(other.re);
		im = std::move(other.im);
		return *this;
	}
	const Complex& operator=(const T& other)
	{
		re = other;
		im = 0;
		return *this;
	}
	
	bool operator==(const Complex& other) const
	{
		return (re == other.re && im == other.im);
	}

	Complex operator*(const Complex& other)
	{
		T tre = re * other.re - im * other.im;
		T tim = im * other.re + re * other.im;
		return Complex(tre, tim);
	}
	Complex operator/(const Complex& other)
	{
		T a = re;
		T b = im;
		T c = other.re;
		T d = other.im;
		if (c == 0 && d == 0)
			throw numeric_error("division_by_zero");
		T tre = a * c + b * d;
		T tim = b * c - a * d;
		T factor = c * c + d * d;
		tre = tre / factor;
		tim = tim / factor;
		return Complex(tre, tim);
	}
	Complex operator+(const Complex& other)
	{
		T tre = re + other.re;
		T tim = im + other.im;
		return Complex(tre, tim);
	}
	Complex operator+(const T& other)
	{
		return (*this) + Complex(other);
	}
	Complex operator-(void) const
	{
		return Complex(-re, -im);
	}
	Complex operator-(const Complex& other)
	{
		return (*this) + (-other);
	}

	bool isReal(void) const
	{
		return (im == 0);
	}
	bool isImg(void) const
	{
		return (re == 0);
	}

	T Re(void) const
	{
		return re;
	}
	T Im(void) const
	{
		return im;
	}

	friend std::ostream& operator<<(std::ostream& out, const Complex& number)
	{
		if (number.isReal())
			out << number.re;
		else if (number.isImg())
			out << number.im << 'I';
		else
			out << '(' << number.re << '+' << number.im << "*i)";
		return out;
	}

	static constexpr inline Complex i(void)
	{
		return Complex(0, 1);
	}
};

#endif