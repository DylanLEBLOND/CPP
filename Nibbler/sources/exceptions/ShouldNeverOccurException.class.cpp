#include <exceptions/ShouldNeverOccurException.class.hpp>

/*
** Constructors
*/
ShouldNeverOccurException::ShouldNeverOccurException (void) : _file("null"), _line(0) {}

ShouldNeverOccurException::ShouldNeverOccurException (const char *file, unsigned int line)
{
	if (file != NULL)
	{
		this->_message = "Should Never Occur exception was thrown at line ";

		this->_message.append (std::to_string (line));
		this->_message.append (" of the file ");
		this->_message.append (file);

		this->_file = file;
	}

	this->_line = line;
}

ShouldNeverOccurException::ShouldNeverOccurException (ShouldNeverOccurException const &src)
{
	*this = src;
}

/*
** Destructor
*/
ShouldNeverOccurException::~ShouldNeverOccurException (void) {}

/*
** Operator "=" Overload
*/
ShouldNeverOccurException		&ShouldNeverOccurException::operator= (ShouldNeverOccurException const &src)
{
	this->_file = src.getFile();
	this->_line = src.getLine();

	return *this;
}

/*
** Getter
*/
char const						*ShouldNeverOccurException::getFile (void)const
{
	return this->_file.c_str();
}

unsigned int					ShouldNeverOccurException::getLine (void) const
{
	return this->_line;
}

std::string						ShouldNeverOccurException::getMessage (void) const
{
	return this->_message;
}

/*
** Public
*/
const char						*ShouldNeverOccurException::what (void) const throw()
{
	return this->_message.c_str();
}
