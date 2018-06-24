#include "Exceptions.hpp"

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

NotEnoughOperandsException::NotEnoughOperandsException(void)
{
}

NotEnoughOperandsException::NotEnoughOperandsException(const NotEnoughOperandsException &b)
{
	(void)b;
}

NotEnoughOperandsException::~NotEnoughOperandsException(void)
{
}

NotEnoughOperandsException	&NotEnoughOperandsException::operator=(const NotEnoughOperandsException &b)
{
	(void)b;
	return (*this);
}
