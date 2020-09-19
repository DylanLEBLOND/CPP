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
# define GUISDL_CLASS_HPP

/*
 * Personals Includes
 */
# include <Board.class.hpp>
# include <Snake.class.hpp>
# include <IGUI.class.hpp>

/*
 * System Includes
 */
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_mixer.h>


class GUISDL : public IGUI
{
private:

	eGUI const				_GUI = eGUI::SDL;

	/* common */
	Board*				_board;
	Snake*				_snakeP1;
	Snake*				_snakeP2;
	eGUI				_wantedGUI;

	/* SDL */
		/* Renderer */
	SDL_Window*			_window;
	SDL_Renderer*		_boardRenderer;
	SDL_Surface*		_mainMenuImage;
	SDL_Texture*		_mainMenuTexture;
	SDL_Surface*		_mapSelectionImage;
	SDL_Texture*		_mapSelectionTexture;
	SDL_Surface*		_endMenuImage;
	SDL_Texture*		_endMenuTexture;
		/* Text */
	unsigned int		_textHeight;
	TTF_Font*			_mainTextPolice;
	SDL_Surface*		_mainTextImage;
	SDL_Texture*		_mainTextTexture;
	TTF_Font*			_scoreTextPolice;
	SDL_Surface*		_scoreP1TextImage;
	SDL_Texture*		_scoreP1TextTexture;
	SDL_Surface*		_scoreP2TextImage;
	SDL_Texture*		_scoreP2TextTexture;
		/* Music */
	Mix_Music*			_mainMenuMusic;
	Mix_Music*			_mapSelectionMusic;
	Mix_Music*			_boardMusic;
	Mix_Music*			_endMenuMusic;
	unsigned int		_musicVolume;

	/* GUI */
	bool				_started;
	bounds				_menuLeftButton;
	bounds				_menuRightButton;
	bounds				_menuMiddleButton;
	bounds				_menuBottomButton;
		/* Maps Bounds */
	bounds				_mapLTButton;	/*  Left  -  Top   */
	bounds				_mapLMButton;	/*  Left  - Middle */
	bounds				_mapLBButton;	/*  Left  - Bottom */
	bounds				_mapCTButton;	/* Center -  Top   */
	bounds				_mapCMButton;	/* Center - Middle */
	bounds				_mapCBButton;	/* Center - Bottom */
	bounds				_mapRTButton;	/*  Right -  Top   */
	bounds				_mapRMButton;	/*  Right - Middle */
	bounds				_mapRBButton;	/*  Right - Bottom */

	GUISDL (void);
	GUISDL (GUISDL const &src);

	GUISDL						&operator=(GUISDL const &src);

	void						ajustBounds (void);

	void						drawMainMenu (void);

	void						drawMapSelection (void);

	void						drawBoard (void);
	void						drawSnakes (void);
	void						drawScore (void);

	void						drawEndMenu (void);

public:

	GUISDL (Board *board);
	~GUISDL (void);

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

	IGUI						*createGUI (Board *board);
	void						destroyGUI (IGUI* GUI);
}

#endif /* GUISDL_CLASS_HPP */
