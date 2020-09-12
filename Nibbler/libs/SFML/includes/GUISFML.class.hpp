// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GUISFML.class.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/08/10 16:19:09 by dle-blon          #+#    #+#             //
//   Updated: 2020/08/16 15:23:32 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef GUISFML_CLASS_HPP
# define GUISFML_CLASS_HPP

/*
 * Personals Includes
 */
# include <SFML/Graphics.hpp>
# include <SFML/Audio.hpp>
# include <common.hpp>

/*
 * System Includes
 */


class GUISFML : public IGUI
{
private:

	eGUI const				_GUIName = eGUI::SFML;

	/* common */
	Board*					_board;
	Snake*					_snakeP1;
	Snake*					_snakeP2;
	eGUI					_wantedGUI;

	/* SFML */
		/* Renderer */
	sf::RenderWindow		_window;
	sf::Texture				_mainMenuTexture;
	sf::Sprite				_mainMenuSprite;
	sf::Texture				_mapSelectionTexture;
	sf::Sprite				_mapSelectionSprite;
	sf::Texture				_endMenuTexture;
	sf::Sprite				_endMenuSprite;
		/* Text */
	unsigned int			_textHeight;
	sf::Font				_mainPolice;
	sf::Text				_mainText;
	sf::Font				_scorePolice;
	sf::Text				_scoreP1Text;
	sf::Text				_scoreP2Text;
		/* Music */
	sf::Music				_mainMenuMusic;
	sf::Music				_mapSelectionMusic;
	sf::Music				_boardMusic;
	sf::Music				_endMenuMusic;
	unsigned int			_musicVolume;
	bool					_muted;

	/* GUI */
	bool					_started;
	bounds					_menuLeftButton;
	bounds					_menuRightButton;
	bounds					_menuMiddleButton;
	bounds					_menuBottomButton;
		/* Maps Bounds */
	bounds					_mapLTButton;	/*  Left  -  Top   */
	bounds					_mapLMButton;	/*  Left  - Middle */
	bounds					_mapLBButton;	/*  Left  - Bottom */
	bounds					_mapCTButton;	/* Center -  Top   */
	bounds					_mapCMButton;	/* Center - Middle */
	bounds					_mapCBButton;	/* Center - Bottom */
	bounds					_mapRTButton;	/*  Right -  Top   */
	bounds					_mapRMButton;	/*  Right - Middle */
	bounds					_mapRBButton;	/*  Right - Bottom */

	GUISFML (void);
	GUISFML (GUISFML const &src);

	GUISFML						&operator=(GUISFML const &src);

	void						ajustBounds (void);

	void						drawMainMenu (void);

	void						drawMapSelection (void);

	void						drawBoard (void);
	void						drawSnakes (void);
	void						drawScore (void);

	void						drawEndMenu (void);

public:

	GUISFML (Board *board);
	~GUISFML (void);

	eGUI						getGUIName (void) const;

	void						start (void);
	bool						alreadyStarted (void) const;
	eGUI						wantedGUI (void) const;
	void						stop (void);
	/* Main Menu */
	void						loadMainMenu (void);
	eGUIMainMenuEvent			getMainMenuEvent (void);
	/* Map Selection */
	void						loadMapSelection (void);
	eGUIMapSelectionEvent		getMapSelectionEvent (void);
	/* Game */
	void						setPlayers (Snake *snakeP1, Snake *snakeP2);
	void						loadBoard (unsigned int soundTrack);
	void						updateGameGUI (void);
	eGUIGameEvent				getGameEvent (void);
	/* End Menu */
	void						loadEndMenu (void);
	eGUIEndMenuEvent			getEndMenuEvent (void);
};

extern "C" {

	GUISFML						*createGUI (Board *board);
	void						setPlayers (GUISFML *GUI, Snake *snakeP1, Snake *snakeP2);
	void						destroyGUI (GUISFML* GUI);
}

#endif /* GUISFML_CLASS_HPP */
