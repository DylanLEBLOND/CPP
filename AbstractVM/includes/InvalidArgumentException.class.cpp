#include "InvalidArgumentException.class.hpp"

/*
** Constructors
*/
InvalidArgumentException::InvalidArgumentException(std::string &message)
{
	_message = message;
}

InvalidArgumentException::InvalidArgumentException(InvalidArgumentException const &src)
{
	*this = src;
}

/*
** Destructor
*/
InvalidArgumentException::~InvalidArgumentException() {}

/*
** Operator "=" Overload
*/
InvalidArgumentException		&InvalidArgumentException::operator=(InvalidArgumentException const &src)
{
	this->_message = src.getMessage();
	return *this;
}

/*
** Getter
*/
std::string				InvalidArgumentException::getInstruction() const
{
	return this->_message;
}

/*
** Public
*/
virtual const char		*InvalidArgumentException::what() const throw()
{
	return this->_message.c_str();
}
