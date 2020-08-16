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

	Board _board;
	Snake _snake;
	int *_ac;
	char **_av;
	eGUISwitch _GUISwitch;

	GUIOpenGL (void);

	void			snakeAnimation (void);

public:

	GUIOpenGL (Board &board, Snake &snake, int *ac, char **av);
	~GUIOpenGL (void);

	static void		drawTriangle (void);
	bool			start (void);
	eGUISwitch		getGUISwitch (void) const;
};

extern "C" {

	GUIOpenGL		*createGUI (Board &board, Snake &snake, int *ac, char **av);
	void			destroyGUI (GUIOpenGL* GUI);
}

#endif /* GUIOPENGL_CLASS_HPP */
