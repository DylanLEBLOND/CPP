// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GUIAllegro.class.hpp                               :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/08/10 16:19:09 by dle-blon          #+#    #+#             //
//   Updated: 2020/08/16 15:23:32 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef GUIALLEGRO_CLASS_HPP
# define GUIALLEGRO_CLASS_HPP

/*
 * Personals Includes
 */
# include <allegro5/allegro.h>
# include <allegro5/allegro_primitives.h>
# include <allegro5/allegro_image.h>
# include <allegro5/allegro_font.h>
# include <allegro5/allegro_ttf.h>
# include <allegro5/allegro_audio.h>
# include <allegro5/allegro_acodec.h>
# include <common.hpp>

/*
 * System Includes
 */


class GUIAllegro : public IGUI
{
private:

	eGUI const						_GUIName = eGUI::Allegro;

	/* common */
	Board*							_board;
	Snake*							_snakeP1;
	Snake*							_snakeP2;
	eGUI							_wantedGUI;

	/* Allegro */
		/* Renderer */
	ALLEGRO_DISPLAY*				_window;
	ALLEGRO_EVENT_QUEUE*			_eventQueue;
	ALLEGRO_BITMAP*					_boardBitmap;
	ALLEGRO_BITMAP*					_mainMenuImage;
	ALLEGRO_BITMAP*					_mapSelectionImage;
	ALLEGRO_BITMAP*					_endMenuImage;
		/* Text */
	unsigned int					_textHeight;
	ALLEGRO_FONT*					_mainTextPolice;
	ALLEGRO_FONT*					_scoreTextPolice;
		/* Music */
	ALLEGRO_SAMPLE*					_mainMenuSample;
	ALLEGRO_SAMPLE_INSTANCE*		_mainMenuMusic;
	ALLEGRO_SAMPLE*					_mapSelectionSample;
	ALLEGRO_SAMPLE_INSTANCE*		_mapSelectionMusic;
	ALLEGRO_SAMPLE*					_boardSample;
	ALLEGRO_SAMPLE_INSTANCE*		_boardMusic;
	ALLEGRO_SAMPLE*					_endMenuSample;
	float							_musicVolume;
	bool							_muted;

	/* GUI */
	bool							_started;
	bounds							_menuLeftButton;
	bounds							_menuRightButton;
	bounds							_menuMiddleButton;
	bounds							_menuBottomButton;
		/* Maps Bounds */
	bounds							_mapLTButton;	/*  Left  -  Top   */
	bounds							_mapLMButton;	/*  Left  - Middle */
	bounds							_mapLBButton;	/*  Left  - Bottom */
	bounds							_mapCTButton;	/* Center -  Top   */
	bounds							_mapCMButton;	/* Center - Middle */
	bounds							_mapCBButton;	/* Center - Bottom */
	bounds							_mapRTButton;	/*  Right -  Top   */
	bounds							_mapRMButton;	/*  Right - Middle */
	bounds							_mapRBButton;	/*  Right - Bottom */

	GUIAllegro (void);
	GUIAllegro (GUIAllegro const &src);

	GUIAllegro					&operator=(GUIAllegro const &src);

	void						ajustBounds (void);

	void						drawMainMenu (void);

	void						drawMapSelection (void);

	void						drawBoard (void);
	void						drawSnakes (void);
	void						drawScore (void);

	void						drawEndMenu (void);

public:

	GUIAllegro (Board *board);
	~GUIAllegro (void);

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

	GUIAllegro					*createGUI (Board *board);
	void						setPlayers (GUIAllegro *GUI, Snake *snakeP1, Snake *snakeP2);
	void						destroyGUI (GUIAllegro* GUI);
}

#endif /* GUIALLEGRO_CLASS_HPP */
