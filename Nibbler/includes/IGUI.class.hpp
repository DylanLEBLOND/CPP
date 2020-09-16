// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GUI.class.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/08/10 16:19:09 by dle-blon          #+#    #+#             //
//   Updated: 2020/08/16 15:23:32 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef IGUI_CLASS_HPP
# define IGUI_CLASS_HPP

/*
 * Personnals Includes
 */
# include <Board.class.hpp>
# include <Snake.class.hpp>

/*
 * Enumerations
 */
enum class eGUI { SDL, SFML, Allegro, unknownGUI };

enum class eGUIMainMenuEvent { startSinglePlayerGame,
							   startMultiPlayerGame,
							   changeGUI,
							   quitGame,
							   nothingTODO,
							   unknownMainMenuEvent };

enum class eGUIMapSelectionEvent
{
	mapLT,	/*  Left  -  Top   */
	mapLM,	/*  Left  - Middle */
	mapLB,	/*  Left  - Bottom */
	mapCT,	/* Center -  Top   */
	mapCM,	/* Center - Middle */
	mapCB,	/* Center - Bottom */
	mapRT,	/*  Right -  Top   */
	mapRM,	/*  Right - Middle */
	mapRB,	/*  Right - Bottom */
	changeGUI,
	quitGame,
	nothingTODO,
	unknownMapSelectionEvent
};

enum class eGUIGameEvent { p1GoLeft,
						   p1GoRight,
						   p1GoUp,
						   p1GoDown,
						   p2GoLeft,
						   p2GoRight,
						   p2GoUp,
						   p2GoDown,
						   changeGUI,
						   forfeitGame,
						   quitGame,
						   nothingTODO,
						   unknownGameEvent };

enum class eGUIEndMenuEvent { restartLevel,
							  nextLevel,
							  backToLobby,
							  changeGUI,
							  quitGame,
							  nothingTODO,
							  unknownEndMenuEvent };

/*
 * Defines
 */
#define eGUIString(GUI)							((GUI) == eGUI::SDL ? "SDL" : \
												 (GUI) == eGUI::SFML ? "SFML" : \
												 (GUI) == eGUI::Allegro ? "Allegro" : "unknownGUI")

#define eGUIMainMenuEventString(event)			((event) == eGUIMainMenuEvent::startSinglePlayerGame ? "startSinglePlayerGame" : \
												 (event) == eGUIMainMenuEvent::startMultiPlayerGame ? "startMultiPlayerGame" : \
												 (event) == eGUIMainMenuEvent::changeGUI ? "changeGUI" : \
												 (event) == eGUIMainMenuEvent::quitGame ? "quitGame" : \
												 (event) == eGUIMainMenuEvent::nothingTODO ? "nothingTODO" : "unknownMainMenuEvent")

#define eGUIMapSelectionEventString(event)		((event) == eGUIMapSelectionEvent::mapLT ? "mapLT" : \
												 (event) == eGUIMapSelectionEvent::mapLM ? "mapLM" : \
												 (event) == eGUIMapSelectionEvent::mapLB ? "mapLB" : \
												 (event) == eGUIMapSelectionEvent::mapCT ? "mapCT" : \
												 (event) == eGUIMapSelectionEvent::mapCM ? "mapCM" : \
												 (event) == eGUIMapSelectionEvent::mapCB ? "mapCB" : \
												 (event) == eGUIMapSelectionEvent::mapRT ? "mapRT" : \
												 (event) == eGUIMapSelectionEvent::mapRM ? "mapRM" : \
												 (event) == eGUIMapSelectionEvent::mapRB ? "mapRB" : \
												 (event) == eGUIMapSelectionEvent::changeGUI ? "changeGUI" : \
												 (event) == eGUIMapSelectionEvent::quitGame ? "quitGame" : \
												 (event) == eGUIMapSelectionEvent::nothingTODO ? "nothingTODO" : "unknownMapSelectionEvent")

#define eGUIGameEventString(event)				((event) == eGUIGameEvent::p1GoLeft ? "p1GoLeft" : \
												 (event) == eGUIGameEvent::p1GoRight ? "p1GoRight" : \
												 (event) == eGUIGameEvent::p1GoUp ? "p1GoUp" : \
												 (event) == eGUIGameEvent::p1GoDown ? "p1GoDown" : \
												 (event) == eGUIGameEvent::p2GoLeft ? "p2GoLeft" : \
												 (event) == eGUIGameEvent::p2GoRight ? "p2GoRight" : \
												 (event) == eGUIGameEvent::p2GoUp ? "p2GoUp" : \
												 (event) == eGUIGameEvent::p2GoDown ? "p2GoDown" : \
												 (event) == eGUIGameEvent::changeGUI ? "changeGUI" : \
												 (event) == eGUIGameEvent::forfeitGame ? "forfeitGame" : \
												 (event) == eGUIGameEvent::quitGame ? "quitGame" : \
												 (event) == eGUIGameEvent::nothingTODO ? "nothingTODO" : "unknownGameEvent")

#define eGUIEndMenuEventString(event)			((event) == eGUIEndMenuEvent::restartLevel ? "restartLevel" : \
												 (event) == eGUIEndMenuEvent::nextLevel ? "nextLevel" : \
												 (event) == eGUIEndMenuEvent::backToLobby ? "backToLobby" : \
												 (event) == eGUIEndMenuEvent::changeGUI ? "changeGUI" : \
												 (event) == eGUIEndMenuEvent::quitGame ? "quitGame" : \
												 (event) == eGUIEndMenuEvent::nothingTODO ? "nothingTODO" : "unknownEndMenuEvent")

class IGUI
{
public:

	virtual ~IGUI (void) {};

	virtual eGUI						getGUIName (void) const = 0;

	virtual void						start (void) = 0;
	virtual bool						alreadyStarted (void) const = 0;
	virtual eGUI						wantedGUI (void) const = 0;
	virtual void						stop (void) = 0;

	virtual void						loadMainMenu (void) = 0;
	virtual eGUIMainMenuEvent			getMainMenuEvent (void) = 0;

	virtual void						loadMapSelection (void) = 0;
	virtual eGUIMapSelectionEvent		getMapSelectionEvent (void) = 0;

	virtual void						setPlayers (Snake *snakeP1, Snake *snakeP2) = 0;
	virtual void						loadBoard (unsigned int soundTrack) = 0;
	virtual void						updateGameGUI (void) = 0;
	virtual eGUIGameEvent				getGameEvent (void) = 0;

	virtual void						loadEndMenu (void) = 0;
	virtual eGUIEndMenuEvent			getEndMenuEvent (void) = 0;
};

#endif /* IGUI_CLASS_HPP */
