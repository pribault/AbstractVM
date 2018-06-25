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
			else if (std::is_same<T, int64_t>::value)
				return (Int64);
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
			else if (std::is_same<T, int64_t>::value)
				return (Int64);
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
				case Int16:
				case Int32:
				case Int64:
				{
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								_value + std::stoll(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								_value + std::stoll(rhs.toString()))));
					break;
				}
				case Float:
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
				case Int16:
				case Int32:
				case Int64:
				{
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								_value - std::stoll(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								_value - std::stoll(rhs.toString()))));
					break;
				}
				case Float:
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
				case Int16:
				case Int32:
				case Int64:
				{
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								_value * std::stoll(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								_value * std::stoll(rhs.toString()))));
					break;
				}
				case Float:
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
				case Int16:
				case Int32:
				case Int64:
				{
					if (!std::stoll(rhs.toString()))
						throw (DivisionByZeroException());
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								_value / std::stoll(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								_value / std::stoll(rhs.toString()))));
					break;
				}
				case Float:
				case Double:
				{
					if (!std::stod(rhs.toString()))
						throw (DivisionByZeroException());
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
				throw (FloatModulus());
			switch (rhs.getType())
			{
				case Int8:
				case Int16:
				case Int32:
				case Int64:
				{
					if (!std::stoll(rhs.toString()))
						throw (DivisionByZeroException());
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								static_cast<int64_t>(_value) % std::stoll(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								static_cast<int64_t>(_value) % std::stoll(rhs.toString()))));
					break;
				}
				case Float:
				case Double:
				{
					throw (FloatModulus());
					break;
				}
				default:
				{
					throw (UnknownTypeException());
					break;
				}
			}
		}

		virtual IOperand const	*operator&(IOperand const &rhs) const
		{
			if (getType() == Float || getType() == Double)
				throw (BinaryOnFloatException());
			switch (rhs.getType())
			{
				case Int8:
				case Int16:
				case Int32:
				case Int64:
				{
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								static_cast<int64_t>(_value) & std::stoll(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								static_cast<int64_t>(_value) & std::stoll(rhs.toString()))));
					break;
				}
				case Float:
				case Double:
				{
					throw (BinaryOnFloatException());
					break;
				}
				default:
				{
					throw (UnknownTypeException());
					break;
				}
			}
		}

		virtual IOperand const	*operator|(IOperand const &rhs) const
		{
			if (getType() == Float || getType() == Double)
				throw (BinaryOnFloatException());
			switch (rhs.getType())
			{
				case Int8:
				case Int16:
				case Int32:
				case Int64:
				{
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								static_cast<int64_t>(_value) | std::stoll(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								static_cast<int64_t>(_value) | std::stoll(rhs.toString()))));
					break;
				}
				case Float:
				case Double:
				{
					throw (BinaryOnFloatException());
					break;
				}
				default:
				{
					throw (UnknownTypeException());
					break;
				}
			}
		}

		virtual IOperand const	*operator^(IOperand const &rhs) const
		{
			if (getType() == Float || getType() == Double)
				throw (BinaryOnFloatException());
			switch (rhs.getType())
			{
				case Int8:
				case Int16:
				case Int32:
				case Int64:
				{
					if (getPrecision() < rhs.getPrecision())
						return (operandFactory.createOperand(
							rhs.getType(),
							std::to_string(
								static_cast<int64_t>(_value) ^ std::stoll(rhs.toString()))));
					else
						return (operandFactory.createOperand(
							getType(),
							std::to_string(
								static_cast<int64_t>(_value) ^ std::stoll(rhs.toString()))));
					break;
				}
				case Float:
				case Double:
				{
					throw (BinaryOnFloatException());
					break;
				}
				default:
				{
					throw (UnknownTypeException());
					break;
				}
			}
		}

		virtual bool			operator==(IOperand const &rhs) const
		{
			const IOperand	*result;
			bool			ret;

			result = *this - rhs;
			ret = (stod(result->toString()) == 0) ? true : false;
			delete result;
			return (ret);
		}

		virtual bool			operator!=(IOperand const &rhs) const
		{
			const IOperand	*result;
			bool			ret;

			result = *this - rhs;
			ret = (stod(result->toString()) != 0) ? true : false;
			delete result;
			return (ret);
		}

		virtual bool			operator<(IOperand const &rhs) const
		{
			const IOperand	*result;
			bool			ret;

			result = *this - rhs;
			ret = (stod(result->toString()) < 0) ? true : false;
			delete result;
			return (ret);
		}

		virtual bool			operator<=(IOperand const &rhs) const
		{
			const IOperand	*result;
			bool			ret;

			result = *this - rhs;
			ret = (stod(result->toString()) <= 0) ? true : false;
			delete result;
			return (ret);
		}

		virtual bool			operator>(IOperand const &rhs) const
		{
			const IOperand	*result;
			bool			ret;

			result = *this - rhs;
			ret = (stod(result->toString()) > 0) ? true : false;
			delete result;
			return (ret);
		}

		virtual bool			operator>=(IOperand const &rhs) const
		{
			const IOperand	*result;
			bool			ret;

			result = *this - rhs;
			ret = (stod(result->toString()) >= 0) ? true : false;
			delete result;
			return (ret);
		}

		virtual std::string const	&toString(void) const
		{
			return (_str);
		}

		class	UnknownTypeException : public std::exception
		{
			public:
				virtual const char	*what(void) const noexcept
				{
					return ("unknown type");
				}
		};

		class	FloatModulus : public std::exception
		{
			public:
				virtual const char	*what(void) const noexcept
				{
					return ("modulus applied to floating point number");
				}
		};

		class	DivisionByZeroException : public std::exception
		{
			public:
				virtual const char	*what(void) const noexcept
				{
					return ("division or modulus by zero");
				}
		};

		class	BinaryOnFloatException : public std::exception
		{
			public:
				virtual const char	*what(void) const noexcept
				{
					return ("binary operator on floating point numbers");
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
