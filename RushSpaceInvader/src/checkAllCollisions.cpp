// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   checkAllCollisions.cpp                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/21 22:21:33 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/21 22:21:38 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "retro.hpp"

bool checkAllCollisions(Obstacle **o, Enemy	**e, Player *p)
{
	Missile	 **p_miss = p->getMiss();

	for (int i = 0; i < NB_ENEMY; i++) //enemy collisions
	{
		if (e[i]->getAlive())
		{
			if ((e[i]->getX() == p->getX()) && (e[i]->getY() == p->getY())) //each enemy with player
			{
				p->setLives(p->getLives() - 10);
				if (p->getLives() <= 0)
				{
					p->setAlive(false);
					return (false);
				}
				e[i]->setAlive(false);
			}
			for (int j = 0; j < NB_OBSTACLE; j++) //each obstacle
			{
				if (o[j]->getAlive() && (e[i]->getX() == o[j]->getX()) && (e[i]->getY() == o[j]->getY())) //each enemy with each obstacle
				{
					e[i]->setAlive(false);
					o[i]->setAlive(false);
					p->setScore(p->getScore() + 1);
				}
			}
			for (int k = 0; k < NB_MISSILE; k++) //each player's missiles
			{
				if (p_miss[k]->getAlive() && (e[i]->getX() == p_miss[k]->getX()) && (e[i]->getY() == p_miss[k]->getY())) //each enemy with each players' missiles
				{
					e[i]->setAlive(false);
					p_miss[k]->setAlive(false);
					p->setScore(p->getScore() + 3);
				}
			}
			Missile **e_miss = e[i]->getMiss();
			for (int l = 0; l < NB_MISSILE; l++) // each ennemy's missile
			{
				if (e_miss[l]->getAlive())
				{
					if ((e_miss[l]->getX() == p->getX()) && (e_miss[l]->getY() == p->getY())) // enemys missile with player
					{
						p->setLives(p->getLives() - 1);
						if (p->getLives() <= 0)
						{
							p->setAlive(false);
							return (false);
						}
						e_miss[l]->setAlive(false);
						return (false);
					}
					for (int m = 0; m < NB_MISSILE; m++) // enemys missiles with player missiles
					{
						if (p_miss[m]->getAlive() && (p_miss[m]->getX() == e_miss[l]->getX()) && (p_miss[m]->getY() == e_miss[l]->getY()))
						{
							p_miss[m]->setAlive(false);
							e_miss[l]->setAlive(false);
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < NB_OBSTACLE; i++) //Obstacle collisions
	{
		if (o[i]->getAlive())
		{
			if ((o[i]->getX() == p->getX()) && (o[i]->getY() == p->getY())) //Each obstacle against player
			{
				p->setLives(p->getLives() - 1);
				if (p->getLives() <= 0)
				{
					p->setAlive(false);
					return (false);
				}

				o[i]->setAlive(false);
				return (false);
			}
			for (int j = 0; j < NB_ENEMY; j++) //Each enemy
			{
				if (e[j]->getAlive())
				{
					Missile	**e_miss = e[j]->getMiss();
					for (int k = 0; k < NB_MISSILE; k++) //Each enemy's missile
					{
						if (e_miss[k]->getAlive() && (o[i]->getX() == e_miss[k]->getX()) && (o[i]->getY() == e_miss[k]->getY())) // Each missils with each obstacle
						{
							o[i]->setAlive(false);
							e_miss[k]->setAlive(false);
						}
					}
				}
			}
		}
		for (int l = 0; l < NB_MISSILE; l++)
		{
			if (p_miss[l]->getAlive() && (o[i]->getX() == p_miss[l]->getX()) && (o[i]->getY() == p_miss[l]->getY()))
			{
				o[i]->setAlive(false);
				p_miss[l]->setAlive(false);
			}
		}
	}

	return (true);
}
