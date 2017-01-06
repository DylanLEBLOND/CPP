#include "OverflowException.class.hpp"

/*
** Constructors
*/
OverflowException::OverflowException(std::string &message)
{
	_message = message;
}

OverflowException::OverflowException(OverflowException const &src)
{
	*this = src;
}

/*
** Destructor
*/
OverflowException::~OverflowException() {}

/*
** Operator "=" Overload
*/
OverflowException		&OverflowException::operator=(OverflowException const &src)
{
	this->_message = src.getMessage();
	return *this;
}

/*
** Getter
*/
std::string				OverflowException::getMessage() const
{
	return this->_message;
}

/*
** Public
*/
virtual const char		*OverflowException::what() const throw()
{
	std::string outmessage = "Overflow: ";

	outmessage.append(this->_message);

	return outmessage.c_str();
}
