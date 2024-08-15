#ifndef CALCULATOR_REVERSEPOLISHNOTATION_H
#define CALCULATOR_REVERSEPOLISHNOTATION_H


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


#endif //CALCULATOR_REVERSEPOLISHNOTATION_H
