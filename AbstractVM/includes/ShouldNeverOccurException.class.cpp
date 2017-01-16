#include "ShouldNeverOccurException.class.hpp"

/*
** Constructors
*/
ShouldNeverOccurException::ShouldNeverOccurException(void) : _file("null"), _line(0) {}

ShouldNeverOccurException::ShouldNeverOccurException(const char *file, unsigned int line)
{
	if (file != NULL)
		_file = file;
	_line = line;
}

ShouldNeverOccurException::ShouldNeverOccurException(ShouldNeverOccurException const &src)
{
	*this = src;
}

/*
** Destructor
*/
ShouldNeverOccurException::~ShouldNeverOccurException(void) {}

/*
** Operator "=" Overload
*/
ShouldNeverOccurException		&ShouldNeverOccurException::operator=(ShouldNeverOccurException const &src)
{
	this->_file = src.getFile();
	this->_line = src.getLine();

	return *this;
}

/*
** Getter
*/
char const						*ShouldNeverOccurException::getFile(void)const
{
	return this->_file.c_str();
}

unsigned int					ShouldNeverOccurException::getLine(void) const
{
	return this->_line;
}

/*
** Public
*/
const char						*ShouldNeverOccurException::what(void) const throw()
{
	std::string message = "Should Never Occur exception was thrown at line ";

	message.append(std::to_string (this->_line));
	message.append("of the file ");
	message.append(this->_file);

	return message.c_str();
}
