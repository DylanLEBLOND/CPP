// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GUISDL.class.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/08/10 16:19:09 by dle-blon          #+#    #+#             //
//   Updated: 2020/08/16 15:23:32 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef GUISDL_CLASS_HPP
# define GUIOPENGL_CLASS_HPP

/*
 * Personals Includes
 */
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <common.hpp>

/*
 * System Includes
 */


class GUISDL : public IGUI
{
private:

	eGUI const			_GUIName = eGUI::SDL;

	/* common */
	Board*				_board;
	Snake*				_snakeP1;
	Snake*				_snakeP2;
	eGUI				_wantedGUI;

	/* SDL */
	SDL_Window*			_window;
	SDL_Renderer*		_boardRenderer;
	SDL_Surface*		_mainMenuImage;
	SDL_Texture*		_mainMenuTexture;
	SDL_Surface*		_endMenuImage;
	SDL_Texture*		_endMenuTexture;

	/* GUI */
	bool				_started;
	bounds				_menuLeftButton;
	bounds				_menuRightButton;
	bounds				_menuQuitButton;

	GUISDL (void);
	GUISDL (GUISDL const &src);

	GUISDL					&operator=(GUISDL const &src);

	void					ajustBounds (void);

	void					drawMainMenu (void);

	void					drawBoard (void);
	void					drawSnakes (void);

	void					drawEndMenu (void);

public:

	GUISDL (Board *board);
	~GUISDL (void);

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

	GUISDL				*createGUI (Board *board);
	void				setPlayers (GUISDL *GUI, Snake *snakeP1, Snake *snakeP2);
	void				destroyGUI (GUISDL* GUI);
}

#endif /* GUISDL_CLASS_HPP */
