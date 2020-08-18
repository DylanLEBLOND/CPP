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

	/* common */
	Board*			_board;
	Snake*			_snake;
	eGUISwitch		_GUISwitch;

	/* openGL */
	int				*_ac;
	char**			_av;

	GUIOpenGL (void);
	GUIOpenGL (GUIOpenGL const &src);

	GUIOpenGL		&operator=(GUIOpenGL const &src);

	void			snakeAnimation (void);

public:

	GUIOpenGL (Board *board, Snake *snake, int *ac, char **av);
	~GUIOpenGL (void);

	static void		drawTriangle (void);
	static void		resizeWindows (int width, int height);
	void			start (int size);
	bool			run (void);
	void			stop (void);
	eGUISwitch		getGUISwitch (void) const;
};

extern "C" {

	GUIOpenGL		*createGUI (Board *board, Snake *snake, int *ac, char **av);
	void			destroyGUI (GUIOpenGL* GUI);
}

#endif /* GUIOPENGL_CLASS_HPP */
