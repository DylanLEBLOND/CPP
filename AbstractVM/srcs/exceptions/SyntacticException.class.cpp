#include <exceptions/SyntacticException.class.hpp>

/*
** Constructors
*/
SyntacticException::SyntacticException(std::string const &message)
{
	_message = message;
}

SyntacticException::SyntacticException(const char *message)
{
	_message = message;
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
	this->_message = src.getMessage();
	return *this;
}

/*
** Getter
*/
std::string				SyntacticException::getMessage() const
{
	return this->_message;
}

/*
** Public
*/
const char				*SyntacticException::what() const throw()
{
	std::string outmessage = "Syntactic Error: ";

	outmessage.append(this->_message);

	return outmessage.c_str();
}
