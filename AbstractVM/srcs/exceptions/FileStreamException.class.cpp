#include <exceptions/FileStreamException.class.hpp>

/*
** Constructors
*/
FileStreamException::FileStreamException(std::string const &message)
{
	_message = message;
}

FileStreamException::FileStreamException(const char *message)
{
	_message = message;
}

FileStreamException::FileStreamException(FileStreamException const &src)
{
	*this = src;
}

/*
** Destructor
*/
FileStreamException::~FileStreamException() {}

/*
** Operator "=" Overload
*/
FileStreamException		&FileStreamException::operator=(FileStreamException const &src)
{
	this->_message = src.getMessage();
	return *this;
}

/*
** Getter
*/
std::string				FileStreamException::getMessage() const
{
	return this->_message;
}

/*
** Public
*/
const char				*FileStreamException::what() const throw()
{
	return this->_message.c_str();
}
