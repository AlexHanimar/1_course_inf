#pragma once

#ifndef CALCULATOR
#define CALCULATOR

#include "token.h"
#include "function_base.h"
#include <map>
#include <utility>

namespace calc {

	template<numeric_base::num_type T>
	requires func_base::func_type<func_base::function<T>, T>
	class grammar
	{
	private:
		typedef func_base::function<T> func_type;
		std::istream* in;
		std::ostream* out;
		std::map<std::string, func_type*> oper_table;
		std::vector<std::vector<std::string>> oper_by_prior;
		token::token_stream<T>* ts;
		std::vector<std::pair<std::string, std::string>> braces;

		int max_prior;

	public:

		struct prior
		{
			int val;
			int mx;
			prior(void) = delete;
			prior(int _mx, int _val)
			{
				mx = _mx;
				val = _val;
				while (val < 0)
					val += mx;
			}
			prior operator-(int step)
			{
				return prior(mx, val - step);
			}
		};

		prior start_prior(void)
		{
			return prior(oper_by_prior.size(), oper_by_prior.size() - 1);
		}

		grammar(void) = delete;
		grammar(std::istream& _in,
			std::ostream& _out,
			const std::vector<std::vector<std::string>>& _oper_by_prior,
			const std::vector<std::pair<std::string, std::string>>& _braces,
			const std::vector<char> _ignored_chars,
			const std::vector<char> _endl_chars,
			const std::vector<char> _exit_chars,
			const std::map<std::string, func_type*>& _oper_table) 
		{
			if (_oper_by_prior.empty())
				throw std::runtime_error("empty operator list");
			in = &_in;
			out = &_out;
			oper_table = _oper_table;
			oper_by_prior = _oper_by_prior;
#pragma warning(push)
#pragma warning(disable : 4267)
			max_prior = oper_by_prior.size() - 1;
#pragma warning(pop)
			braces = _braces;
			std::vector<std::string> _allowed_words;
			for (const std::vector<std::string>& v : _oper_by_prior) {
				for (const std::string& word : v) {
					_allowed_words.push_back(word);
				}
			}
			for (auto [f, s] : _braces) {
				_allowed_words.push_back(f);
				_allowed_words.push_back(s);
			}
			ts = new token::token_stream<T>(_in,
				_allowed_words,
				_ignored_chars,
				_endl_chars,
				_exit_chars);
		}

		token::token_stream<T>* get_token_stream(void)
		{
			return ts;
		}

		T term(prior p)
		{
			if (p.val == 0) {
				token::token<T> tok = ts->get_token();
				// processing numbers
				if (tok.type == token::NUMBER)
					return tok.val;
				// processing braces
				for (auto [op_brace, cl_brace] : braces) {
					if (tok.type != op_brace)
						continue;
					T res = term(p - 1);
					tok = ts->get_token();
					if (tok.type != cl_brace)
						throw std::runtime_error("no matching brace for " + op_brace);
					return res;
				}
				// processing functions and unary operators
				for (const std::string& oper : oper_by_prior[p.val]) {
					if (oper == tok.type) {
						func_type* func_ptr = oper_table[oper];
						T res;
						(*func_ptr)({ term(p) }, res);
						return res;
					}
				}
				// no match found: syntax error
				if (tok.type == token::ENDL)
					throw token::ENDL;
				if (tok.type == token::EXIT)
					throw token::EXIT;
				throw std::runtime_error("syntax error");
			} 
			else {
				T lhs = term(p - 1);
				token::token<T> tok = ts->get_token();
				CYCLE_START:
				while (true) {
					for (const std::string& oper : oper_by_prior[p.val]) {
						if (oper == tok.type) {
							func_type* func_ptr = oper_table[oper];
							(*func_ptr)({ lhs, term(p - 1) }, lhs);
							tok = ts->get_token();
							goto CYCLE_START;
						}
					}
					ts->putback(tok);
					return lhs;
				}
			}
		}

	};

	template<numeric_base::num_type T>
	requires func_base::func_type<func_base::function<T>, T>
	class calculator
	{
	private:
		typedef func_base::function<T> func_type;
		grammar<T> gr;
		token::token_stream<T>* ts;
		std::istream* in;
		std::ostream* out;
	public:
		calculator(void) = delete;
		calculator(std::istream& _in,
			std::ostream& _out,
			const std::vector<std::vector<std::string>>& _oper_by_prior,
			const std::vector<std::pair<std::string, std::string>>& _braces,
			const std::vector<char> _ignored_chars,
			const std::vector<char> _endl_chars,
			const std::vector<char> _exit_chars,
			const std::map<std::string, func_type*>& _oper_table) : 
			gr{ grammar<T>(_in, _out, _oper_by_prior, _braces,
				_ignored_chars, _endl_chars, _exit_chars, _oper_table) }
		{
			ts = gr.get_token_stream();
			in = &_in;
			out = &_out;
		}

		void main_cycle(void)
		{
			while (true) {
				try {
					T x = gr.term(gr.start_prior());
					(*out) << x << std::endl;
				}
				catch (std::string& e) {
					if (e == token::ENDL) {}
					if (e == token::EXIT) {
						(*out) << "shutting down" << std::endl;
						return;
					}
				}
				catch (std::exception& e) {
					(*out) << e.what() << std::endl;
					token::token<T> tok;
					while (tok != token::ENDL)
						tok = ts->get_token();
				}
			}
		}
	};

}

#endif