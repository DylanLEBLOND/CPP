#include <exceptions/UnknownEventException.class.hpp>

/*
** Constructors
*/
UnknownEventException::UnknownEventException (std::string const &affectedGUI, std::string const &receivedEvent)
{
	this->_message = "Unknown Event Error: GUI = \"";
	this->_message += affectedGUI;
	this->_message += "\" | Received Event = \"";
	this->_message += receivedEvent;
	this->_message += "\".";
}

UnknownEventException::UnknownEventException (const char *affectedGUI, const char *receivedEvent)
{
	this->_message = "Unknown Event Error: GUI = \"";
	this->_message += affectedGUI;
	this->_message += "\" | Received Event = \"";
	this->_message += receivedEvent;
	this->_message += "\".";
}

UnknownEventException::UnknownEventException (UnknownEventException const &src)
{
	*this = src;
}

/*
** Destructor
*/
UnknownEventException::~UnknownEventException (void) {}

/*
** Operator "=" Overload
*/
UnknownEventException		&UnknownEventException::operator= (UnknownEventException const &src)
{
	this->_message = src.getMessage();
	return *this;
}

/*
** Getter
*/
std::string					UnknownEventException::getMessage (void) const
{
	return this->_message;
}

/*
** Public
*/
const char					*UnknownEventException::what (void) const throw()
{
	return this->_message.c_str();
}
