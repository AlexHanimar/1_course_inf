#pragma once
#ifndef OPERATIONS
#define OPERATIONS

#include <vector>
#include <string>
namespace oper {
	template<typename returnType, typename argType, size_t argNum>
	class Operation
	{
	public:
		std::vector<argType> args;
		Operation(void) {}
		Operation(const std::vector<argType>& args)
		{
			if (args.size() < argNum)
				throw std::string("too few arguments");
			else if (args.size() > argNum)
				throw std::string("too many arguments");
			this->args = args;
		}
		void setArgs(const std::vector<argType>& args)
		{
			if (args.size() < argNum)
				throw std::string("too few arguments");
			else if (args.size() > argNum)
				throw std::string("too many arguments");
			this->args = args;
		}
		virtual returnType exec(void) = 0;
	};

	template<typename returnType, typename argType>
	class UnaryOperation : public Operation<returnType, argType, 1> {};

	class UnaryPlus : public UnaryOperation<double, double>
	{
	public:
		double exec(void)
		{
			return args.back();
		}
	};

	class UnaryMinus : public UnaryOperation<double, double>
	{
	public:
		double exec(void)
		{
			return -args.back();
		}
	};

	class BitInvertion : public UnaryOperation<int, int>
	{
	public:
		int exec(void)
		{
			return ~args.back();
		}
	};

	class Negation : public UnaryOperation<bool, bool>
	{
	public:
		bool exec(void)
		{
			return !args.back();
		}
	};

	template<typename returnType, typename argType>
	class BinaryOperation : public Operation<returnType, argType, 2> {};

	class Sum : public BinaryOperation<double, double>
	{
	public:
		double exec(void)
		{
			return args[0] + args[1];
		}
	};

	class Diff : public BinaryOperation<double, double>
	{
	public:
		double exec(void)
		{
			return args[0] - args[1];
		}
	};

	class Mult : public BinaryOperation<double, double>
	{
	public:
		double exec(void)
		{
			return args[0] * args[1];
		}
	};

	class DivD : public BinaryOperation<double, double>
	{
	public:
		double exec(void)
		{
			if (args[1] == 0)
				throw std::string("division by zero");
			return args[0] / args[1];
		}
	};
}

#endif