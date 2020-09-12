#include <exceptions/UnknownEventException.class.hpp>

/*
** Constructors
*/
UnknownEventException::UnknownEventException (eGUI affectedGUI, eGUIMainMenuEvent receivedEvent)
{
	this->_message = "Unknown Event Error: GUI = \"";
	switch (affectedGUI)
	{
		case eGUI::SDL:
			this->_message += "SDL";
			break;
		case eGUI::SFML:
			this->_message += "SFML";
			break;
		default:
			this->_message += "unknownGUI";
			break;
	}
	this->_message += "\" | Received Main Menu Event = \"";
	switch (receivedEvent)
	{
		case eGUIMainMenuEvent::startSinglePlayerGame:
			this->_message += "startSinglePlayerGame";
			break;
		case eGUIMainMenuEvent::startMultiPlayerGame:
			this->_message += "startMultiPlayerGame";
			break;
		case eGUIMainMenuEvent::changeGUI:
			this->_message += "changeGUI";
			break;
		case eGUIMainMenuEvent::quitGame:
			this->_message += "quitGame";
			break;
		default:
			this->_message += "unknownMainMenuEvent";
			break;
	}
	this->_message += "\".";
}

UnknownEventException::UnknownEventException (eGUI affectedGUI, eGUIMapSelectionEvent receivedEvent)
{
	this->_message = "Unknown Event Error: GUI = \"";
	switch (affectedGUI)
	{
		case eGUI::SDL:
			this->_message += "SDL";
			break;
		case eGUI::SFML:
			this->_message += "SFML";
			break;
		default:
			this->_message += "unknownGUI";
			break;
	}
	this->_message += "\" | Received Main Menu Event = \"";
	switch (receivedEvent)
	{
		case eGUIMapSelectionEvent::mapLT:
			this->_message += "mapLeftTop";
			break;
		case eGUIMapSelectionEvent::mapLM:
			this->_message += "mapLeftMiddle";
			break;
		case eGUIMapSelectionEvent::mapLB:
			this->_message += "mapLeftBottom";
			break;
		case eGUIMapSelectionEvent::mapCT:
			this->_message += "mapCenterTop";
			break;
		case eGUIMapSelectionEvent::mapCM:
			this->_message += "mapCenterMiddle";
			break;
		case eGUIMapSelectionEvent::mapCB:
			this->_message += "mapCenterBottom";
			break;
		case eGUIMapSelectionEvent::mapRT:
			this->_message += "mapRightTop";
			break;
		case eGUIMapSelectionEvent::mapRM:
			this->_message += "mapRightMiddle";
			break;
		case eGUIMapSelectionEvent::mapRB:
			this->_message += "mapRightBottom";
			break;
		case eGUIMapSelectionEvent::changeGUI:
			this->_message += "changeGUI";
			break;
		case eGUIMapSelectionEvent::quitGame:
			this->_message += "quitGame";
			break;
		default:
			this->_message += "unknownMapSelectionEvent";
			break;
	}
	this->_message += "\".";
}

UnknownEventException::UnknownEventException (eGUI affectedGUI, eGUIGameEvent receivedEvent)
{
	this->_message = "Unknown Event Error: GUI = \"";
	switch (affectedGUI)
	{
		case eGUI::SDL:
			this->_message += "SDL";
			break;
		case eGUI::SFML:
			this->_message += "SFML";
			break;
		default:
			this->_message += "unknownGUI";
			break;
	}
	this->_message += "\" | Received Game Event = \"";
	switch (receivedEvent)
	{
		case eGUIGameEvent::p1GoLeft:
			this->_message += "p1GoLeft";
			break;
		case eGUIGameEvent::p1GoRight:
			this->_message += "p1GoRight";
			break;
		case eGUIGameEvent::p1GoUp:
			this->_message += "p1GoUp";
			break;
		case eGUIGameEvent::p1GoDown:
			this->_message += "p1GoDown";
			break;
		case eGUIGameEvent::p2GoLeft:
			this->_message += "p2GoLeft";
			break;
		case eGUIGameEvent::p2GoRight:
			this->_message += "p2GoRight";
			break;
		case eGUIGameEvent::p2GoUp:
			this->_message += "p2GoUp";
			break;
		case eGUIGameEvent::p2GoDown:
			this->_message += "p2GoDown";
			break;
		case eGUIGameEvent::changeGUI:
			this->_message += "changeGUI";
			break;
		case eGUIGameEvent::quitGame:
			this->_message += "quitGame";
			break;
		case eGUIGameEvent::nothingTODO:
			this->_message += "nothingTODO";
			break;
		default:
			this->_message += "unknownGameEvent";
			break;
	}
	this->_message += "\".";
}

UnknownEventException::UnknownEventException (eGUI affectedGUI, eGUIEndMenuEvent receivedEvent)
{
	this->_message = "Unknown Event Error: GUI = \"";
	switch (affectedGUI)
	{
		case eGUI::SDL:
			this->_message += "SDL";
			break;
		case eGUI::SFML:
			this->_message += "SFML";
			break;
		default:
			this->_message += "unknownGUI";
			break;
	}
	this->_message += "\" | Received End Menu Event = \"";
	switch (receivedEvent)
	{
		case eGUIEndMenuEvent::restartLevel:
			this->_message += "restart";
			break;
		case eGUIEndMenuEvent::nextLevel:
			this->_message += "nextLevel";
			break;
		case eGUIEndMenuEvent::changeGUI:
			this->_message += "changeGUI";
			break;
		case eGUIEndMenuEvent::quitGame:
			this->_message += "quitGame";
			break;
		default:
			this->_message += "unknownEndMenuEvent";
			break;
	}
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
