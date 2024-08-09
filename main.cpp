#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

// void consoleLog(const string &str)
// {
// 	cout << str << endl;
// }

template<typename VariableType>
string stringifyVariable(const VariableType &element);

template<>
string stringifyVariable<double>(const double &element)
{
	return to_string(element) += " ";
}

template<>
string stringifyVariable<char>(const char &element)
{
	return string(1, element) += " ";
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

/*template<typename VectorType>
void pushFront(vector<VectorType> &v, const VectorType element)
{
	v.insert(v.begin(), element);
}

template<typename VectorType>
VectorType popFrontAndReturn(vector<VectorType> &v)
{
	auto element = v.front();

	v.erase(v.begin());

	return element;
}

double calculate(double firstOperand, double secondOperand, char oper)
{
	switch (oper)
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

double solveExpression(vector<double> &operands, vector<char> &operators)
{
	double secondOperand      = popFrontAndReturn(operands);
	double firstOperand       = popFrontAndReturn(operands);
	char   arithmeticOperator = popFrontAndReturn(operators);
	double result             = calculate(firstOperand, secondOperand, arithmeticOperator);

	pushFront(operands, result);

	return result;
}*/

string infixNotationToReversePolishNotation(const string &str)
{
	stack<double> operands;
	stack<char>   operators;

	string reversePolishNotation;

	int i;

	for (i = 0; i < str.length(); ++i)
	{
		if (isspace(str[i]))
			continue;
		else if (isdigit(str[i]))
		{
			// Subtract ASCII character by '0' to get numeric value, and multiply it by 10 to shuffle digits to the left
			double result = 0;

			for (; isdigit(str[i]); ++i)
				result = (result * 10) + (str[i] - '0');
			i--;

			operands.push(result);

			reversePolishNotation += stringifyVariable(result);
		}
		else if (isValidOperator(str[i]))
		{
			while (!operators.empty()
			       && operators.top() != '('
			       && (operatorPrecedence(operators.top()) > operatorPrecedence(str[i])
			           || operatorPrecedence(operators.top()) == operatorPrecedence(str[i])
			              && operatorAssociativity(str[i]) == "left"))
			{
				reversePolishNotation += stringifyVariable(operators.top());

				operators.pop();
			}

			operators.push(str[i]);
		}
		else if (str[i] == '(')
			operators.push(str[i]);
		else if (str[i] == ')')
		{
			while (operators.top() != '(')
			{
				if (!operators.empty())
				{
					reversePolishNotation += stringifyVariable(operators.top());

					operators.pop();
				}
			}

			if (operators.top() == '(')
				operators.pop();
			if (operators.top() == '%') // TODO: Check if operator is a function
			{
				reversePolishNotation += stringifyVariable(operators.top());

				operators.pop();
			}
		}
	}

	while (!operators.empty())
	{
		if (operators.top() != '(')
		{
			reversePolishNotation += stringifyVariable(operators.top());

			operators.pop();
		}
	}

	return reversePolishNotation;
}

int main()
{
	cout << "Enter an arithmetical expression, separating with whitespaces operands, operators and parentheses."
	     << endl;
	cout << "Example: 3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3" << endl;

	string infixExpression;
	getline(cin, infixExpression);

	string result = infixNotationToReversePolishNotation(infixExpression);
	cout << "Reverse Polish Notation: " << result << endl;

	return 0;
}
