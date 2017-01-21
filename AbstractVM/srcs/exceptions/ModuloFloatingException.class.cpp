#include <exceptions/ModuloFloatingException.class.hpp>

/*
** Constructors
*/
ModuloFloatingException::ModuloFloatingException(std::string const &message)
{
	_message = message;
}

ModuloFloatingException::ModuloFloatingException(const char *message)
{
	_message = message;
}

ModuloFloatingException::ModuloFloatingException(ModuloFloatingException const &src)
{
	*this = src;
}

/*
** Destructor
*/
ModuloFloatingException::~ModuloFloatingException() {}

/*
** Operator "=" Overload
*/
ModuloFloatingException		&ModuloFloatingException::operator=(ModuloFloatingException const &src)
{
	this->_message = src.getMessage();
	return *this;
}

/*
** Getter
*/
std::string				ModuloFloatingException::getMessage() const
{
	return this->_message;
}

/*
** Public
*/
const char				*ModuloFloatingException::what() const throw()
{
	std::string outmessage = "Modulo Floating Number: ";

	outmessage.append(this->_message);

	return outmessage.c_str();
}
