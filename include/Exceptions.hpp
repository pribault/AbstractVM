#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP

# include <exception>
# include <string>

class	TokenizedException : public std::exception
{
	public:
		TokenizedException(void);
		TokenizedException(const std::string &token);
		TokenizedException(const TokenizedException &b);
		~TokenizedException(void);
		virtual const char*	what(void) const noexcept;
		TokenizedException	&operator=(const TokenizedException &b);
	protected:
		std::string	_token;
};

class	NotEnoughOperandsException : public TokenizedException
{
	public:
		NotEnoughOperandsException(const std::string &token);
		virtual const char*	what(void) const noexcept;
};

class	InvalidTokenException : public TokenizedException
{
	public:
		InvalidTokenException(const std::string &token);
		virtual const char*	what(void) const noexcept;
};

class	NoParameterException : public TokenizedException
{
	public:
		NoParameterException(const std::string &token);
		virtual const char*	what(void) const noexcept;
};

class	AssertException : public TokenizedException
{
	public:
		AssertException(const std::string &token);
		virtual const char*	what(void) const noexcept;
};

class	LineMalformed : public std::exception
{
	public:
		virtual const char*	what(void) const noexcept;
};

class	StackEmptyException : public std::exception
{
	public:
		virtual const char*	what(void) const noexcept;
};

class	ExitException : public std::exception
{
	public:
		virtual const char*	what(void) const noexcept;
};

class	InvalidTypeException : public std::exception
{
	public:
		virtual const char*	what(void) const noexcept;
};

#endif
