#include <iostream>
#include <vector>
#include <cctype>
#include <typeinfo>
#include <cmath>

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

string operatorAssociativity(char oper)
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

template<typename VectorType>
void pushFront(vector<VectorType> &v, VectorType element)
{
	v.insert(v.begin(), element);
}

template<typename VectorType>
VectorType popFrontAndReturn(vector<VectorType> &v)
{
	auto element = v.front();

	v.erase(v.begin());

	if (typeid(element) == typeid(int))
		return element;
	else if (typeid(element) == typeid(char))
		return static_cast<char>(element);

	return 0;
}

double solveExpression(double firstOperand, double secondOperand, char arithmeticOperator)
{
	switch (arithmeticOperator)
	{
		case '+':
			return firstOperand + secondOperand;
		case '-':
			return firstOperand - secondOperand;
		case '*':
			return firstOperand * secondOperand;
		case '/':
			return firstOperand / secondOperand;
		case '^':
			return pow(firstOperand, secondOperand);
		default:
			return 0;
	}
}

string infixNotationToReversePolishNotation(const string &str)
{
	vector<double> operands;
	vector<char> operators;

	string reversePolishNotation;

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

			reversePolishNotation += stringifyVariable(result);
		}
		else if (str[i] == '(')
			pushFront(operators, str[i]);
		else if (str[i] == ')')
		{
			for (; operators.front() != '('; ++i)
			{
				char oper = popFrontAndReturn(operators);

				reversePolishNotation += stringifyVariable(oper);
			}

			if (operators.front() == '(')
				popFrontAndReturn(operators);
		}
		else if (isValidOperator(str[i]))
		{
			if (!operators.empty() && operators.front() != '(')
			{
				if (operatorPrecedence(str[i]) == operatorPrecedence(operators.front()))
				{
					if (operatorAssociativity(str[i]) != "right")
					{
						char oper = popFrontAndReturn(operators);

						reversePolishNotation += stringifyVariable(oper);
					}

					pushFront(operators, str[i]);
				}
				else
					pushFront(operators, str[i]);
			}
			else
				pushFront(operators, str[i]);
		}
	}

	if (!operators.empty())
		for (i = 0; i < operators.size(); ++i)
			reversePolishNotation += stringifyVariable(operators[i]);

	operands.clear();
	operators.clear();

	return reversePolishNotation;
}

int main()
{
	cout << "Enter an arithmetical expression, separating with whitespaces operands, operators and parentheses." << endl;
	cout << "Example: 3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3" << endl;

	string infixExpression;
	getline(cin, infixExpression);

	consoleLog("Reverse Polish Notation: " + infixNotationToReversePolishNotation(infixExpression));

	return 0;
}
