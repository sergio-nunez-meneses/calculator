#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <deque>
#include <map>

using namespace std;

class ReversePolishNotation
{
public:
	explicit ReversePolishNotation(string &input);

	string display();

private:
	deque<string> ordered_tokens;

	static bool isValidOper(char t_oper);

	static map<char, string> operInfo(char t_oper);

	void convert(const string &tokens);
};

ReversePolishNotation::ReversePolishNotation(string &input)
{
	this->convert(input);
}

string ReversePolishNotation::display()
{
	string output;

	for (const string &token: this->ordered_tokens)
		output += token + " ";

	return output;
}

bool ReversePolishNotation::isValidOper(char t_oper)
{
	vector<char> validOpers = {'^', '*', '/', '+', '-'};

	return find(validOpers.begin(), validOpers.end(), t_oper) != validOpers.end();
}

map<char, string> ReversePolishNotation::operInfo(char t_oper)
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

void ReversePolishNotation::convert(const string &tokens)
{
	stack<char> operators;

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

			this->ordered_tokens.push_back(to_string(operand));
		}
		else if (isValidOper(tokens[i]))
		{
			while (!operators.empty() && operators.top() != '('
			       && (operInfo(operators.top())['p'] > operInfo(tokens[i])['p']
			           || operInfo(operators.top())['p'] == operInfo(tokens[i])['p']
			              && operInfo(tokens[i])['a'] == "left"))
			{
				this->ordered_tokens.emplace_back(1, operators.top());

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
					this->ordered_tokens.emplace_back(1, operators.top());

					operators.pop();
				}
			}

			if (operators.top() == '(')
				operators.pop();

			if (operators.top() == '%') // TODO: Check if operator is a function
			{
				this->ordered_tokens.emplace_back(1, operators.top());

				operators.pop();
			}
		}
	}

	while (!operators.empty())
	{
		if (operators.top() != '(')
		{
			this->ordered_tokens.emplace_back(1, operators.top());

			operators.pop();
		}
	}
}

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
