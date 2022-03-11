#include <iostream>
#include <vector>
#include <cctype>

using namespace std;

void consoleLog(const string &str)
{
	cout << str << endl;
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
