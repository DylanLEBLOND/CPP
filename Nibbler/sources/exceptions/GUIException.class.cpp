#include <exceptions/GUIException.class.hpp>

/*
** Constructors
*/
GUIException::GUIException (std::string const &affectedGUI, std::string const &GUIFunc)
{
	this->_message = "GUI Error: GUI = \"";
	this->_message += affectedGUI;
	this->_message += "\" | function = \"";
	this->_message += GUIFunc;
	this->_message += "\".";
}

GUIException::GUIException (std::string const &affectedGUI, std::string const &GUIFunc, std::string const &GUIErrorMessage)
{
	this->_message = "GUI Error: GUI = \"";
	this->_message += affectedGUI;
	this->_message += "\" | function = \"";
	this->_message += GUIFunc;
	this->_message += "\" | library error message = \"";
	this->_message += GUIErrorMessage;
	this->_message += "\".";
}

GUIException::GUIException (const char *affectedGUI, const char *GUIFunc)
{
	this->_message = "GUI Error: GUI = \"";
	this->_message += affectedGUI;
	this->_message += "\" | function = \"";
	this->_message += GUIFunc;
	this->_message += "\".";
}

GUIException::GUIException (const char *affectedGUI, const char *GUIFunc, const char *GUIErrorMessage)
{
	this->_message = "GUI Error: GUI = \"";
	this->_message += affectedGUI;
	this->_message += "\" | function = \"";
	this->_message += GUIFunc;
	this->_message += "\" | library error message = \"";
	this->_message += GUIErrorMessage;
	this->_message += "\".";
}

GUIException::GUIException (GUIException const &src)
{
	*this = src;
}

/*
** Destructor
*/
GUIException::~GUIException (void) {}

/*
** Operator "=" Overload
*/
GUIException		&GUIException::operator= (GUIException const &src)
{
	this->_message = src.getMessage();
	return *this;
}

/*
** Getter
*/
std::string					GUIException::getMessage (void) const
{
	return this->_message;
}

/*
** Public
*/
const char					*GUIException::what (void) const throw()
{
	return this->_message.c_str();
}
