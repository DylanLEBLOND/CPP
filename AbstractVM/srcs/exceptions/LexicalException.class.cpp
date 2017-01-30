#include <exceptions/LexicalException.class.hpp>

/*
** Constructors
*/
LexicalException::LexicalException(std::string const &message)
{
	_message = message;
}

LexicalException::LexicalException(const char *message)
{
	_message = message;
}

LexicalException::LexicalException(LexicalException const &src)
{
	*this = src;
}

/*
** Destructor
*/
LexicalException::~LexicalException() {}

/*
** Operator "=" Overload
*/
LexicalException		&LexicalException::operator=(LexicalException const &src)
{
	this->_message = src.getMessage();
	return *this;
}

/*
** Getter
*/
std::string				LexicalException::getMessage() const
{
	return this->_message;
}

/*
** Public
*/
const char				*LexicalException::what() const throw()
{
	std::string outmessage = "Lexical Error: ";

	outmessage.append(this->_message);

	return outmessage.c_str();
}
