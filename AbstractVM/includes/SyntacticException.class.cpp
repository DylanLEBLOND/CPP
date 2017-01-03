#include "SyntacticException.class.hpp"

/*
** Constructors
*/
SyntacticException::SyntacticException(eInstruction instruction)
{
	switch (instruction)
	{
		case eInstruction::Push:
			this->_instruction = "Push";
			break;
		case eInstruction::Assert:
			this->_instruction = "Assert";
			break;
		default:		//Unknown
			this->_instruction = "Unknown";
			break;
	}
}

SyntacticException::SyntacticException(SyntacticException const &src)
{
	*this = src;
}

/*
** Destructor
*/
SyntacticException::~SyntacticException() {}

/*
** Operator "=" Overload
*/
SyntacticException		&SyntacticException::operator=(SyntacticException const &src)
{
	this->_instruction = src.getInstruction();
	return *this;
}

/*
** Getter
*/
std::string				SyntacticException::getInstruction() const
{
	return this->_instruction;
}

/*
** Public
*/
virtual const char		*SyntacticException::what() const throw()
{
	std::string message = "Bad syntax for:";

	message.append(this->_instruction);
	message.append("> Instruction");

	return message.c_str();
}
