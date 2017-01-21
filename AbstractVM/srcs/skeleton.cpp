#include <abstractVM.hpp>

eInstruction	get_instruction(std::string const &line)
{
	if (line.find("push") == 0)
	{
		/* throw Exception() */
		return eInstruction::Push;
	}
	if (line.find("pop") == 0)
	{
		if (line.length() > 3)
			return eInstruction::Unknown;
		return eInstruction::Pop;
	}
	if (line.find("dump") == 0)
	{
		if (line.length() > 4)
			return eInstruction::Unknown;
		return eInstruction::Dump;
	}
	if (line.find("assert") == 0)
	{
		/* throw Exception() */
		return eInstruction::Assert;
	}
	if (line.find("add") == 0)
	{
		if (line.length() > 3)
			return eInstruction::Unknown;
		return eInstruction::Add;
	}
	if (line.find("sub") == 0)
	{
		if (line.length() > 3)
			return eInstruction::Unknown;
		return eInstruction::Sub;
	}
	if (line.find("mul") == 0)
	{
		if (line.length() > 3)
			return eInstruction::Unknown;
		return eInstruction::Mul;
	}
	if (line.find("div") == 0)
	{
		if (line.length() > 3)
			return eInstruction::Unknown;
		return eInstruction::Div;
	}
	if (line.find("mod") == 0)
	{
		if (line.length() > 3)
			return eInstruction::Unknown;
		return eInstruction::Mod;
	}
	if (line.find("print") == 0)
	{
		if (line.length() > 5)
			return eInstruction::Unknown;
		return eInstruction::Print;
	}

	return eInstruction::Unknown;
}

void			getPushData(std::string const &line, eOperandType &operand, std::string &value)
{
	(void)line;
	operand = eOperandType::Unknown;
	value = "null";
}

void			getAssertData(std::string const &line, std::string &value)
{
	(void)line;
	value = "null";
}
