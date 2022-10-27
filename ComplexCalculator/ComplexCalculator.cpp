#include "calculator.h"
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int main()
{
	Parser p("1+1.0+1+++-129507.2378250");
	std::stack<Token> st{ p.tokenize() };
	std::vector<Token> v;
	while (!st.empty()) {
		v.push_back(st.top());
		st.pop();
	}
	std::reverse(v.begin(), v.end());
	for (Token& t : v) {
		std::cout << t << " ";
	}
	return 0;
}