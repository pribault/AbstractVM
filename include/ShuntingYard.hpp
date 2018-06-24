#ifndef SHUNTING_YARD_HPP
# define SHUNTING_YARD_HPP

# include <string>
# include <vector>

std::vector<std::string>	*ShuntingYard(
							const std::string &string,
							const std::vector<std::string> &functions,
							const std::vector<std::string> &operators);

#endif
