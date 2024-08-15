#include <iostream>
#include "ReversePolishNotation.h"

using namespace std;

int main()
{
	cout << "Enter an arithmetical expression, separating with whitespaces operands, operators and parentheses."
	     << endl;
	cout << "Example: 3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3" << endl;

	string input;
	getline(cin, input);

	ReversePolishNotation rpn(input);
	cout << "Expression in Reverse Polish Notation: " << rpn.display() << endl;

	return 0;
}
