#include <exceptions/InvalidArgumentException.class.hpp>

/*
** Constructors
*/
InvalidArgumentException::InvalidArgumentException(std::string const &message)
{
	_message = message;
}

InvalidArgumentException::InvalidArgumentException(const char *message)
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
std::string						InvalidArgumentException::getMessage() const
{
	return this->_message;
}

/*
** Public
*/
const char						*InvalidArgumentException::what() const throw()
{
	return this->_message.c_str();
}
