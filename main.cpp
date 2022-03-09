#include <iostream>
#include <vector>
#include <cctype>
#include <typeinfo>

using namespace std;

void consoleLog(const string &str)
{
	cout << str << endl;
}

template<typename VectorType>
string stringifyVector(const VectorType &v, const string &delimiter)
{
	string stringify;

	if (!v.empty())
	{
		short int i = 0;
		string element;

		for (auto e: v)
		{
			if (typeid(e) == typeid(int))
				element = to_string(e);
			else if (typeid(e) == typeid(char))
				element = string(1, e);

			stringify += element;

			if (i < v.size() - 1)
				stringify += delimiter;

			++i;
		}
	}
	return stringify;
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

	consoleLog(stringifyVector(operands, " "));
	consoleLog(stringifyVector(operators, " "));
}

int main()
{
	calculator("3 + 4");
	return 0;
}
