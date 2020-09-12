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
 * Enumerations
 */
enum class eGUI { openGL, SDL, SFML, unknownGUI };

enum class eGUIMainMenuEvent { startSinglePlayerGame, startMultiPlayerGame, changeGUI, quitGame, nothingTODO, unknownMainMenuEvent };

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

enum class eGUIGameEvent { p1GoLeft, p1GoRight, p1GoUp, p1GoDown, p2GoLeft, p2GoRight, p2GoUp, p2GoDown, changeGUI, quitGame, nothingTODO, unknownGameEvent };

enum class eGUIEndMenuEvent { restartLevel, nextLevel, backToLobby, changeGUI, quitGame, nothingTODO, unknownEndMenuEvent };

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

	virtual void						loadBoard (unsigned int soundTrack) = 0;
	virtual void						updateGameGUI (void) = 0;
	virtual eGUIGameEvent				getGameEvent (void) = 0;

	virtual void						loadEndMenu (void) = 0;
	virtual eGUIEndMenuEvent			getEndMenuEvent (void) = 0;
};

#endif /* IGUI_CLASS_HPP */
