#include <iostream>
#include "ReversePolishNotation.h"

using namespace std;

int main()
{
	cout << "Enter an arithmetical expression, separating with whitespaces operands, operators and parentheses."
	     << endl;
	cout << "Example: 3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3" << endl;

	string input;

	while (getline(cin, input))
	{
		if (!input.empty())
		{
			ReversePolishNotation rpn(input);
			cout << "Expression in Reverse Polish Notation: " << rpn.display() << endl;
			break;
		}
		else
			cout << "Please, enter an arithmetical expression: " << endl;
	}

	return 0;
}
