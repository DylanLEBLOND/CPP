#include <exceptions/StackException.class.hpp>

/*
** Constructors
*/
StackException::StackException(std::string const &message)
{
	_message = message;
}

StackException::StackException(const char *message)
{
	_message = message;
}

StackException::StackException(StackException const &src)
{
	*this = src;
}

/*
** Destructor
*/
StackException::~StackException() {}

/*
** Operator "=" Overload
*/
StackException		&StackException::operator=(StackException const &src)
{
	this->_message = src.getMessage();
	return *this;
}

/*
** Getter
*/
std::string				StackException::getMessage() const
{
	return this->_message;
}

/*
** Public
*/
const char				*StackException::what() const throw()
{
	return this->_message.c_str();
}
