#include <exceptions/UnknownEventException.class.hpp>

/*
** Constructors
*/
UnknownEventException::UnknownEventException(eGUI affectedGUI, eGUIEvent receivedEvent)
{
	this->_message = "Unknown Event Error: GUI = \"";
	switch (affectedGUI)
	{
		case eGUI::SDL:
			this->_message += "SDL";
			break;
		case eGUI::MinilibX:
			this->_message += "MinilibX";
			break;
		case eGUI::openGL:
			this->_message += "openGLL";
			break;
		default:
			this->_message += "unknownGUI";
			break;
	}
	this->_message += "\" | Received Event = \"";
	switch (receivedEvent)
	{
		case eGUIEvent::p1GoLeft:
			this->_message += "p1GoLeft";
			break;
		case eGUIEvent::p1GoRight:
			this->_message += "p1GoRight";
			break;
		case eGUIEvent::p1GoUp:
			this->_message += "p1GoUp";
			break;
		case eGUIEvent::p1GoDown:
			this->_message += "p1GoDown";
			break;
		case eGUIEvent::p2GoLeft:
			this->_message += "p2GoLeft";
			break;
		case eGUIEvent::p2GoRight:
			this->_message += "p2GoRight";
			break;
		case eGUIEvent::p2GoUp:
			this->_message += "p2GoUp";
			break;
		case eGUIEvent::p2GoDown:
			this->_message += "p2GoDown";
			break;
		case eGUIEvent::changeGUI:
			this->_message += "changeGUI";
			break;
		case eGUIEvent::quitGame:
			this->_message += "quitGame";
			break;
		case eGUIEvent::nothingTODO:
			this->_message += "nothingTODO";
			break;
		default:
			this->_message += "unknownEvent";
			break;
	}
	this->_message += "\".";
}

UnknownEventException::UnknownEventException(UnknownEventException const &src)
{
	*this = src;
}

/*
** Destructor
*/
UnknownEventException::~UnknownEventException(void) {}

/*
** Operator "=" Overload
*/
UnknownEventException		&UnknownEventException::operator=(UnknownEventException const &src)
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
const char					*UnknownEventException::what(void) const throw()
{
	return this->_message.c_str();
}
