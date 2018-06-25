#include "Exceptions.hpp"

/*
**	TokenizedException
*/

TokenizedException::TokenizedException(const std::string &token)
{
	_token = token;
}

const char*	TokenizedException::what(void) const noexcept
{
	static std::string	str;

	str.append(_token);
	return (str.c_str());
}

TokenizedException::TokenizedException(void)
{
}

TokenizedException::TokenizedException(const TokenizedException &b)
{
	(void)b;
}

TokenizedException::~TokenizedException(void)
{
}

TokenizedException	&TokenizedException::operator=(const TokenizedException &b)
{
	(void)b;
	return (*this);
}

/*
**	NotEnoughOperandsException
*/

NotEnoughOperandsException::NotEnoughOperandsException(const std::string &token)
{
	_token = token;
}

const char*	NotEnoughOperandsException::what(void) const noexcept
{
	static std::string	str;

	str = "Not enough operands for ";
	str.append(_token);
	return (str.c_str());
}

/*
**	InvalidTokenException
*/

InvalidTokenException::InvalidTokenException(const std::string &token)
{
	_token = token;
}

const char*	InvalidTokenException::what(void) const noexcept
{
	static std::string	str;

	str = "Invalid token '";
	str.append(_token);
	str.append("'");
	return (str.c_str());
}

/*
**	NoParameterException
*/

NoParameterException::NoParameterException(const std::string &token)
{
	_token = token;
}

const char*	NoParameterException::what(void) const noexcept
{
	static std::string	str;

	str = "No parameter given for '";
	str.append(_token);
	str.append("'");
	return (str.c_str());
}

/*
**	LineMalformed
*/

const char*	LineMalformed::what(void) const noexcept
{
	return ("line malformed");
}

/*
**	StackEmptyException
*/

const char*	StackEmptyException::what(void) const noexcept
{
	return ("stack is empty");
}

/*
**	ExitException
*/

const char*	ExitException::what(void) const noexcept
{
	return ("stack is empty");
}

/*
**	AssertException
*/

AssertException::AssertException(const std::string &token)
{
	_token = token;
}

const char*	AssertException::what(void) const noexcept
{
	static std::string	str;

	str = "assert exception (";
	str.append(_token);
	str.append(")");
	return (str.c_str());
}

/*
**	InvalidTypeException
*/

const char*	InvalidTypeException::what(void) const noexcept
{
	return ("invalid type");
}
