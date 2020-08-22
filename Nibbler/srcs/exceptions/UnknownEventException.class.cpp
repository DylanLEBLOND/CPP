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
		case eGUIEvent::goLeft:
			this->_message += "goLeft";
			break;
		case eGUIEvent::goRight:
			this->_message += "goRight";
			break;
		case eGUIEvent::goUp:
			this->_message += "goUp";
			break;
		case eGUIEvent::goDown:
			this->_message += "goDown";
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
