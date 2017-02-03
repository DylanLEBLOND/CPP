#include <abstractVM.hpp>

void 	standard_workflow ()
{
	std::string line;
	bool run;
	int lineNB = 0;
	bool exit = false;
	bool error_occured = false;
	Stack stack;
	eInstruction instruction;
	eOperandType operand;
	std::string value;
	std::string message;

	message.clear();
	run = true;
	while (run)
	{
		lineNB++;

		std::getline (std::cin, line);
		if ((line.length() == 2) && (line.compare (";;") == 0))
		{
			run = false;
			continue;
		}

		if ((line.length() == 0) || (line.find (";") == 0))
			continue;

		if (exit || error_occured)
			continue;

		instruction = get_instruction (line);
		try
		{
			switch (instruction)
			{
				case eInstruction::Push:
					getPushData (line, operand, value);
					stack.push(operand, value);
					break;
				case eInstruction::Pop:
					stack.pop();
					break;
				case eInstruction::Dump:
					message.append (stack.dump());
					break;
				case eInstruction::Assert:
					getAssertData (line, operand, value);
					stack.assert(operand, value);
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
					message += stack.print();
					message += '\n';
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
			message += "Line ";
			message +=  std::to_string (lineNB);
			message.append (" : Error : ");

			std::string tmp = e.what();
			message += tmp;
			message += '\n';
			error_occured = true;
		}
	}
	if (!error_occured && !exit)
		throw FileStreamException ("Missing \"Exit\" instruction at the end of input");

	std::cout << message;
}
