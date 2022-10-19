#pragma once
#ifndef CALCULATOR_CLASS
#define CALCULATOR_CLASS
#include <string>
#include <vector>
#include "calculator_operations.h"

const std::string EXIT = "exit";

class Calculator
{
private:
	std::string curRequest;
	bool charAllowed(char c);
	std::vector<std::string> splitRequest(void);
	bool isNum(std::string s);
	bool isOp(std::string s);
public:
	// friend int main(void);
	Calculator(void);
	void getRequest(void);
	double processRequest(void);
	void mainCycle(void);
};

#endif


