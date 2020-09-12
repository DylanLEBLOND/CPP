#include <exceptions/DynamicLoadGUIException.class.hpp>

/*
** Constructors
*/
DynamicLoadGUIException::DynamicLoadGUIException (eGUI affectedGUI, std::string const &dlFunc, const char* dlErrorMessage)
{
	this->_message = "DynamicLoadGUI Error: GUI = \"";
	switch (affectedGUI)
	{
		case eGUI::SDL:
			this->_message += "SDL";
			break;
		case eGUI::SFML:
			this->_message += "SFML";
			break;
		default:
			this->_message += "Unknown";
			break;
	}
	this->_message += "\" | function = \"";
	this->_message += dlFunc;
	this->_message += "\" | dlerror message = \"";
	this->_message += dlErrorMessage;
	this->_message += "\".";
}

DynamicLoadGUIException::DynamicLoadGUIException (eGUI affectedGUI, const char *dlFunc, const char* dlErrorMessage)
{
	this->_message = "DynamicLoadGUI Error: GUI = \"";
	switch (affectedGUI)
	{
		case eGUI::SDL:
			this->_message += "SDL";
			break;
		case eGUI::SFML:
			this->_message += "SFML";
			break;
		default:
			this->_message += "Unknown";
			break;
	}
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
