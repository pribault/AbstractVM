#include "avm.hpp"
#include <iostream>
#include <fstream>

static std::vector<std::string>	functions = {{"push"}};
static std::vector<std::string>	operators = {{"+"}};

int		main(int argc, char **argv)
{
	std::vector<std::string>	*rpn;
	std::ifstream				file;
	std::string					line;

	if (argc == 1)
	{
		while (getline(std::cin, line))
		{
			rpn = ShuntingYard(line, functions, operators);
			std::cout << "rpn: " << std::endl;
			for (size_t j = 0; j < rpn->size(); j++)
				std::cout << "\t" << rpn->at(j);
			delete rpn;
		}
	}
	else
		for (int i = 1; i < argc; i++)
		{
			file.open(argv[i], std::ifstream::in);
			if (file.is_open())
			{
				while (getline(file, line))
				{
					rpn = ShuntingYard(line, functions, operators);
					std::cout << "rpn: " << std::endl;
					for (size_t j = 0; j < rpn->size(); j++)
						std::cout << "\t" << rpn->at(j);
					delete rpn;
				}
				file.close();
			}
		}
	return (0);
}
