#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string EXIT = "exit";

bool isNum(string s)
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

bool isOp(string s)
{
	if (s.size() != 1)
		return false;
	char c = s[0];
	switch (c) {
	case '+':case '-':case '/':case '*':case '^':return true;
	default:return false;
	}
}

class Calculator
{
private:
	string curRequest;
public:
	Calculator(void) {}
	void getRequest(void) { getline(cin, curRequest); }
	double processRequest(void)
	{
		if (curRequest == "exit")
			exit(0);
		vector<string> words;
		string curWord = "";
		for (const char& c : curRequest) {
			if (('0' <= c && c <= '9') || c == '.')
				curWord += c;
			else {
				words.push_back(curWord);
				curWord = "";
				if (isOp(string(1, c))) {
					words.push_back(string(1, c));
				}
				else {
					throw string(" incorrect input: unsupported symbol " + c);
				}
			}
		}
		if (!curWord.empty())
			words.push_back(curWord);
		if (words.size() > 3)
			throw string("too many arguments");
		if (words.size() < 3)
			throw string("too few arguments");
		if (!isNum(words[0]) || !isOp(words[1]) || !isNum(words[2]))
			throw string("invalid arguments: incorrect format");
		double a = stod(words[0]), b = stod(words[2]);
		char op = words[1][0];
		switch (op) {
		case '+':return a + b;
		case '-':return a - b;
		case '*':return a * b;
		case '/':
			if (b == 0.0)
				throw string("invalid arguments: division by zero");
			return a / b;
		case '^':
			if (a == a && b == 0)
				throw string("invalid arguments: power(0, 0)");
			if (a < 0)
				throw string("invalid arguments: negative power base");
			return pow(a, b);
		default:
			throw string("what happened");
		}
	}
	void mainCycle(void)
	{
		while (1) {
			getRequest();
			try {
				cout << processRequest() << endl;
			}
			catch (string err) {
				cout << err << endl;
			}
		}
	}
};

int main()
{
	Calculator calc;
	calc.mainCycle();
	return 0;
}