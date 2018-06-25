#ifndef AVM_HPP
# define AVM_HPP

# include "IOperand.hpp"
# include "ShuntingYard.hpp"
# include "Log.hpp"
# include "Exceptions.hpp"
# include "OperandFactory.hpp"
# include <iostream>
# include <fstream>
# include <stack>

void	execute(const std::vector<std::string> *rpn, std::vector<const IOperand *> &stack, size_t &index);

extern std::vector<std::string>	functions;
extern std::vector<std::string>	operators;
extern std::vector<std::string>	brackets;
extern std::vector<std::string>	comments;

#endif
