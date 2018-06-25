#ifndef SHUNTING_YARD_HPP
# define SHUNTING_YARD_HPP

# include "Exceptions.hpp"
# include <string>
# include <vector>

class	ParenthesesMismatchedException : public std::exception
{
	public:
		virtual const char*	what(void) const noexcept;
};

std::vector<std::string>	*ShuntingYard(
							const std::string &string,
							const std::vector<std::string> &functions,
							const std::vector<std::string> &operators,
							const std::vector<std::string> &brackets,
							const std::vector<std::string> &comments);

#endif
