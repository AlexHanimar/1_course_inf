#include "operations.h"
#include <iostream>
#include <vector>
#include <string>

int main()
{
	oper::Sum op;
	std::vector<double> args;
	args.push_back(11);
	args.push_back(10);
	try {
		op.setArgs(args);
		std::cout << op.exec() << std::endl;
	}
	catch (std::string s) {
		std::cout << s << std::endl;
	}
	return 0;
}