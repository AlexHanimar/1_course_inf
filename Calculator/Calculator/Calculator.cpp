#include "complex.h"
#include "token.h"

using namespace std;

vector<vector<string>> operTable(10);

string ignoredChars = " \n";

int main()
{
	operTable[0] = { "number", "(", ")" };
	operTable[1] = { "sin", "cos", "exp", "sqrt" };
	operTable[2] = { "^" };
	operTable[3] = { "*", "/" };
	operTable[4] = { "+", "-" };
	TokenStream ts(&cin);
	Token t;
	try {
		while (true) {
			ts >> t;
			cout << '{' << t.type << '|' << t.val << "}\n";
		}
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
	return 0;
}