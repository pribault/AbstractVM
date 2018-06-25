#include "avm.hpp"
#include "Operand.hpp"

const Operand<int8_t>	zero(0);
const Operand<int8_t>	one(1);

template		<typename T>
static int	find(const std::vector<T> &vector, const T &b)
{
	for (int i = 0; i < static_cast<int>(vector.size()); i++)
		if (vector[i] == b)
			return (i);
	return (-1);
}

typedef struct		s_enum
{
	std::string		token;
	eOperandType	value;
}					t_enum;

void	var(const std::string &token, std::stack<const IOperand *> &tmp, std::vector<const IOperand *> &, size_t &)
{
	static const t_enum	enums[] = {
		{"int8", Int8},
		{"int16", Int16},
		{"int32", Int32},
		{"int64", Int64},
		{"float", Float},
		{"double", Double}
	};
	eOperandType	value = Int8;

	for (size_t i = 0; i < sizeof(enums) / sizeof(t_enum); i++)
		if (token == enums[i].token)
			value = enums[i].value;
	if (tmp.empty())
		throw (NoParameterException(token));
	else
		tmp.top() = operandFactory.createOperand(value, tmp.top()->toString());
}

void	push(const std::string &token, std::stack<const IOperand *> &tmp, std::vector<const IOperand *> &stack, size_t &)
{
	if (tmp.empty())
		throw (NotEnoughOperandsException(token));
	stack.push_back(tmp.top());
	tmp.pop();
	log << "'" << stack.back()->toString() << "' pushed" << std::endl;
}

void	pop(const std::string &, std::stack<const IOperand *> &, std::vector<const IOperand *> &stack, size_t &)
{
	if (!stack.empty())
	{
		log << "'" << stack.back()->toString() << "' poped" << std::endl;
		stack.pop_back();
	}
	else
		throw (StackEmptyException());
}

void	dump(const std::string &, std::stack<const IOperand *> &, std::vector<const IOperand *> &stack, size_t &)
{
	for (size_t i = 0; i < stack.size(); i++)
		std::cout << stack[i]->toString() << std::endl;
	log << "memory dumped" << std::endl;
}

void	add(const std::string &token, std::stack<const IOperand *> &, std::vector<const IOperand *> &stack, size_t &)
{
	const IOperand	*a;
	const IOperand	*b;

	if (stack.size() < 2)
		throw (NotEnoughOperandsException(token));
	b = stack.back();
	stack.pop_back();
	a = stack.back();
	stack.pop_back();
	stack.push_back(*a + *b);
	delete a;
	delete b;
	log << "addition done" << std::endl;
}

void	sub(const std::string &token, std::stack<const IOperand *> &, std::vector<const IOperand *> &stack, size_t &)
{
	const IOperand	*a;
	const IOperand	*b;

	if (stack.size() < 2)
		throw (NotEnoughOperandsException(token));
	b = stack.back();
	stack.pop_back();
	a = stack.back();
	stack.pop_back();
	stack.push_back(*a - *b);
	delete a;
	delete b;
	log << "substraction done" << std::endl;
}

void	mul(const std::string &token, std::stack<const IOperand *> &, std::vector<const IOperand *> &stack, size_t &)
{
	const IOperand	*a;
	const IOperand	*b;

	if (stack.size() < 2)
		throw (NotEnoughOperandsException(token));
	b = stack.back();
	stack.pop_back();
	a = stack.back();
	stack.pop_back();
	stack.push_back(*a * *b);
	delete a;
	delete b;
	log << "multiplication done" << std::endl;
}

void	div(const std::string &token, std::stack<const IOperand *> &, std::vector<const IOperand *> &stack, size_t &)
{
	const IOperand	*a;
	const IOperand	*b;

	if (stack.size() < 2)
		throw (NotEnoughOperandsException(token));
	b = stack.back();
	stack.pop_back();
	a = stack.back();
	stack.pop_back();
	stack.push_back(*a / *b);
	delete a;
	delete b;
	log << "division done" << std::endl;
}

void	mod(const std::string &token, std::stack<const IOperand *> &, std::vector<const IOperand *> &stack, size_t &)
{
	const IOperand	*a;
	const IOperand	*b;

	if (stack.size() < 2)
		throw (NotEnoughOperandsException(token));
	b = stack.back();
	stack.pop_back();
	a = stack.back();
	stack.pop_back();
	stack.push_back(*a % *b);
	delete a;
	delete b;
	log << "modulus done" << std::endl;
}

void	exit(const std::string &, std::stack<const IOperand *> &, std::vector<const IOperand *> &, size_t &)
{
	log << "exiting" << std::endl;
	throw (ExitException());
}

void	assert(const std::string &token, std::stack<const IOperand *> &tmp, std::vector<const IOperand *> &stack, size_t &)
{
	std::string	s;

	if (stack.empty())
		throw (StackEmptyException());
	if (tmp.empty())
		throw (NotEnoughOperandsException(token));
	if (*tmp.top() != *stack.back())
	{
		s.append(tmp.top()->toString());
		s.append(",");
		s.append(stack.back()->toString());
		tmp.pop();
		log << "assert failed" << std::endl;
		throw (AssertException(s));
	}
	tmp.pop();
	log << "assert succeeded" << std::endl;
}

void	print(const std::string &, std::stack<const IOperand *> &, std::vector<const IOperand *> &stack, size_t &)
{
	if (stack.empty())
		throw (StackEmptyException());
	if (stack.back()->getType() != Int8)
		throw (InvalidTypeException());
	std::cout << static_cast<char>(stoi(stack.back()->toString()));
	log << "printed '" << static_cast<int>(stoi(stack.back()->toString())) << "'" << std::endl;
}

void	jmp(const std::string &token, std::stack<const IOperand *> &tmp, std::vector<const IOperand *> &, size_t &index)
{
	if (tmp.empty())
		throw (NotEnoughOperandsException(token));
	index = stoul(tmp.top()->toString()) - 1;
	log << "jumped to " << index + 1 << std::endl;
	tmp.pop();
}

void	cmp(const std::string &token, std::stack<const IOperand *> &tmp, std::vector<const IOperand *> &stack, size_t &)
{
	if (stack.empty())
		throw (StackEmptyException());
	if (tmp.empty())
		throw (NotEnoughOperandsException(token));
	log << "compared '" << stack.back()->toString() << "' and '" << tmp.top()->toString() << "'" << std::endl;
	stack.push_back(*stack.back() - *tmp.top());
	tmp.pop();
}

void	je(const std::string &token, std::stack<const IOperand *> &tmp, std::vector<const IOperand *> &stack, size_t &index)
{
	if (stack.empty())
		throw (StackEmptyException());
	if (tmp.empty())
		throw (NotEnoughOperandsException(token));
	if (*stack.back() == zero)
	{
		index = stoul(tmp.top()->toString()) - 1;
		log << "jumped to " << index + 1 << std::endl;
	}
	stack.pop_back();
	tmp.pop();
}

void	jne(const std::string &token, std::stack<const IOperand *> &tmp, std::vector<const IOperand *> &stack, size_t &index)
{
	if (stack.empty())
		throw (StackEmptyException());
	if (tmp.empty())
		throw (NotEnoughOperandsException(token));
	if (*stack.back() != zero)
	{
		index = stoul(tmp.top()->toString()) - 1;
		log << "jumped to " << index + 1 << std::endl;
	}
	stack.pop_back();
	tmp.pop();
}

void	jl(const std::string &token, std::stack<const IOperand *> &tmp, std::vector<const IOperand *> &stack, size_t &index)
{
	if (stack.empty())
		throw (StackEmptyException());
	if (tmp.empty())
		throw (NotEnoughOperandsException(token));
	if (*stack.back() < zero)
	{
		index = stoul(tmp.top()->toString()) - 1;
		log << "jumped to " << index + 1 << std::endl;
	}
	stack.pop_back();
	tmp.pop();
}

void	jle(const std::string &token, std::stack<const IOperand *> &tmp, std::vector<const IOperand *> &stack, size_t &index)
{
	if (stack.empty())
		throw (StackEmptyException());
	if (tmp.empty())
		throw (NotEnoughOperandsException(token));
	if (*stack.back() <= zero)
	{
		index = stoul(tmp.top()->toString()) - 1;
		log << "jumped to " << index + 1 << std::endl;
	}
	stack.pop_back();
	tmp.pop();
}

void	jg(const std::string &token, std::stack<const IOperand *> &tmp, std::vector<const IOperand *> &stack, size_t &index)
{
	if (stack.empty())
		throw (StackEmptyException());
	if (tmp.empty())
		throw (NotEnoughOperandsException(token));
	if (*stack.back() > zero)
	{
		index = stoul(tmp.top()->toString()) - 1;
		log << "jumped to " << index + 1 << std::endl;
	}
	stack.pop_back();
	tmp.pop();
}

void	jge(const std::string &token, std::stack<const IOperand *> &tmp, std::vector<const IOperand *> &stack, size_t &index)
{
	if (stack.empty())
		throw (StackEmptyException());
	if (tmp.empty())
		throw (NotEnoughOperandsException(token));
	if (*stack.back() >= zero)
	{
		index = stoul(tmp.top()->toString()) - 1;
		log << "jumped to " << index + 1 << std::endl;
	}
	stack.pop_back();
	tmp.pop();
}

void	inc(const std::string &token, std::stack<const IOperand *> &, std::vector<const IOperand *> &stack, size_t &)
{
	const IOperand	*a;

	if (stack.size() < 1)
		throw (NotEnoughOperandsException(token));
	a = stack.back();
	stack.pop_back();
	stack.push_back(*a + one);
	delete a;
	log << "incrementation done" << std::endl;
}

void	dec(const std::string &token, std::stack<const IOperand *> &, std::vector<const IOperand *> &stack, size_t &)
{
	const IOperand	*a;

	if (stack.size() < 1)
		throw (NotEnoughOperandsException(token));
	a = stack.back();
	stack.pop_back();
	stack.push_back(*a - one);
	delete a;
	log << "decrementation done" << std::endl;
}

void	_and(const std::string &token, std::stack<const IOperand *> &, std::vector<const IOperand *> &stack, size_t &)
{
	const IOperand	*a;
	const IOperand	*b;

	if (stack.size() < 2)
		throw (NotEnoughOperandsException(token));
	b = stack.back();
	stack.pop_back();
	a = stack.back();
	stack.pop_back();
	stack.push_back(*a & *b);
	delete a;
	delete b;
	log << "binary and done" << std::endl;
}

void	_or(const std::string &token, std::stack<const IOperand *> &, std::vector<const IOperand *> &stack, size_t &)
{
	const IOperand	*a;
	const IOperand	*b;

	if (stack.size() < 2)
		throw (NotEnoughOperandsException(token));
	b = stack.back();
	stack.pop_back();
	a = stack.back();
	stack.pop_back();
	stack.push_back(*a | *b);
	delete a;
	delete b;
	log << "binary and done" << std::endl;
}

void	_xor(const std::string &token, std::stack<const IOperand *> &, std::vector<const IOperand *> &stack, size_t &)
{
	const IOperand	*a;
	const IOperand	*b;

	if (stack.size() < 2)
		throw (NotEnoughOperandsException(token));
	b = stack.back();
	stack.pop_back();
	a = stack.back();
	stack.pop_back();
	stack.push_back(*a ^ *b);
	delete a;
	delete b;
	log << "binary and done" << std::endl;
}

typedef struct	s_data
{
	std::string	token;
	void		(*function)(const std::string &, std::stack<const IOperand *> &, std::vector<const IOperand *> &, size_t &);
	bool		action;
	size_t		tmp_size;
}				t_data;

void	execute(const std::vector<std::string> *rpn, std::vector<const IOperand *> &stack, size_t &index)
{
	static const t_data				pointers[] = {
		{"int8", &var, false, 1},
		{"int16", &var, false, 1},
		{"int32", &var, false, 1},
		{"int64", &var, false, 1},
		{"float", &var, false, 1},
		{"double", &var, false, 1},
		{"push", &push, true, 1},
		{"pop", &pop, true, 0},
		{"dump", &dump, true, 0},
		{"add", &add, true, 0},
		{"sub", &sub, true, 0},
		{"mul", &mul, true, 0},
		{"div", &div, true, 0},
		{"mod", &mod, true, 0},
		{"assert", &assert, true, 1},
		{"print", &print, true, 0},
		{"exit", &exit, true, 0},
		{"jmp", &jmp, true, 1},
		{"cmp", &cmp, true, 1},
		{"je", &je, true, 1},
		{"jne", &jne, true, 1},
		{"jl", &jl, true, 1},
		{"jle", &jle, true, 1},
		{"jg", &jg, true, 1},
		{"jge", &jge, true, 1},
		{"inc", &inc, true, 0},
		{"dec", &dec, true, 0},
		{"and", &_and, true, 0},
		{"or", &_or, true, 0},
		{"xor", &_xor, true, 0},
		{"end", NULL, false, 0}
	};
	static const std::string		numbers = "0123456789.";
	std::stack<const IOperand *>	tmp;
	const IOperand					*a;
	const IOperand					*b;
	const IOperand					*result;
	size_t							actions = 0;
	bool							found;

	for (size_t i = 0; i < rpn->size(); i++)
	{
		if (find(functions, rpn->at(i)) != -1)
		{
			found = false;
			for (size_t j = 0; !found && pointers[j].function; j++)
				if (rpn->at(i) == pointers[j].token)
				{
					if ((pointers[j].action && actions) ||
						(pointers[j].tmp_size != tmp.size()))
					{
						while (!tmp.empty())
						{
							delete tmp.top();
							tmp.pop();
						}
						throw (LineMalformed());
					}
					try
					{
						log << "executing " << pointers[j].token << std::endl;
						pointers[j].function(rpn->at(i), tmp, stack, index);
					}
					catch (const ExitException &e)
					{
						if (!tmp.empty())
						{
							while (!tmp.empty())
							{
								delete tmp.top();
								tmp.pop();
							}
							throw (LineMalformed());
						}
						throw;
					}
					catch (const std::exception &e)
					{
						log << "failed to execute " << pointers[j].token << std::endl;
						while (!tmp.empty())
						{
							delete tmp.top();
							tmp.pop();
						}
						throw ;
					}
					if (pointers[j].action)
						actions++;
					found = true;
				}
			if (!found)
			{
				while (!tmp.empty())
				{
					delete tmp.top();
					tmp.pop();
				}
				throw (InvalidTokenException(rpn->at(i)));
			}
		}
		else if (find(operators, rpn->at(i)) != -1)
		{
			if (tmp.size() >= 2)
			{
				b = tmp.top();
				tmp.pop();
				a = tmp.top();
				tmp.pop();
				try
				{
					if (rpn->at(i) == "+")
						result = *a + *b;
					else if (rpn->at(i) == "-")
						result = *a - *b;
					else if (rpn->at(i) == "/")
						result = *a / *b;
					else if (rpn->at(i) == "%")
						result = *a % *b;
					else if (rpn->at(i) == "*")
						result = *a * *b;
					delete a;
					delete b;
				}
				catch (const std::exception &e)
				{
					while (!tmp.empty())
					{
						delete tmp.top();
						tmp.pop();
					}
					throw;
				}
				tmp.push(result);
			}
			else if (tmp.size() == 1)
			{
				a = tmp.top();
				tmp.pop();
				try
				{
					if (rpn->at(i) == "+")
						result = zero + *a;
					else if (rpn->at(i) == "-")
						result = zero - *a;
					else
					{
						while (!tmp.empty())
						{
							delete tmp.top();
							tmp.pop();
						}
						throw;
					}
					delete a;
				}
				catch (const std::exception &e)
				{
					while (!tmp.empty())
					{
						delete tmp.top();
						tmp.pop();
					}
					throw;
				}
				tmp.push(result);
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
		else if (numbers.find(rpn->at(i)[0]) != std::string::npos)
		{
			tmp.push(operandFactory.createOperand(Double, rpn->at(i)));
		}
		else
		{
			while (!tmp.empty())
			{
				delete tmp.top();
				tmp.pop();
			}
			throw (InvalidTokenException(rpn->at(i)));
		}
	}
	if (!tmp.empty())
	{
		while (!tmp.empty())
		{
			delete tmp.top();
			tmp.pop();
		}
		throw (LineMalformed());
	}
}
