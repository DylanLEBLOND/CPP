#include <exceptions/DivModByZeroException.class.hpp>

/*
** Constructors
*/
DivModByZeroException::DivModByZeroException(std::string const &message)
{
	_message = message;
}

DivModByZeroException::DivModByZeroException(const char *message)
{
	_message = message;
}

DivModByZeroException::DivModByZeroException(DivModByZeroException const &src)
{
	*this = src;
}

/*
** Destructor
*/
DivModByZeroException::~DivModByZeroException() {}

/*
** Operator "=" Overload
*/
DivModByZeroException		&DivModByZeroException::operator=(DivModByZeroException const &src)
{
	this->_message = src.getMessage();
	return *this;
}

/*
** Getter
*/
std::string				DivModByZeroException::getMessage() const
{
	return this->_message;
}

/*
** Public
*/
const char				*DivModByZeroException::what() const throw()
{
	std::string outmessage = "Divison/Modulo By Zero: ";

	outmessage.append(this->_message);

	return outmessage.c_str();
}
