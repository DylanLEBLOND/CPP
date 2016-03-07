// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Missile.class.cpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/21 22:20:58 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/21 22:41:31 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Missile.class.hpp"

/*
** constructor
*/
Missile::Missile(char img) : AStuff(img)
{
	this->_alive = false;
	if (DEBUG) this->debug("Missile constructed (default).");
}

Missile::Missile(Missile const &copy)
{
	if (DEBUG) this->debug("Missile constructed (copy).");

	*this = copy;
}

/*
** destructor
*/
Missile::~Missile(void)
{
	if (DEBUG) this->debug("Missile destructed.");
}

/*
** operator overload
*/
Missile					&Missile::operator=(Missile const &copy)
{
	AStuff::operator=(copy);

	return *this;
}

/*
** public
*/
void					Missile::move(char direction)
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
