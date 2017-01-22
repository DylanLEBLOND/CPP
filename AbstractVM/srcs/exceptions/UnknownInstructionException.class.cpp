#include <exceptions/UnknownInstructionException.class.hpp>

/*
** Constructors
*/
UnknownInstructionException::UnknownInstructionException(std::string const &message)
{
	_message = message;
}

UnknownInstructionException::UnknownInstructionException(const char *message)
{
	_message = message;
}

UnknownInstructionException::UnknownInstructionException(UnknownInstructionException const &src)
{
	*this = src;
}

/*
** Destructor
*/
UnknownInstructionException::~UnknownInstructionException() {}

/*
** Operator "=" Overload
*/
UnknownInstructionException		&UnknownInstructionException::operator=(UnknownInstructionException const &src)
{
	this->_message = src.getMessage();
	return *this;
}

/*
** Getter
*/
std::string				UnknownInstructionException::getMessage() const
{
	return this->_message;
}

/*
** Public
*/
const char				*UnknownInstructionException::what() const throw()
{
	std::string outmessage = "Unknown Instruction: \"";

	outmessage.append(this->_message);
	outmessage.append("\"");

	return outmessage.c_str();
}
