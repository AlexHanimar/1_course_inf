#pragma once

#ifndef FUNCTIONS
#define FUNCTIONS

#include "numeric_base.h"
#include "function_base.h"

namespace functions
{

	constexpr double EPS = 1e-8;
	constexpr double PI = 3.1415926535;

	template<numeric_base::num_type T>
		requires func_base::func_type<func_base::function<T>, T>
	class func_list
	{
	public:
		struct sum : public func_base::function<T> {
			void operator()(const std::vector<T>& vec, T& x) override {
				x = vec[0] + vec[1];
			}
		};
		struct diff : public func_base::function<T> {
			void operator()(const std::vector<T>& vec, T& x) override {
				x = vec[0] + -vec[1];
			}
		};
		struct mult : public func_base::function<T> {
			void operator()(const std::vector<T>& vec, T& x) override {
				x = vec[0] * vec[1];
			}
		};
		struct div : public func_base::function<T> {
			void operator()(const std::vector<T>& vec, T& x) override {
				if (vec[1] == T::zero())
					throw std::runtime_error("division by zero");
				x = vec[0] / vec[1];
			}
		};
		struct neg : public func_base::function<T> {
			void operator()(const std::vector<T>& vec, T& x) override {
				x = -vec[0];
			}
		};
		struct sin : public func_base::function<T> {
			void operator()(const std::vector<T>& vec, T& x) override {
				T mlt = vec[0];
				T term = mlt;
				x = T::zero();
				int i = 1;
				while (term.mod() > EPS) {
					x = x + term;
					term = term / (i + 1);
					term = term / (i + 2);
					i += 2;
					term = term * mlt * mlt;
					term = -term;
				}
			}
		};
		struct cos : public func_base::function<T> {
			void operator()(const std::vector<T>& vec, T& x) override {
				T mlt = vec[0];
				T term = T(1);
				x = T::zero();
				int i = 0;
				while (term.mod() > EPS) {
					x = x + term;
					term = term / (i + 1);
					term = term / (i + 2);
					i += 2;
					term = term * mlt * mlt;
					term = -term;
				}
			}
		};
		struct tan : public func_base::function<T> {
			void operator()(const std::vector<T>& vec, T& x){
				sin _sin;
				cos _cos;
				T x1, x2;
				_sin(vec, x1);
				_cos(vec, x2);
				div _div;
				_div({ x1, x2 }, x);
			}
		};
		struct cot : public func_base::function<T> {
			void operator()(const std::vector<T>& vec, T& x) {
				sin _sin;
				cos _cos;
				T x1, x2;
				_sin(vec, x1);
				_cos(vec, x2);
				div _div;
				_div({ x2, x1 }, x);
			}
		};
		struct exp : public func_base::function<T> {
			void operator()(const std::vector<T>& vec, T& x) override {
				T mlt = vec[0];
				T term = 1;
				x = T::zero();
				int i = 0;
				while (term.mod() > EPS) {
					x = x + term;
					term = term * mlt / (i + 1);
					i++;
				}
			}
		};
		struct ln : public func_base::function<T> {
			void operator()(const std::vector<T>& vec, T& x) override {
				T mlt = vec[0];
				bool inv = false;
				if (mlt.mod() > 1) {
					inv = true;
					mlt = T(1) / mlt;
				}
				mlt = -T(1) + mlt;
				if (!(mlt.mod() < 1))
					throw std::runtime_error("logarithm diverges");
				T term = mlt;
				x = T::zero();
				int i = 1;
				while (term.mod() > EPS) {
					x = x + term / i;
					term = -term * mlt;
					i++;
				}
				if (inv)
					x = -x;
			}
		};
		struct pow : public func_base::function<T> {
			void operator()(const std::vector<T>& vec, T& x) {
				exp _exp;
				ln _ln;
				mult _mult;
				T arg;
				_ln({ vec[0] }, arg);
				_mult({ arg, vec[1] }, arg);
				_exp({ arg }, x);
			}
		};

		static void set_data(std::vector<std::vector<std::string>>& oper_by_prior,
			std::map<std::string, func_base::function<T>*>& oper_table)
		{
			oper_by_prior = { {"sin", "cos", "tan", "cot", "exp", "ln", "neg"}, {"^"}, {"*", "/"}, {"+", "-"} };
			oper_table = {
				{"+", new sum},
				{"-", new diff},
				{"*", new mult},
				{"/", new div}, 
				{"neg", new neg},
				{"sin", new sin},
				{"cos", new cos},
				{"tan", new tan},
				{"cot", new cot},
				{"exp", new exp},
				{"ln", new ln},
				{"^", new pow}
			};
		}
	};
}

#endif