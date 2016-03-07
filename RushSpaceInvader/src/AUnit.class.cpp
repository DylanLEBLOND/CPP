// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AUnit.class.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/21 22:20:40 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/21 22:45:03 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "AUnit.class.hpp"

/*
** constructor
*/
AUnit::AUnit(char img) : AStuff(img),
						 _miss(0)
{
	if (DEBUG) this->debug("Unit constructed (default).");

	this->_miss = new Missile*[NB_MISSILE];
	for (int i = 0; i < NB_MISSILE; i++)
		this->_miss[i] = new Missile;
}

AUnit::AUnit(AUnit const &copy)
{
	if (DEBUG) this->debug("Unit constructed (copy).");

	this->_miss = new Missile*[NB_MISSILE];
	*this = copy;
}

/*
** destructor
*/
AUnit::~AUnit(void)
{
	if (DEBUG) this->debug("Unit destructed.");
}

/*
** operator overload
*/
AUnit					&AUnit::operator=(AUnit const &copy)
{
	AStuff::operator=(copy);
	this->_miss = copy._miss;
	for (int i = 0; i < NB_MISSILE; i++)
		this->_miss[i] = copy._miss[i];

	return *this;
}

/*
** public
*/
void					AUnit::shoot(bool player)
{
	for (int i = 0; i < NB_MISSILE; i++)
		if (!this->_miss[i]->getAlive())
		{
			this->_miss[i]->setAlive(true);
			this->_miss[i]->setX(this->_x + (player ? 1 : -1));
			this->_miss[i]->setY(this->_y);
			break;
		}
}

void					AUnit::move(char direction)
{
	switch (direction)
	{
	case RIGHT:
		if (this->_x + 1 < HEIGHT - 1)
			this->_x++;
		else
			this->_alive = false;
		break;
	case LEFT:
		if (this->_x - 1 > 0)
			this->_x--;
		else
			this->_alive = false;
		break;
	case DOWN:
		if (this->_y + 1 < WIDTH - 1)
			this->_y++;
		else
			this->_alive = false;
		break;
	case UP:
		if (this->_y - 1 > 0)
			this->_y--;
		else
			this->_alive = false;
		break;
	}
}

/*
** getter/setter
*/
Missile					**AUnit::getMiss(void) const	{ return this->_miss; }
