#pragma once
#include <string>
#include <vector>
#include "calculator_operations.h"

const std::string EXIT = "exit";

double calc::sum(double a, double b)
{
	return a + b;
}

double calc::diff(double a, double b)
{
	return a - b;
}

double calc::mult(double a, double b)
{
	return a * b;
}

double calc::div_d(double a, double b)
{
	if (b == 0)
		throw std::string("in calc::div_d: division by zero");
	return a / b;
}

double calc::pow(double a, double b)
{
	if (a < 0)
		throw std::string("in calc::pow: negative power base");
	return std::pow(a, b);
}

class Calculator
{
private:
	std::string curRequest;
	bool charAllowed(char c);
	std::vector<std::string> splitRequest(void);
	bool isNum(std::string s);
	bool isOp(std::string s);
public:
	friend int main(void);
	Calculator(void) {}
	void getRequest(void) { std::getline(std::cin, curRequest); }
	double processRequest(void)
	{
		std::vector<std::string> words = splitRequest();
		if (words.size() > 5)
			throw std::string("incorrect input: too many arguments");
		if (words.size() < 3)
			throw std::string("incorrect input: too few arguments");
		double firstArg, secondArg;
		char op;
		switch (words.size()) {
		case 3:
			if (!isNum(words[0]) || !isOp(words[1]) || !isNum(words[2]))
				throw std::string("incorrect input: incorrect format");
			firstArg = stod(words[0]), secondArg = stod(words[2]), op = words[1][0];
			break;
		case 5:
			if (!isOp(words[0]) || !isNum(words[1]) || !isOp(words[2]) || !isOp(words[3]) || !isNum(words[4]))
				throw std::string("incorrect input: incorrect format");
			firstArg = stod(words[1]), secondArg = stod(words[4]), op = words[2][0];
			if (words[0][0] == '-')
				firstArg *= -1.0;
			else if (words[0][0] != '+')
				throw std::string("incorrect input: incorrect format");
			if (words[3][0] == '-')
				secondArg *= -1.0;
			else if (words[3][0] != '+')
				throw std::string("incorrect input: incorrect format");
			break;
		case 4:
			if (isOp(words[0]) && isNum(words[1]) && isOp(words[2]) && isNum(words[3])) {
				firstArg = stod(words[1]), secondArg = stod(words[3]), op = words[2][0];
				if (words[0][0] == '-')
					firstArg *= -1.0;
				else if (words[0][0] != '+')
					throw std::string("incorrect input: incorrect format");
				break;
			}
			if (isNum(words[0]) && isOp(words[1]) && isOp(words[2]) && isNum(words[3])) {
				firstArg = stod(words[0]), secondArg = stod(words[3]), op = words[1][0];
				if (words[2][0] == '-')
					secondArg *= -1.0;
				else if (words[2][0] != '+')
					throw std::string("incorrect input: incorrect format");
				break;
			}
			throw std::string("incorrect input: incorrect format");
		default:
			firstArg = 0, secondArg = 0, op = '+';
			break;
		}
		switch (op) {
		case '+':
			return calc::sum(firstArg, secondArg);
		case '-':
			return calc::diff(firstArg, secondArg);
		case '*':
			return calc::mult(firstArg, secondArg);
		case '/':
			return calc::div_d(firstArg, secondArg);
		case '^':
			return calc::pow(firstArg, secondArg);
		default:
			throw std::string("unknown error");
		}
	}
	void mainCycle(void)
	{
		while (true) {
			getRequest();
			if (curRequest == EXIT)
				exit(0);
			try {
				std::cout << processRequest() << std::endl;
			}
			catch (std::string err) {
				std::cout << err << std::endl;
			}
			std::cout.flush();
		}
	}
};

bool Calculator::charAllowed(char c)
{
	switch (c) {
	case '+':case '-':case '*':case '/':case '^':return true;
	default:return false;
	}
}

std::vector<std::string> Calculator::splitRequest(void)
{
	std::vector<std::string> words;
	std::string curWord = "";
	for (const char& c : curRequest) {
		if (('0' <= c && c <= '9') || c == '.') {
			curWord += c;
			continue;
		}
		if (!charAllowed(c)) {
			if (!curWord.empty()) {
				words.push_back(curWord);
				curWord = "";
			}
			continue;
		}
		if (!curWord.empty()) {
			words.push_back(curWord);
			curWord = "";
		}
		words.push_back(std::string(1, c));
	}
	if (!curWord.empty())
		words.push_back(curWord);
	return words;
}

bool Calculator::isNum(std::string s)
{
	bool dot = false;
	for (const char& c : s) {
		if ('0' <= c && c <= '9')
			continue;
		if (c == '.' && !dot) {
			dot = true;
			continue;
		}
		return false;
	}
	return true;
}

bool Calculator::isOp(std::string s)
{
	if (s.size() != 1)
		return false;
	char c = s[0];
	return Calculator::charAllowed(c);
}
