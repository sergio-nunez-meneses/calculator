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
	vector<char> validOperators = {'*', '/', '+', '-'};

	return find(validOperators.begin(), validOperators.end(), oper) != validOperators.end();
}

int operatorPrecedence(char oper)
{
	switch (oper)
	{
		case '^':
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

void calculator(const string &str)
{
	vector<int> operands;
	vector<char> operators;
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
		}
		else
			operators.push_back(str[i]);
	}
}

int main()
{
	calculator("3 + 4");
	return 0;
}
