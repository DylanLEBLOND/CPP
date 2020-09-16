#include <exceptions/DynamicLoadGUIException.class.hpp>

/*
** Constructors
*/
DynamicLoadGUIException::DynamicLoadGUIException (std::string const &affectedGUI, std::string const &dlFunc, const char* dlErrorMessage)
{
	this->_message = "DynamicLoadGUI Error: GUI = \"";
	this->_message += affectedGUI;
	this->_message += "\" | function = \"";
	this->_message += dlFunc;
	this->_message += "\" | dlerror message = \"";
	this->_message += dlErrorMessage;
	this->_message += "\".";
}

DynamicLoadGUIException::DynamicLoadGUIException (const char *affectedGUI, const char *dlFunc, const char* dlErrorMessage)
{
	this->_message = "DynamicLoadGUI Error: GUI = \"";
	this->_message += affectedGUI;
	this->_message += "\" | function = \"";
	this->_message += dlFunc;
	this->_message += "\" | dlerror message = \"";
	this->_message += dlErrorMessage;
	this->_message += "\".";
}

DynamicLoadGUIException::DynamicLoadGUIException (DynamicLoadGUIException const &src)
{
	*this = src;
}

/*
** Destructor
*/
DynamicLoadGUIException::~DynamicLoadGUIException (void) {}

/*
** Operator "=" Overload
*/
DynamicLoadGUIException		&DynamicLoadGUIException::operator= (DynamicLoadGUIException const &src)
{
	this->_message = src.getMessage();
	return *this;
}

/*
** Getter
*/
std::string					DynamicLoadGUIException::getMessage (void) const
{
	return this->_message;
}

/*
** Public
*/
const char					*DynamicLoadGUIException::what (void) const throw()
{
	return this->_message.c_str();
}
