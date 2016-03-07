// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   moveAll.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/21 18:37:12 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/21 21:26:05 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "retro.hpp"

bool		moveAll(char key, Obstacle **o, Enemy **e, Player *p)
{
	int		i, j;
	Missile	**pmiss = p->getMiss();

	i = 0;
	while (i < NB_MISSILE)
		pmiss[i++]->move(RIGHT);
    if (!checkAllCollisions(o, e, p))
		return false;
    if (key != SHOOT)
        p->move(key);
	i = 0;
	while (i < NB_OBSTACLE)
		o[i++]->move(LEFT);
	i = 0;
    while (i < NB_ENEMY)
	{
		j = 0;
		if (rand() % 3 == 2)
			e[i]->move(DOWN);
		else if (rand() % 3 == 0)
            e[i]->move(UP);
        e[i]->move(LEFT);
		Missile **emiss = e[i]->getMiss();
		while (j < NB_MISSILE)
			emiss[j++]->move(LEFT);
		j = 0;
		if (!checkAllCollisions(o, e, p))
			return false;
		emiss = e[i]->getMiss();
		while (j < NB_MISSILE)
            emiss[j++]->move(LEFT);
		i++;
	}
    if (!checkAllCollisions(o, e, p))
        return false;
	return true;
}
