#include <abstractVM.hpp>

void 	standard_workflow ()
{
	bool run;
	std::string line;
	char const *str;
	eInstruction instruction;
	Stack stack;
	eOperandType operand;
	std::string value;

	run = true;
	while (run)
	{
		std::getline (std::cin, line);
		str = line.c_str();
		if (strcmp (str, ";;") == 0)
		{
			run = false;
			continue;
		}

		instruction = get_instruction (line);
		switch (instruction)
		{
			case eInstruction::Push:
				getPushData (line, operand, value);
				stack.push(Operand (operand, value));
				break;
			case eInstruction::Pop:
				stack.pop();
				break;
			case eInstruction::Dump:
				std::cout << stack.dump();
				break;
			case eInstruction::Assert:
				getAssertData (line, value);
				stack.assert(value);
				break;
			case eInstruction::Add:
				stack.add();
				break;
			case eInstruction::Sub:
				stack.sub();
				break;
			case eInstruction::Mul:
				stack.mul();
				break;
			case eInstruction::Div:
				stack.div();
				break;
			case eInstruction::Mod:
				stack.mod();
				break;
			case eInstruction::Print:
				std::cout << stack.print() << std::endl;
				break;
			default:	//Unknown
				throw UnknownInstructionException(line);
				continue;
		}
	}
}
