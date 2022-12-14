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
		template<int mx>
		struct prior
		{
			int val;
			prior(void) : val{ mx } {}
			prior operator-(int step) 
			{ 
				prior<mx> res;
				res.val -= step;
				while (res.val < 0)
					res.val += mx;
				return res;
			}
		};

	public:
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
			in = &_in;
			out = &_out;
			oper_table = _oper_table;
			oper_by_prior = _oper_by_prior;
#pragma warning(push)
#pragma warning(disable : 4267)
			max_prior = oper_by_prior.size() - 1;
#pragma warning(pop)
			braces = _braces;
			for (auto [f, s] : braces) {
				oper_by_prior[0].push_back(f);
				oper_by_prior[0].push_back(s);
			}
			std::vector<std::string> _allowed_words;
			for (const std::vector<std::string>& v : _oper_by_prior) {
				for (const std::string& word : v) {
					_allowed_words.push_back(word);
				}
			}
			ts = new token::token_stream<T>(_in,
				_allowed_words,
				_ignored_chars,
				_endl_chars,
				_exit_chars);
		}

	};

}

#endif