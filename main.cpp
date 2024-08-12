#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <deque>
#include <map>

using namespace std;

bool isValidOper(char t_oper)
{
	vector<char> validOpers = {'^', '*', '/', '+', '-'};

	return find(validOpers.begin(), validOpers.end(), t_oper) != validOpers.end();
}

map<char, string> operInfo(char t_oper)
{
	map<char, string> op;
	string            p;
	string            a;

	switch (t_oper)
	{
		case '^':
			p = "4";
			a = "right";
			break;
		case '*':
		case '/':
			p = "3";
			a = "left";
			break;
		case '+':
		case '-':
			p = "2";
			a = "left";
			break;
		default:
			p = "";
			a = "";
	}

	op['p'] = p;
	op['a'] = a;

	return op;
}

string buildOutput(const deque<string> &tokens)
{
	string output;

	for (const string &token : tokens)
		output += token + " ";

	return output;
}

string reversePolishNotation(const string &tokens)
{
	stack<char>   operators;
	deque<string> ordered_tokens;

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

			ordered_tokens.push_back(to_string(operand));
		}
		else if (isValidOper(tokens[i]))
		{
			map<char, string> op1 = operInfo(tokens[i]);
			map<char, string> op2;

			if (!operators.empty())
				op2 = operInfo(operators.top());

			while (!operators.empty() && operators.top() != '('
			       && (op2['p'] > op1['p'] || op2['p'] == op1['p']
			                                  && op1['a'] == "left"))
			{
				ordered_tokens.emplace_back(1, operators.top());

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
					ordered_tokens.emplace_back(1, operators.top());

					operators.pop();
				}
			}

			if (operators.top() == '(')
				operators.pop();

			if (operators.top() == '%') // TODO: Check if operator is a function
			{
				ordered_tokens.emplace_back(1, operators.top());

				operators.pop();
			}
		}
	}

	while (!operators.empty())
	{
		if (operators.top() != '(')
		{
			ordered_tokens.emplace_back(1, operators.top());

			operators.pop();
		}
	}
	return buildOutput(ordered_tokens);
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
