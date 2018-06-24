#include "ShuntingYard.hpp"
#include "Log.hpp"
#include <iostream>
#include <stack>

static const std::string	whitespaces = " \a\b\t\n\v\f\r";
static const std::string	numbers = "0123456789.";
static const std::string	words = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789._";

const char*	ParenthesesMismatchedException::what(void) const noexcept
{
	return ("parentheses mismatched");
}

InvalidTokenException::InvalidTokenException(const std::string &token)
{
	_token = token;
}
const char*	InvalidTokenException::what(void) const noexcept
{
	static std::string	str;

	str = "invalid token ";
	str.append(_token);
	return (str.c_str());
}

InvalidTokenException::InvalidTokenException(void)
{
}

InvalidTokenException::InvalidTokenException(const InvalidTokenException &b)
{
	(void)b;
}

InvalidTokenException::~InvalidTokenException(void)
{
}

InvalidTokenException	&InvalidTokenException::operator=(const InvalidTokenException &b)
{
	(void)b;
	return (*this);
}

template		<typename T>
static int	find(const std::vector<T> &vector, const T &b)
{
	for (int i = 0; i < static_cast<int>(vector.size()); i++)
		if (vector[i] == b)
			return (i);
	return (-1);
}

static bool		getToken(
				const std::string &str,
				const std::vector<std::string> &functions,
				const std::vector<std::string> &operators,
				const std::vector<std::string> &brackets,
				const std::vector<std::string> &comments,
				size_t &i,
				std::string &token)
{
	if (i >= str.length())
		return (false);

	token = "";

	//	get words

	if (words.find(str[i]) != std::string::npos)
	{
		while (words.find(str[i]) != std::string::npos)
			token.push_back(str[i++]);
		return (true);
	}

	//	get whitespace

	if (whitespaces.find(str[i]) != std::string::npos)
	{
		while (whitespaces.find(str[i]) != std::string::npos)
			token.push_back(str[i++]);
		return (true);
	}

	for (size_t j = 0; j < functions.size(); j++)
		if (!str.compare(i, functions[j].length(), functions[j]))
		{
			token = functions[j];
			i += functions[j].length();
			return (true);
		}

	for (size_t j = 0; j < operators.size(); j++)
		if (!str.compare(i, operators[j].length(), operators[j]))
		{
			token = operators[j];
			i += operators[j].length();
			return (true);
		}

	for (size_t j = 0; j < brackets.size(); j++)
		if (!str.compare(i, brackets[j].length(), brackets[j]))
		{
			token = brackets[j];
			i += brackets[j].length();
			return (true);
		}

	for (size_t j = 0; j < comments.size(); j++)
		if (!str.compare(i, comments[j].length(), comments[j]))
		{
			token = comments[j];
			i += comments[j].length();
			return (true);
		}

	token.push_back(str[i++]);
	return (true);
}

std::vector<std::string>	*ShuntingYard(
							const std::string &string,
							const std::vector<std::string> &functions,
							const std::vector<std::string> &operators,
							const std::vector<std::string> &brackets,
							const std::vector<std::string> &comments)
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
	while (getToken(string, functions, operators, brackets, comments, i, token))
	{
		log << "token: " << token << std::endl;
		if (numbers.find(token[0]) != std::string::npos)
			output->push_back(token);
		else if (find(functions, token) != -1)
			stack.push(token);
		else if (find(operators, token) != -1)
		{
			while (!stack.empty() && (
				(find(functions, stack.top()) != -1) ||
				(find(operators, stack.top()) >= find(operators, token))) &&
				(find(brackets, stack.top()) == -1 || (find(brackets, stack.top()) % 2) == 1))
			{
				output->push_back(stack.top());
				stack.pop();
			}
			stack.push(token);
		}
		else if (find(brackets, token) != -1 && (find(brackets, token) % 2) == 0)
			stack.push(token);
		else if (find(brackets, token) != -1 && (find(brackets, token) % 2) == 1)
		{
			while (!stack.empty() &&
				(find(brackets, stack.top()) == -1 || (find(brackets, stack.top()) % 2) == 1))
			{
				output->push_back(stack.top());
				stack.pop();
			}
			if (!stack.empty() &&
				find(brackets, stack.top()) != -1 &&
				(find(brackets, stack.top()) % 2) == 0 &&
				find(brackets, token) / 2 == find(brackets, stack.top()) / 2)
				stack.pop();
			else
			{
				delete output;
				throw (ParenthesesMismatchedException());
			}
		}
		else if (find(comments, token) != -1)
			break;
		else if (whitespaces.find(token) == std::string::npos)
		{
			delete output;
			throw (InvalidTokenException(token));
		}
	}
	while (!stack.empty())
		if (find(brackets, stack.top()) != -1)
		{
			delete output;
			throw (ParenthesesMismatchedException());
		}
		else
		{
			output->push_back(stack.top());
			stack.pop();
		}
	return (output);
}
