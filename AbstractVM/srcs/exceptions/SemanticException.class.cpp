#include <exceptions/SemanticException.class.hpp>

/*
** Constructors
*/
SemanticException::SemanticException(std::string const &message)
{
	_message = message;
}

SemanticException::SemanticException(const char *message)
{
	_message = message;
}

SemanticException::SemanticException(SemanticException const &src)
{
	*this = src;
}

/*
** Destructor
*/
SemanticException::~SemanticException() {}

/*
** Operator "=" Overload
*/
SemanticException		&SemanticException::operator=(SemanticException const &src)
{
	this->_message = src.getMessage();
	return *this;
}

/*
** Getter
*/
std::string				SemanticException::getMessage() const
{
	return this->_message;
}

/*
** Public
*/
const char				*SemanticException::what() const throw()
{
	std::string outmessage = "Semantic Error: ";

	outmessage.append(this->_message);

	return outmessage.c_str();
}
