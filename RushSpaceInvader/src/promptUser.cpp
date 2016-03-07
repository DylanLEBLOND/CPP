// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   promptUser.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/21 22:22:43 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/21 22:22:44 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "retro.hpp"

//cf. AStuff.class.hpp for defines

char promptUser(void)
{
	char		car = 0;

	if ((car = static_cast<char>(getch())) != ERR)
		flushinp();
	if (car == EXIT)
	{
		endwin();
		exit(0);//end game;
	}

	return (car);
}
