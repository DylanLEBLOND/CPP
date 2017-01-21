#include "abstractVM.hpp"

void 	standard_workflow () throw (std::exception)
{
	bool run;
	std::string line;
	char *str;
	eInstruction instruction;
	Stack stack;
	eOperandType operand;
	std::string value;

	if (DEBUG)
		std::cout << "Debut Standard Workflow" << std::endl;

	run = true;
	while (run)
	{
		std::getline (std::cin, line);
		if (DEBUG)
			std::cout << "Entree = " << line << std::endl;

		str = line.c_str();
		if (strcmp (str, ";;") == 0)
		{
			run = false;
			continue;
		}

		instruction = get_instruction (line);
		switch (instruction)
		{
			case Push:
				getPushData (line, &operand, &value);
				stack.push(operand, value);
				break;

			default:	//Unknown
				throw UnknownInstructionException();
				continue;
		}
	}

	if (DEBUG)
		std::cout << "Fin Standard Workflow" << std::endl;
}
