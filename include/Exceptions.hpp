#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP

# include <exception>
# include <string>

class	NotEnoughOperandsException : public std::exception
{
	public:
		NotEnoughOperandsException(void);
		NotEnoughOperandsException(const std::string &token);
		NotEnoughOperandsException(const NotEnoughOperandsException &b);
		~NotEnoughOperandsException(void);
		virtual const char*	what(void) const noexcept;
		NotEnoughOperandsException	&operator=(const NotEnoughOperandsException &b);
	private:
		std::string	_token;
};

#endif
