#include <iostream>
#include <vector>

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

int main()
{
	return 0;
}
