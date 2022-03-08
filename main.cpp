#include <iostream>
#include <vector>
#include <cctype>
#include <typeinfo>

using namespace std;

void consoleLog(const string &str)
{
    cout << str << endl;
}

template <typename VectorType>
string stringifyVector(const VectorType &v)
{
	string stringify;

	if (!v.empty())
	{
		short int i = 0;
		string element;

		stringify = "[";
		for (auto e : v)
		{
			if (typeid(e) == typeid(int))
				element = to_string(e);
			else if (typeid(e) == typeid(char))
				element = string(1, e);

			stringify += element;

			if (i < v.size() - 1)
				stringify += ", ";

			++i;
		}
		stringify += "]";
	}
	return stringify;
}

void calculator(const string &str)
{
	vector <int> operands;
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
