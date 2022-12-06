#pragma once

#ifndef GRAMMAR
#define GRAMMAR

#include "token.h"
#include "complex.h"
#include "numeric_base.h"
#include "rational.h"
#include <map>

constexpr int EXIT_CODE = 0;

template<typename T>
using funcType = void(*)(const std::vector<T>&, T&);

template<NumBase num_t>
class Grammar
{
private:
	TokenStream<num_t> ts;
	std::istream* in;
	std::ostream* out;
	std::string ignoredChars;
	std::vector<std::vector<std::string>> operTable;
	std::map<std::string, funcType<num_t>> operMap;
	struct prior {
		int nmax;
		int n;
		prior(int _nmax) : nmax{ _nmax }, n{ nmax } {}
		prior next(void)
		{
			prior res(nmax);
			res.n = (n > 0 ? n - 1 : nmax);
			return res;
		}
	};
public:
	Grammar(void) {}
	Grammar(std::istream* _in,
		std::ostream* _out,
		std::vector<std::vector<std::string>> _operTable,
		std::string _ignoredChars,
		std::map<std::string, funcType<num_t>> _operMap)
	{
		ts = TokenStream<num_t>(_in, _operTable, _ignoredChars);
		operTable = _operTable;
		ignoredChars = _ignoredChars;
		operMap = _operMap;
		in = _in;
		out = _out;
	}

	const Grammar& operator=(const Grammar& other)
	{
		ts = other.ts;
		ignoredChars = other.ignoredChars;
		operTable = other.operTable;
		operMap = other.operMap;
		in = other.in;
		out = other.out;
		return *this;
	}

	num_t expression(prior p)
	{
		try {
			if (p.n == 0) { // unary operations and primary expressions
				Token<num_t> tok;
				ts >> tok;

				if (tok.type == "(") { // processing braces
					double val = expression(p.next());
					ts >> tok;
					if (tok.type != ")")
						throw token_error("syntax error: no matching brace");
					return val;
				}

				for (std::string type : operTable[p.n]) {
					if (tok.type == type) {
						num_t res;
						operMap[type]({ expression(p) }, res);
						return res;
					}
				}
				if (tok.type == "number")
					return tok.val;
				throw token_error("syntax error: unknown grammar construction");
			}
			else { // binary operations
				double lhs = expression(p.next());
				Token<num_t> tok;
				ts >> tok;
			CycleStart:
				while (true) {
					for (std::string type : operTable[p.n]) {
						if (tok.type == type) {
							operMap[type]({ lhs, expression(p.next()) }, lhs);
							ts >> tok;
							goto CycleStart;
						}
					}
					ts.putBack(tok);
					return lhs;
				}
			}
		}
		catch (std::exception& e) {
			throw e;
		}
	}

	void cycle(void)
	{
		num_t val(0.0);
		while (true) {
			try {
				Token<num_t> tok;
				ts >> tok;
				if (tok.type == "#") {
					(*out) << "Goodbye" << std::endl;
					exit(0);
				}
				else if (tok.type == ";")
					(*out) << val << std::endl;
				else if (tok.type == "help") {
					(*out) << "Available operations: +, -, *, /, ^, sin, cos, tan, cot, exp, neg.\n";
					(*out) << "All request sequences must end with \";\" symbol.\n";
					(*out) << "If you run into a problem and calculator doesn't say ";
					(*out) << "\"Now it should work\"\n";
					(*out) << "please, enter \";\" symbol\n";
					(*out) << "To exit, enter \"#\" symbol." << std::endl;
				}
				else
				{
					ts.putBack(tok);
					val = expression(operTable.size() - 2);
				}
			}
			catch (std::exception& e) {
				(*out) << e.what() << std::endl;
				char c = (*in).get();
				while (c != ';')
					c = (*in).get();
				(*out) << "Now it should work" << std::endl;
			}
		}
	}
};

#endif