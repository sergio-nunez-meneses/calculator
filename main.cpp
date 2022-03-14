#include <iostream>
#include <vector>
#include <cctype>
#include <typeinfo>

using namespace std;

void consoleLog(const string &str)
{
	cout << str << endl;
}

template<typename VariableType>
string stringifyVariable(const VariableType &element)
{
	string stringify;

	if (typeid(element) == typeid(int))
		stringify += to_string(element);
	else if (typeid(element) == typeid(char))
		stringify += string(1, element);

	return stringify += " ";
}

bool isValidOperator(char oper)
{
	vector<char> validOperators = {'^', '*', '/', '+', '-'};

	return find(validOperators.begin(), validOperators.end(), oper) != validOperators.end();
}

int operatorPrecedence(char oper)
{
	switch (oper)
	{
		case '^':
			return 3;
		case '*':
		case '/':
			return 2;
		case '+':
		case '-':
			return 1;
		default:
			return 0;
	}
}

string operatorAssociativity(const char &oper)
{
	switch (oper)
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

void pushOperatorFront(vector<char> &v, const char &oper)
{
	v.insert(v.begin(), oper);
}

void popOperatorFront(vector<char> &v)
{
	v.erase(v.begin());
}

string calculator(const string &str)
{
	vector<int> operands;
	vector<char> operators;

	string reversedPolishNotation;

	int i;

	for (i = 0; i < str.length(); ++i)
	{
		if (isspace(str[i]))
			continue;
		else if (isdigit(str[i]))
		{
			// Subtract ASCII character by '0' to get numeric value, and multiply it by 10 to shuffle digits to the left
			int result = 0;

			for (; isdigit(str[i]); ++i)
				result = (result * 10) + (str[i] - '0');

			operands.push_back(result);

			reversedPolishNotation += stringifyVariable(result);
		}
		else if (str[i] == '(')
			pushOperatorFront(operators, str[i]);
		else if (str[i] == ')')
		{
			for (; operators.front() != '('; ++i)
			{
				reversedPolishNotation += stringifyVariable(operators.front());

				popOperatorFront(operators);
			}

			if (operators.front() == '(')
				popOperatorFront(operators);
		}
		else if (isValidOperator(str[i]))
		{
			if (!operators.empty() && operators.front() != '(')
			{
				if (operatorPrecedence(str[i]) == operatorPrecedence(operators.front()))
				{
					if (operatorAssociativity(str[i]) != "right")
					{
						reversedPolishNotation += stringifyVariable(operators.front());

						popOperatorFront(operators);
					}

					pushOperatorFront(operators, str[i]);
				}
				else
					pushOperatorFront(operators, str[i]);
			}
			else
				pushOperatorFront(operators, str[i]);
		}
	}

	if (!operators.empty())
		for (i = 0; i < operators.size(); ++i)
			reversedPolishNotation += stringifyVariable(operators[i]);

	operands.clear();
	operators.clear();

	return reversedPolishNotation;
}

int main()
{
	// Expression taken from https://en.wikipedia.org/wiki/Shunting-yard_algorithm#Detailed_example
	consoleLog(calculator("3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3"));
	return 0;
}
