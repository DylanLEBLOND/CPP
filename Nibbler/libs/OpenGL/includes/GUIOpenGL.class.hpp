// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GUIOpenGL.class.hpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/08/10 16:19:09 by dle-blon          #+#    #+#             //
//   Updated: 2020/08/16 15:23:32 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef GUIOPENGL_CLASS_HPP
# define GUIOPENGL_CLASS_HPP

/*
 * Personals Includes
 */
# include <GL/glut.h>
# include <GL/gl.h>
# include <common.hpp>

/*
 * System Includes
 */


class GUIOpenGL : public IGUI
{
private:

	eGUI const			_GUIName = eGUI::openGL;

	/* common */
	Board*				_board;
	Snake*				_snakeP1;
	Snake*				_snakeP2;
	eGUI				_wantedGUI;

	/* openGL */
	int*				_ac;
	char**				_av;

	/* GUI */
	bool				_started;
	bounds				_mainMenuSinglePlayer;
	bounds				_mainMenuMultiplayer;
	bounds				_mainMenuQuitGame;

	GUIOpenGL (void);
	GUIOpenGL (GUIOpenGL const &src);

	GUIOpenGL				&operator=(GUIOpenGL const &src);

	void					ajustBounds (void);

	void					drawMainMenu (void);

	void					drawBoard (void);
	void					drawSnakes (void);

	void					drawEndMenu (void);

	void					resizeWindows (int width, int height);

public:

	GUIOpenGL (Board *board);
	~GUIOpenGL (void);

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
	void					loadBoard (unsigned int soundTrack);
	void					updateGameGUI (void);
	eGUIGameEvent			getGameEvent (void);
	/* End Menu */
	void					loadEndMenu (void);
	eGUIEndMenuEvent		getEndMenuEvent (void);
};

extern "C" {

	GUIOpenGL			*createGUI (Board *board);
	void				destroyGUI (GUIOpenGL* GUI);
}

#endif /* GUIOPENGL_CLASS_HPP */
