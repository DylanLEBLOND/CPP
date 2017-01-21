#include <exceptions/UnderflowException.class.hpp>

/*
** Constructors
*/
UnderflowException::UnderflowException(std::string const &message)
{
	_message = message;
}

UnderflowException::UnderflowException(const char *message)
{
	_message = message;
}

UnderflowException::UnderflowException(UnderflowException const &src)
{
	*this = src;
}

/*
** Destructor
*/
UnderflowException::~UnderflowException() {}

/*
** Operator "=" Overload
*/
UnderflowException		&UnderflowException::operator=(UnderflowException const &src)
{
	this->_message = src.getMessage();
	return *this;
}

/*
** Getter
*/
std::string				UnderflowException::getMessage() const
{
	return this->_message;
}

/*
** Public
*/
const char				*UnderflowException::what() const throw()
{
	std::string outmessage = "Underflow: ";

	outmessage.append(this->_message);

	return outmessage.c_str();
}
