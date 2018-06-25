#ifndef IOPERAND_HPP
# define IOPERAND_HPP

# include <string>

typedef enum	eOperandType
{
	Int8 = 0,
	Int16 = 1,
	Int32 = 2,
	Float = 3,
	Double = 4
}				eOperandType;

class	IOperand
{
	public:

		virtual ~IOperand(void) {}

		virtual int	getPrecision(void) const = 0;
		virtual eOperandType	getType(void) const = 0;

		virtual IOperand const	*operator+(IOperand const &rhs) const = 0;
		virtual IOperand const	*operator-(IOperand const &rhs) const = 0;
		virtual IOperand const	*operator*(IOperand const &rhs) const = 0;
		virtual IOperand const	*operator/(IOperand const &rhs) const = 0;
		virtual IOperand const	*operator%(IOperand const &rhs) const = 0;
		virtual bool			operator==(IOperand const &rhs) const = 0;
		virtual bool			operator!=(IOperand const &rhs) const = 0;
		virtual bool			operator<(IOperand const &rhs) const = 0;
		virtual bool			operator<=(IOperand const &rhs) const = 0;
		virtual bool			operator>(IOperand const &rhs) const = 0;
		virtual bool			operator>=(IOperand const &rhs) const = 0;

		virtual std::string const	&toString(void) const = 0;
};

#endif
