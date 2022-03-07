#include <iostream>
#include <vector>
#include <cctype>

using namespace std;

void consoleLog(const string &str)
{
    cout << str << endl;
}

string stringifyVector(vector<char> &v)
{
	string stringify;

	if (!v.empty())
	{
		short int i = 0;

		stringify = "[";
		for (const auto &element : v)
		{
			stringify += "\"";
			stringify += element;
			stringify += "\"";

			if (i < v.size() - 1)
			{
				stringify += ", ";
			}
			++i;
		}
		stringify += "]";
	}
	return stringify;
}

void calculator(const string &str)
{
	vector <char> operands;
	vector <char> operators;
	int i;

	for (i = 0; i < str.length(); ++i)
	{
		if (isspace(str[i]))
			continue;
		else if (isdigit(str[i]))
			operands.push_back(str[i]);
		else
			operators.push_back(str[i]);
	}

	consoleLog(stringifyVector(operands));
	consoleLog(stringifyVector(operators));
}

int main()
{
	calculator("3 + 4");
	return 0;
}
