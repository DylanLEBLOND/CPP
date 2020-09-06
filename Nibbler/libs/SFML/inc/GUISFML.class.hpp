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
# include <common.hpp>

/*
 * System Includes
 */


class GUISFML : public IGUI
{
private:

	eGUI const			_GUIName = eGUI::SFML;

	/* common */
	Board*				_board;
	Snake*				_snakeP1;
	Snake*				_snakeP2;
	eGUI				_wantedGUI;

	/* SFML */
	sf::RenderWindow*	_window;
//	SFML_Renderer*		_boardRenderer;
//	SFML_Surface*		_mainMenuImage;
//	SFML_Texture*		_mainMenuTexture;
//	SFML_Surface*		_endMenuImage;
//	SFML_Texture*		_endMenuTexture;

	/* GUI */
	bool				_started;
	bounds				_menuLeftButton;
	bounds				_menuRightButton;
	bounds				_menuQuitButton;

	GUISFML (void);
	GUISFML (GUISFML const &src);

	GUISFML					&operator=(GUISFML const &src);

	void					ajustBounds (void);

	void					drawMainMenu (void);

	void					drawBoard (void);
	void					drawSnakes (void);

	void					drawEndMenu (void);

public:

	GUISFML (Board *board);
	~GUISFML (void);

	eGUI					getGUIName (void) const;

	void					start (void);
	bool					alreadyStarted (void) const;
	eGUI					wantedGUI (void) const;
	void					stop (void);
	/* Main Menu */
	void					loadMainMenu (void);
	eGUIMainMenuEvent		getMainMenuEvent (void);
	/* Game */
	void					setPlayers (Snake *snakeP1, Snake *snakeP2);
	void					updateGameGUI (void);
	eGUIGameEvent			getGameEvent (void);
	/* End Menu */
	void					loadEndMenu (void);
	eGUIEndMenuEvent		getEndMenuEvent (void);
};

extern "C" {

	GUISFML					*createGUI (Board *board);
	void					setPlayers (GUISFML *GUI, Snake *snakeP1, Snake *snakeP2);
	void					destroyGUI (GUISFML* GUI);
}

#endif /* GUISFML_CLASS_HPP */
