#include "OperandFactory.hpp"
#include "Operand.hpp"
#include <stdexcept>

OperandFactory	operandFactory;

typedef IOperand const *	(OperandFactory::*t_constructor)(std::string const &) const;

typedef struct		s_table
{
	eOperandType	type;
	t_constructor	constructor;
}					t_table;

IOperand const	*OperandFactory::createOperand(eOperandType type, std::string const &value) const
{
	static const t_table	table[] = {
		{Int8, &OperandFactory::createInt8},
		{Int16, &OperandFactory::createInt16},
		{Int32, &OperandFactory::createInt32},
		{Int64, &OperandFactory::createInt64},
		{Float, &OperandFactory::createFloat},
		{Double, &OperandFactory::createDouble},
		{Int8, NULL}
	};

	for (size_t i = 0; table[i].constructor; i++)
		if (type == table[i].type)
			return ((this->*table[i].constructor)(value));
	return (NULL);
}

IOperand const	*OperandFactory::createInt8(std::string const &value) const
{
	IOperand	*result;

	result = new Operand<int8_t>(std::stoi(value));
	if (std::stoll(result->toString()) != std::stoll(value))
		throw (std::out_of_range("stoi: out of range"));
	return (static_cast<IOperand const *>(result));
}

IOperand const	*OperandFactory::createInt16(std::string const &value) const
{
	IOperand	*result;

	result = new Operand<int16_t>(std::stoi(value));
	if (std::stoll(result->toString()) != std::stoll(value))
		throw (std::out_of_range("stoi: out of range"));
	return (static_cast<IOperand const *>(result));
}

IOperand const	*OperandFactory::createInt32(std::string const &value) const
{
	IOperand	*result;

	result = new Operand<int32_t>(std::stoi(value));
	if (std::stoll(result->toString()) != std::stoll(value))
		throw (std::out_of_range("stoi: out of range"));
	return (static_cast<IOperand const *>(result));
}

IOperand const	*OperandFactory::createInt64(std::string const &value) const
{
	return (static_cast<IOperand const *>(new Operand<int64_t>(std::stoll(value))));
}

IOperand const	*OperandFactory::createFloat(std::string const &value) const
{
	return (static_cast<IOperand const *>(new Operand<float>(std::stof(value))));
}

IOperand const	*OperandFactory::createDouble(std::string const &value) const
{
	return (static_cast<IOperand const *>(new Operand<double>(std::stod(value))));
}
