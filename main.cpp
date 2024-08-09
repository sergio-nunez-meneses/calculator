#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

bool isValidOper(char t_oper)
{
	vector<char> validOpers = {'^', '*', '/', '+', '-'};

	return find(validOpers.begin(), validOpers.end(), t_oper) != validOpers.end();
}

int operPrecedence(char t_oper)
{
	switch (t_oper)
	{
		case '^':
			return 4;
		case '*':
		case '/':
			return 3;
		case '+':
		case '-':
			return 2;
		default:
			return 0;
	}
}

string operAssociativity(char t_oper)
{
	switch (t_oper)
	{
		case '^':
			return "right";
		case '*':
		case '/':
		case '+':
		case '-':
			return "left";
		default:
			return "";
	}
}

string reversePolishNotation(const string &tokens)
{
	stack<double> operands; // TODO: Use for solving the expression
	stack<char>   operators;

	string output;

	int i;
	for (i = 0; i < tokens.length(); ++i)
	{
		if (isspace(tokens[i]))
			continue;
		else if (isdigit(tokens[i]))
		{
			// Subtract ASCII character by '0' to get numeric value, and multiply it by 10 to shuffle digits to the left
			double operand = 0;

			for (; isdigit(tokens[i]); ++i)
				operand = (operand * 10) + (tokens[i] - '0');
			i--;

			operands.push(operand);

			output += to_string(operand);
			output += " ";

		}
		else if (isValidOper(tokens[i]))
		{
			while (!operators.empty()
			       && operators.top() != '('
			       && (operPrecedence(operators.top()) > operPrecedence(tokens[i])
			           || operPrecedence(operators.top()) == operPrecedence(tokens[i])
			              && operAssociativity(tokens[i]) == "left"))
			{
				output += operators.top();
				output += " ";

				operators.pop();
			}

			operators.push(tokens[i]);
		}
		else if (tokens[i] == '(')
			operators.push(tokens[i]);
		else if (tokens[i] == ')')
		{
			while (operators.top() != '(')
			{
				if (!operators.empty())
				{
					output += operators.top();
					output += " ";

					operators.pop();
				}
			}

			if (operators.top() == '(')
				operators.pop();

			if (operators.top() == '%') // TODO: Check if operator is a function
			{
				output += operators.top();
				output += " ";

				operators.pop();
			}
		}
	}

	while (!operators.empty())
	{
		if (operators.top() != '(')
		{
			output += operators.top();
			output += " ";

			operators.pop();
		}
	}
	return output;
}

int main()
{
	cout << "Enter an arithmetical expression, separating with whitespaces operands, operators and parentheses."
	     << endl;
	cout << "Example: 3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3" << endl;

	string input;
	getline(cin, input);

	string result = reversePolishNotation(input);
	cout << "Expression in Reverse Polish Notation: " << result << endl;

	return 0;
}
