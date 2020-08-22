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

	/* common */
	Board*			_board;
	Snake*			_snake;
	eGUISwitch		_GUISwitch;

	/* SDL */
	SDL_Window*		_window;
	SDL_Renderer*	_boardRenderer;

	GUISDL (void);
	GUISDL (GUISDL const &src);

	GUISDL			&operator=(GUISDL const &src);

	void			drawSnake (void);
	void			drawTriangle (void);

public:

	GUISDL (Board *board, Snake *snake);
	~GUISDL (void);

	void			start (void);
	bool			run (void);
	void			stop (void);
	eGUISwitch		getGUISwitch (void) const;
};

extern "C" {

	GUISDL			*createGUI (Board *board, Snake *snake, int *ac, char **av);
	void			destroyGUI (GUISDL* GUI);
}

#endif /* GUISDL_CLASS_HPP */
