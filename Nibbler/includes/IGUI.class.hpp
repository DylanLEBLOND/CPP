// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GUI.class.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/08/10 16:19:09 by dle-blon          #+#    #+#             //
//   Updated: 2020/08/16 15:23:32 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef IGUI_CLASS_HPP
# define IGUI_CLASS_HPP

/*
 * Enumerations
 */
enum class eGUI { openGL, SDL, MinilibX, unknownGUI };

enum class eGUIEvent { goLeft, goRight, goUp, goDown, changeGUI, quitGame, nothingTODO, unknownEvent };

class IGUI
{

public:

	virtual ~IGUI (void) {};

	virtual eGUI			getGUIName (void) const = 0;

	virtual void			start (void) = 0;
	virtual void			stop (void) = 0;
	virtual eGUIEvent		getEvent (void) = 0;
	virtual void			updateGUI (void) = 0;
	virtual eGUI			wantedGUI (void) const = 0;
};

#endif /* IGUI_CLASS_HPP */
