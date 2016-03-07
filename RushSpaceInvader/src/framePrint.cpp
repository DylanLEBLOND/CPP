// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   framePrint.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/21 22:21:52 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/21 22:21:53 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "retro.hpp"
#define PLAYER ">"
#define OBSTACLE "O"
#define ENEMY "<"
#define PLAYER_MISSILE "-"
#define ENEMY_MISSILE "~"

void	 framePrint(Obstacle **o, Enemy	**e, Player p)
{
	int	i = 0;
	int		 j;
	Missile ** m;

	clear();
	//Display Player
	attron(COLOR_PAIR(1));
	mvprintw(p.getY(), p.getX(), PLAYER);

	while (i < NB_ENEMY)
	{
		if (e[i]->getAlive())
		{
			//DISPLAY ENEMY UNIT
			attron(COLOR_PAIR(2));
			mvprintw(e[i]->getY(), e[i]->getX(), ENEMY);
			j = 0;
			m = e[i]->getMiss();
			while (j < NB_MISSILE)
			{
				//DISPLAY ENEMY UNIT MISSILE
				attron(COLOR_PAIR(3));
				if (m[j]->getAlive())
					mvprintw(m[j]->getY(), m[j]->getX(), ENEMY_MISSILE);
				j++;
			}
		}
		i++;
	}

	i = 0;
	while (i < NB_OBSTACLE)
	{
//DISPLAY OBSTACLE
		attron(COLOR_PAIR(4));
		if (o[i]->getAlive())
			mvprintw(o[i]->getY(), o[i]->getX(), OBSTACLE);
		i++;
	}

	m = p.getMiss();
	i = 0;
	while (i < NB_MISSILE)
	{
//DISPLAY PLAYER MISSILE
		attron(COLOR_PAIR(5));
		if (m[i]->getAlive())
			mvprintw(m[i]->getY(), m[i]->getX(), PLAYER_MISSILE);
		i++;
	}

}
