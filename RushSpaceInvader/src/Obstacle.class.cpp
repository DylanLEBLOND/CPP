// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Obstacle.class.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/21 22:21:11 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/21 22:41:43 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Obstacle.class.hpp"

/*
** constructor
*/
Obstacle::Obstacle(char img) : AStuff(img)
{
	if (DEBUG) this->debug("Obstacle constructed (default).");
	this->setX(WIDTH - 1);
	this->setY(rand() % (HEIGHT - 1));
	this->setAlive(false);
}

Obstacle::Obstacle(Obstacle const &copy)
{
	if (DEBUG) this->debug("Obstacle constructed (copy).");

	*this = copy;
}

/*
** destructor
*/
Obstacle::~Obstacle(void)
{
	if (DEBUG) this->debug("Obstacle destructed.");
}

/*
** operator overload
*/
Obstacle				&Obstacle::operator=(Obstacle const &copy)
{
	AStuff::operator=(copy);

	return *this;
}

/*
** public
*/
void					Obstacle::move(char direction)
{
	switch (direction)
	{
	case RIGHT:
		if (this->_x + 1 < WIDTH - 1)
			this->_x++;
		else
			this->_alive = false;
		break ;
	case LEFT:
		if (this->_x - 1 > 0)
			this->_x--;
		else
			this->_alive = false;
		break ;
	case DOWN:
		if (this->_y + 1 < HEIGHT - 1)
			this->_y++;
		else
			this->_alive = false;
		break ;
	case UP:
		if (this->_y - 1 > 0)
			this->_y--;
		else
			this->_alive = false;
		break ;
	}
}
