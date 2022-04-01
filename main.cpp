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
	double secondOperand = popFrontAndReturn(operands);
	double firstOperand = popFrontAndReturn(operands);
	char arithmeticOperator = popFrontAndReturn(operators);
	double result = calculate(firstOperand, secondOperand, arithmeticOperator);

	pushFront(operands, result);

	return result;
}

vector<string> infixNotationToReversePolishNotation(const string &str)
{
	vector<string> returnData;
	vector<double> operands;
	vector<char> operators;

	string reversePolishNotation;

	double expressionResult;
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

			pushFront(operands, result);

			reversePolishNotation += stringifyVariable(result);
		}
		else if (str[i] == '(')
			pushFront(operators, str[i]);
		else if (str[i] == ')')
		{
			for (; operators.front() != '('; ++i)
			{
				reversePolishNotation += stringifyVariable(operators.front());

				expressionResult = solveExpression(operands, operators);
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
						for (int j = 0; !operators.empty(); ++j)
						{
							reversePolishNotation += stringifyVariable(operators.front());

							expressionResult = solveExpression(operands, operators);
						}
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

	for (int k = 0; !operators.empty(); ++k)
	{
		reversePolishNotation += stringifyVariable(operators.front());

		expressionResult = solveExpression(operands, operators);
	}

	returnData.push_back(reversePolishNotation);
	returnData.push_back(to_string(expressionResult));

	return returnData;
}

int main()
{
	cout << "Enter an arithmetical expression, separating with whitespaces operands, operators and parentheses."
	     << endl;
	cout << "Example: 3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3" << endl;

	string infixExpression;
	getline(cin, infixExpression);

	vector<string> result = infixNotationToReversePolishNotation(infixExpression);

	consoleLog("Reverse Polish Notation: " + result[0]);
	consoleLog("Expression result: " + result[1]);

	return 0;
}
