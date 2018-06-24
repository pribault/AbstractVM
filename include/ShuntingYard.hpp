#ifndef SHUNTING_YARD_HPP
# define SHUNTING_YARD_HPP

# include <string>
# include <vector>

class	ParenthesesMismatchedException : public std::exception
{
	public:
		virtual const char*	what(void) const noexcept;
};

class	InvalidTokenException : public std::exception
{
	public:
		InvalidTokenException(void);
		InvalidTokenException(const std::string &token);
		InvalidTokenException(const InvalidTokenException &b);
		~InvalidTokenException(void);
		virtual const char*	what(void) const noexcept;
		InvalidTokenException	&operator=(const InvalidTokenException &b);
	private:
		std::string	_token;
};

std::vector<std::string>	*ShuntingYard(
							const std::string &string,
							const std::vector<std::string> &functions,
							const std::vector<std::string> &operators,
							const std::vector<std::string> &brackets,
							const std::vector<std::string> &comments);

#endif
