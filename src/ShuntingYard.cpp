#include "ShuntingYard.hpp"
#include "Log.hpp"
#include <iostream>
#include <stack>

static const std::vector<std::string>		brackets = {{"()", "{}", "[]"}};
static const std::string					whitespaces = " \a\b\t\n\v\f\r";
static const std::string					letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const std::string					numbers = "0123456789.";

template		<typename T>
static size_t	find(const std::vector<T> &vector, const T &b)
{
	for (size_t i = 0; i < vector.size(); i++)
		if (vector[i] == b)
			return (i);
	return (-1);
}

static bool		getToken(
				const std::string &str,
				size_t &i,
				std::string &token)
{
	if (i >= str.length())
		return (false);

	token = "";

	//	get whitespace

	if (whitespaces.find(str[i]) != std::string::npos)
	{
		while (whitespaces.find(str[i]) != std::string::npos)
			token.push_back(str[i++]);
		return (true);
	}

	//	get number

	if (numbers.find(str[i]) != std::string::npos)
	{
		while (numbers.find(str[i]) != std::string::npos)
			token.push_back(str[i++]);
		return (true);
	}

	//	get word

	if (letters.find(str[i]) != std::string::npos)
	{
		while (letters.find(str[i]) != std::string::npos)
			token.push_back(str[i++]);
		return (true);
	}

	token.push_back(str[i++]);
	return (true);
}

/*
while there are tokens to be read:
	read a token.
	if the token is a number, then:
		push it to the output queue.
	if the token is a function then:
		push it onto the operator stack 
	if the token is an operator, then:
		while ((there is a function at the top of the operator stack)
				or (there is an operator at the top of the operator stack with greater precedence)
				or (the operator at the top of the operator stack has equal precedence and is left associative))
				and (the operator at the top of the operator stack is not a left bracket):
			pop operators from the operator stack onto the output queue.
		push it onto the operator stack.
	if the token is a left bracket (i.e. "("), then:
		push it onto the operator stack.
	if the token is a right bracket (i.e. ")"), then:
		while the operator at the top of the operator stack is not a left bracket:
			pop the operator from the operator stack onto the output queue.
		pop the left bracket from the stack.
		if the stack runs out without finding a left bracket, then there are mismatched parentheses.
if there are no more tokens to read:
	while there are still operator tokens on the stack:
		if the operator token on the top of the stack is a bracket, then there are mismatched parentheses.
		pop the operator from the operator stack onto the output queue.
exit.
*/

template	<typename T>
bool		find(std::vector<T> &vector, T &word)
{
	for (size_t i = 0; i < vector.size(); i++)
		if (vector[i] == word)
			return (true);
	return (false);
}

std::vector<std::string>	*ShuntingYard(
							const std::string &string,
							const std::vector<std::string> &functions,
							const std::vector<std::string> &operators
							)
{
	std::vector<std::string>	*output;
	std::stack<std::string>		stack;
	std::string					token;
	size_t						i = 0;

	try
	{
		output = new std::vector<std::string>();
	}
	catch (const std::exception &e)
	{
		return (NULL);
	}
	while (getToken(string, i, token))
	{
		log << "token: " << token << std::endl;
		if (numbers.find(token[0]) != std::string::npos)
			output->push_back(token);
		else if (find(functions, token))
			stack.push(token);
		else if (find(operators, token))
		{

		}
	}
	return (output);
}
