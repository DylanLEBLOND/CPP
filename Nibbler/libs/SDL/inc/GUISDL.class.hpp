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
#include <SDL2/SDL.h>
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

	/* GUI */
	bool				_started;

	GUISDL (void);
	GUISDL (GUISDL const &src);

	GUISDL				&operator=(GUISDL const &src);

	void				drawBoard (void);
	void				drawSnakes (void);

	void				drawMenu (void);

public:

	GUISDL (Board *board, Snake *snake);
	GUISDL (Board *board, Snake *snakeP1, Snake *snakeP2);
	~GUISDL (void);

	eGUI				getGUIName (void) const;

	void				start (void);
	bool				alreadyStarted (void) const;
	void				stop (void);
	eGUIEvent			getEvent (void);
	void				updateGUI (void);
	eGUI				wantedGUI (void) const;

	void				loadMenu (void);
	eGUIMenuEvent		getMenuEvent (void);
};

extern "C" {

	GUISDL				*createGUI (Board *board, Snake *snakeP1, Snake *snakeP2);
	void				destroyGUI (GUISDL* GUI);
}

#endif /* GUISDL_CLASS_HPP */
