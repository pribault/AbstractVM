#include "avm.hpp"

template		<typename T>
static int	find(const std::vector<T> &vector, const T &b)
{
	for (int i = 0; i < static_cast<int>(vector.size()); i++)
		if (vector[i] == b)
			return (i);
	return (-1);
}

void	execute(const std::vector<std::string> *rpn, std::stack<IOperand *> &stack)
{
	std::stack<IOperand *>	tmp;

	for (size_t i = 0; i < rpn->size(); i++)
	{
		if (find(operators, rpn->at(i)) != -1)
		{
			if (tmp.size() >= 2)
			{

			}
			else
			{
				while (!tmp.empty())
				{
					delete tmp.top();
					tmp.pop();
				}
				throw (NotEnoughOperandsException(rpn->at(i)));
			}
		}
	}
}
