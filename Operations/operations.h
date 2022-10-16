#pragma once
#include "operations_exceptions.h"
#include <stack>
namespace oper {
	template<typename returnType, typename argType>
	class Operation
	{
	protected:
		std::stack<argType> args;
		void checkArgs(void);
	public:
		Operation(void) {}
		Operation(std::stack<argType> args) { this->args = args; }
		void setArgs(std::stack<argType> args) { this->args = args; }
		returnType exec(void);
	};
}