#pragma once
#include "operations_exceptions.h"
#include <vector>
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
				throw op_except::tooFewArguments;
			else if (args.size() > argNum)
				throw op_except::tooManyArguments;
			this->args = args;
		}
		void setArgs(const std::vector<argType>& args)
		{
			if (args.size() < argNum)
				throw op_except::tooFewArguments;
			else if (args.size() > argNum)
				throw op_except::tooManyArguments;
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

	class BitwiseInvertion : public UnaryOperation<int, int>
	{
	public:
		int exec(void)
		{
			return ~args.back();
		}
	};

	class Increment : public UnaryOperation<void, int>
	{
	public:
		void exec(void)
		{
			++args.back();
		}
	};

	class Decrement : public UnaryOperation<void, int>
	{
	public:
		void exec(void)
		{
			--args.back();
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
}