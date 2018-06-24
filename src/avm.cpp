#include "avm.hpp"

std::vector<std::string>	functions = {
	"push",
	"pop",
	"dump",
	"assert",
	"add",
	"sub",
	"mul",
	"div",
	"mod",
	"print",
	"exit",
	";;",
	"int8",
	"int16",
	"int32",
	"float",
	"double"
};
std::vector<std::string>	operators = {"+", "-", "/", "%", "*"};
std::vector<std::string>	brackets = {"(", ")", "{", "}", "[", "]"};
std::vector<std::string>	comments = {";", "#"};

void	run(std::istream &stream)
{
	std::stack<IOperand *>		stack;
	std::vector<std::string>	*rpn;
	std::string					line;

	while (getline(stream, line))
	{
		try
		{
			rpn = ShuntingYard(line, functions, operators, brackets, comments);
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
			rpn = NULL;
		}
		if (rpn)
		{
			std::cout << "rpn: " << std::endl;
			for (size_t j = 0; j < rpn->size(); j++)
				std::cout << "\t" << rpn->at(j);
			std::cout << std::endl;
			try
			{
				execute(rpn, stack);
			}
			catch (const std::exception &e)
			{
				std::cerr << e.what() << std::endl;
			}
			delete rpn;
		}
	}
}

int		main(int argc, char **argv)
{
	std::ifstream				file;

	if (argc == 1)
		run(std::cin);
	else
		for (int i = 1; i < argc; i++)
		{
			file.open(argv[i], std::ifstream::in);
			if (file.is_open())
			{
				run(file);
				file.close();
			}
			else
				std::cerr << "cannot open " << argv[i] << std::endl;
		}
	return (0);
}
