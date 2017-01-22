#include <abstractVM.hpp>

void	file_workflow(char const *filename)
{
	std::fstream file;
	std::string line;
	bool exit = false;
	int lineNB = -1;
	Stack stack;
	eInstruction instruction;
	eOperandType operand;
	std::string value;

	file.open (filename, std::fstream::in);
	if (file.fail())
		throw FileStreamException ("Couldn't open \"" + std::string (filename) + "\"");

	while (!exit && std::getline (file, line))
	{
		lineNB++;
		try
		{
			if ((line.length() == 0) || (line.find (";") == 0))
				continue;

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
					getAssertData (line, operand, value);
					stack.assert(Operand (operand, value));
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
				case eInstruction::Exit:
					exit = true;
					continue;
				default:	//Unknown
					throw UnknownInstructionException(line);
					continue;
			}
		}
		catch (std::exception &e)
		{
			std::cerr << "Line " << lineNB << " : Error : " << e.what() << std::endl;
		}
	}
	if (!exit && !file.eof())
		throw FileStreamException ("An unknown error occurred during the reading of the file");
	if (!exit && file.eof())
		throw FileStreamException ("Missing \"Exit\" instruction at the end of the file");
}
