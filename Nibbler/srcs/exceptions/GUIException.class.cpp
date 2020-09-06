#include <exceptions/GUIException.class.hpp>

/*
** Constructors
*/
GUIException::GUIException (eGUI affectedGUI, std::string const &GUIFunc)
{
	this->_message = "GUI Error: GUI = \"";
	switch (affectedGUI)
	{
		case eGUI::SDL:
			this->_message += "SDL";
			break;
		case eGUI::SFML:
			this->_message += "SFML";
			break;
		case eGUI::openGL:
			this->_message += "openGLL";
			break;
		default:
			this->_message += "Unknown";
			break;
	}
	this->_message += "\" | function = \"";
	this->_message += GUIFunc;
	this->_message += "\".";
}

GUIException::GUIException (eGUI affectedGUI, const char *GUIFunc)
{
	this->_message = "GUI Error: GUI = \"";
	switch (affectedGUI)
	{
		case eGUI::SDL:
			this->_message += "SDL";
			break;
		case eGUI::SFML:
			this->_message += "SFML";
			break;
		case eGUI::openGL:
			this->_message += "openGLL";
			break;
		default:
			this->_message += "Unknown";
			break;
	}
	this->_message += "\" | function = \"";
	this->_message += GUIFunc;
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
