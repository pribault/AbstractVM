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
	"jmp",
	"cmp",
	"je",
	"jne",
	"jl",
	"jle",
	"jg",
	"jge",
	"inc",
	"dec",
	"int8",
	"int16",
	"int32",
	"float",
	"double"
};
std::vector<std::string>	operators = {"+", "-", "/", "%", "*"};
std::vector<std::string>	brackets = {"(", ")", "{", "}", "[", "]"};
std::vector<std::string>	comments = {";", "#"};

void	debug(std::vector<std::string> *rpn)
{
	for (size_t i = 0; i < rpn->size(); i++)
		log << "\t" << rpn->at(i);
	log << std::endl;
}

void	run(std::istream &stream, bool file)
{
	std::vector<const IOperand *>			stack;
	std::vector<std::vector<std::string> *>	program;
	std::vector<std::string>				*rpn;
	std::string								line;
	bool									exited = false;
	bool									end = false;

	while (!end && getline(stream, line))
	{
		try
		{
			rpn = ShuntingYard(line, functions, operators, brackets, comments);
			if (rpn->size())
			{
				if (!file && rpn->size() == 1 && rpn->back() == ";;")
					end = true;
				else
					program.push_back(rpn);
			}
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
			rpn = NULL;
		}
	}
	log << "___program_start___" << std::endl;
	for (size_t i = 0; i < program.size(); i++)
	{
		log << "\t[" << i << "]";
		debug(program[i]);
	}
	log << "___program_end___" << std::endl;
	for (size_t i = 0; i < program.size(); i++)
	{
		rpn = program[i];
		try
		{
			execute(rpn, stack, i);
		}
		catch (const ExitException &e)
		{
			exited = true;
			break;
		}
		catch (const std::exception &e)
		{
			std::cerr << "error: " << e.what() << std::endl;
		}
	}
	for (size_t i = 0; i < program.size(); i++)
		delete program[i];
	if (!exited)
		std::cerr << "program didn't ended with exit" << std::endl;
}

int		main(int argc, char **argv)
{
	std::ifstream				file;

	if (argc == 1)
		run(std::cin, false);
	else
		for (int i = 1; i < argc; i++)
		{
			file.open(argv[i], std::ifstream::in);
			if (file.is_open())
			{
				run(file, true);
				file.close();
			}
			else
				std::cerr << "cannot open " << argv[i] << std::endl;
		}
	return (0);
}
