#pragma once

#ifndef TOKEN
#define TOKEN

#include "numeric_base.h"
#include <string>
#include <stack>
#include <vector>
#include <stdexcept>

namespace token {

	const std::string NUMBER = "NUMBER";
	const std::string EXIT = "EXIT";
	const std::string ENDL = "ENDL";

	class ts_error : public std::runtime_error {
	public:
		ts_error(const std::string& msg) : std::runtime_error(msg) {}
		ts_error(const char* msg) : std::runtime_error(msg) {}
	};

	template<numeric_base::num_type T>
	struct token
	{
		std::string type;
		T val;
		token(const std::string& _type = "", const T& _val = T::zero()) : type{_type}, val{_val} {}
		const token& operator=(const token& other) { type = other.type, val = other.val; return *this; }
		bool operator==(const token& other) { return (type == other.type) && (val == other.val); }
		constexpr static const token null(void) { return token(); }
		friend std::ostream& operator<<(std::ostream& out, token& tok)
		{
			out << '(' << tok.type << '|' << tok.val << ')';
			return out;
		}
	};

	template<numeric_base::num_type T>
	class token_stream
	{
	private:
		token<T> token_buffer;
		std::istream* in;
		std::vector<std::string> allowed_words;
		std::vector<char> ignored_chars;
		std::vector<char> endl_chars;
		std::vector<char> exit_chars;

		bool can_be_extended(const std::string& str)
		{
			for (const std::string& word : allowed_words) {
				if (word.size() >= str.size() && word.substr(0, str.size()) == str)
					return true;
			}
			return false;
		}
		bool is_allowed(const std::string& str)
		{
			for (const std::string& word : allowed_words) {
				if (word == str)
					return true;
			}
			return false;
		}
		bool ignored(char ch)
		{
			for (const char& c : ignored_chars) {
				if (c == ch)
					return true;
			}
			return false;
		}
		bool is_endl(char ch)
		{
			for (const char& c : endl_chars) {
				if (c == ch)
					return true;
			}
			return false;
		}
		bool is_exit(char ch)
		{
			for (const char& c : exit_chars) {
				if (c == ch)
					return true;
			}
			return false;
		}

	public:
		token_stream(void) = delete;
		token_stream(std::istream& _in,
			const std::vector<std::string>& _allowed_words,
			const std::vector<char>& _ignored_chars = { ' ', '\n' },
			const std::vector<char>& _endl_chars = { ';' },
			const std::vector<char>& _exit_chars = { '#' }) :
			in{ &_in },
			allowed_words{ _allowed_words },
			ignored_chars{ _ignored_chars },
			endl_chars{ _endl_chars },
			exit_chars{ _exit_chars } {}
		void putback(const token<T>& tok) { token_buffer = tok; }
		token<T> get_token(void)
		{
			if (token_buffer != token<T>::null()) {
				token<T> res = token_buffer;
				token_buffer = token<T>::null();
				return res;
			}
			std::string str = "";
			while (true) {
				if (is_allowed(str)) {
					return token<T>(str);
				}
				char c = (*in).get();
				if (ignored(c))
					continue;
				if (str.empty() && is_endl(c))
					return token<T>(ENDL);
				if (str.empty() && is_exit(c))
					return token<T>(EXIT);
				if (str.empty() && T::can_start_with(c)) {
					(*in).putback(c);
					T val;
					(*in) >> val;
					return token<T>(NUMBER, val);
				}
				if (can_be_extended(str + c)) {
					str += c;
					continue;
				}
				throw ts_error("incorrect token");
			}
		}
	};

}

#endif