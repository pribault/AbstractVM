#ifndef OPERAND_HPP
# define OPERAND_HPP

# include "IOperand.hpp"
# include <cstdint>
# include "OperandFactory.hpp"

template	<typename T>
class	Operand : public IOperand
{
	public:

		Operand(void) : _value(0), _str(std::to_string(static_cast<T>(0)))
		{
		}

		Operand(T b) : _value(b), _str(std::to_string(b))
		{
		}

		virtual ~Operand(void)
		{
		}

		virtual int	getPrecision(void) const
		{
			if (std::is_same<T, int8_t>::value)
				return (Int8);
			else if (std::is_same<T, int16_t>::value)
				return (Int16);
			else if (std::is_same<T, int32_t>::value)
				return (Int32);
			else if (std::is_same<T, float>::value)
				return (Float);
			else if (std::is_same<T, double>::value)
				return (Double);
			throw (UnknownTypeException());
		}

		virtual eOperandType getType(void) const
		{
			if (std::is_same<T, int8_t>::value)
				return (Int8);
			else if (std::is_same<T, int16_t>::value)
				return (Int16);
			else if (std::is_same<T, int32_t>::value)
				return (Int32);
			else if (std::is_same<T, float>::value)
				return (Float);
			else if (std::is_same<T, double>::value)
				return (Double);
			throw (UnknownTypeException());
		}

		virtual IOperand const	*operator+(IOperand const &rhs) const
		{
			switch (rhs.getType())
			{
				case Int8:
				{
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								_value + std::stoi(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								_value + std::stoi(rhs.toString()))));
					break;
				}
				case Int16:
				{
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								_value + std::stoi(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								_value + std::stoi(rhs.toString()))));
					break;
				}
				case Int32:
				{
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								_value + std::stoi(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								_value + std::stoi(rhs.toString()))));
					break;
				}
				case Float:
				{
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								_value + std::stod(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								_value + std::stod(rhs.toString()))));
					break;
				}
				case Double:
				{
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								_value + std::stod(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								_value + std::stod(rhs.toString()))));
					break;
				}
				default:
				{
					throw (UnknownTypeException());
					break;
				}
			}
		}

		virtual IOperand const	*operator-(IOperand const &rhs) const
		{
			switch (rhs.getType())
			{
				case Int8:
				{
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								_value - std::stoi(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								_value - std::stoi(rhs.toString()))));
					break;
				}
				case Int16:
				{
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								_value - std::stoi(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								_value - std::stoi(rhs.toString()))));
					break;
				}
				case Int32:
				{
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								_value - std::stoi(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								_value - std::stoi(rhs.toString()))));
					break;
				}
				case Float:
				{
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								_value - std::stod(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								_value - std::stod(rhs.toString()))));
					break;
				}
				case Double:
				{
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								_value - std::stod(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								_value - std::stod(rhs.toString()))));
					break;
				}
				default:
				{
					throw (UnknownTypeException());
					break;
				}
			}
		}

		virtual IOperand const	*operator*(IOperand const &rhs) const
		{
			switch (rhs.getType())
			{
				case Int8:
				{
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								_value * std::stoi(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								_value * std::stoi(rhs.toString()))));
					break;
				}
				case Int16:
				{
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								_value * std::stoi(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								_value * std::stoi(rhs.toString()))));
					break;
				}
				case Int32:
				{
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								_value * std::stoi(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								_value * std::stoi(rhs.toString()))));
					break;
				}
				case Float:
				{
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								_value * std::stod(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								_value * std::stod(rhs.toString()))));
					break;
				}
				case Double:
				{
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								_value * std::stod(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								_value * std::stod(rhs.toString()))));
					break;
				}
				default:
				{
					throw (UnknownTypeException());
					break;
				}
			}
		}

		virtual IOperand const	*operator/(IOperand const &rhs) const
		{
			switch (rhs.getType())
			{
				case Int8:
				{
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								_value / std::stoi(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								_value / std::stoi(rhs.toString()))));
					break;
				}
				case Int16:
				{
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								_value / std::stoi(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								_value / std::stoi(rhs.toString()))));
					break;
				}
				case Int32:
				{
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								_value / std::stoi(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								_value / std::stoi(rhs.toString()))));
					break;
				}
				case Float:
				{
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								_value / std::stod(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								_value / std::stod(rhs.toString()))));
					break;
				}
				case Double:
				{
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								_value / std::stod(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								_value / std::stod(rhs.toString()))));
					break;
				}
				default:
				{
					throw (UnknownTypeException());
					break;
				}
			}
		}

		virtual IOperand const	*operator%(IOperand const &rhs) const
		{
			if (getType() == Float ||
				getType() == Double)
				throw (FloatModulo());
			switch (rhs.getType())
			{
				case Int8:
				{
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								static_cast<int32_t>(_value) % std::stoi(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								static_cast<int32_t>(_value) % std::stoi(rhs.toString()))));
					break;
				}
				case Int16:
				{
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								static_cast<int32_t>(_value) % std::stoi(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								static_cast<int32_t>(_value) % std::stoi(rhs.toString()))));
					break;
				}
				case Int32:
				{
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								static_cast<int32_t>(_value) % std::stoi(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								static_cast<int32_t>(_value) % std::stoi(rhs.toString()))));
					break;
				}
				case Float:
				{
					throw (FloatModulo());
					break;
				}
				case Double:
				{
					throw (FloatModulo());
					break;
				}
				default:
				{
					throw (UnknownTypeException());
					break;
				}
			}
		}

		virtual std::string const	&toString(void) const
		{
			return (_str);
		}

		class	UnknownTypeException : std::exception
		{
			public:
				virtual const char	*what(void) const noexcept
				{
					return ("unknown type");
				}
		};

		class	FloatModulo : std::exception
		{
			public:
				virtual const char	*what(void) const noexcept
				{
					return ("modulo applied to floating point number");
				}
		};

	private:

		Operand(const Operand &b)
		{
			*this = b;
		}

		Operand		&operator=(const Operand &b)
		{
			(void)b;
			_value = 0;
			_str = std::to_string(static_cast<T>(0));
		}

		T			_value;
		std::string	_str;
};

#endif
