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

	eGUI const		_GUIName = eGUI::SDL;

	/* common */
	Board*			_board;
	Snake*			_snake;
	eGUI			_wantedGUI;

	/* SDL */
	SDL_Window*		_window;
	SDL_Renderer*	_boardRenderer;

	GUISDL (void);
	GUISDL (GUISDL const &src);

	GUISDL			&operator=(GUISDL const &src);

	void			drawSnake (void);

public:

	GUISDL (Board *board, Snake *snake);
	~GUISDL (void);

	eGUI			getGUIName (void) const;

	void			start (void);
	void			stop (void);
	eGUIEvent		getEvent (void);
	void			updateGUI (void);
	eGUI			wantedGUI (void) const;
};

extern "C" {

	GUISDL			*createGUI (Board *board, Snake *snake, int *ac, char **av);
	void			destroyGUI (GUISDL* GUI);
}

#endif /* GUISDL_CLASS_HPP */
