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
 * Personals Includes
 */
# include <common.hpp>

/*
 * Enumerations
 */
enum class eGUISwitch { openGL, SDL, MinilibX, Unknown };

class IGUI
{

public:

	virtual ~IGUI (void) {};

	virtual bool			start (int size) = 0;
	virtual eGUISwitch		getGUISwitch (void) const = 0;

};

#endif /* IGUI_CLASS_HPP */
