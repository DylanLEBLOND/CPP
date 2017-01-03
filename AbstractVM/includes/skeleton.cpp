#include "abstractVM.hpp"

eInstruction	get_instruction(std::string line)
{
	return Unknown;
}

void			getPushData(std::string line, eOperandType *operand, std::string *value)
{
	if (line.length() < 5)
		throw LexicalException ();




	return operand;
}
