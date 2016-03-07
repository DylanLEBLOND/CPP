// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AStuff.class.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/21 22:20:30 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/21 22:20:31 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "AStuff.class.hpp"

/*
** constructor
*/
AStuff::AStuff(char img) : _img(img),
						   _x(0),
						   _y(0),
						   _alive(true)
{
	if (DEBUG) this->debug("Stuff constructed (default).");
}

AStuff::AStuff(AStuff const &copy)
{
	if (DEBUG) this->debug("Stuff constructed (copy).");
	*this = copy;
}

/*
** destructor
*/
AStuff::~AStuff(void)
{
	if (DEBUG) this->debug("Stuff destructed.");
}

/*
** operator overload
*/
AStuff					&AStuff::operator=(AStuff const &copy)
{
	this->_x = copy._x;
	this->_y = copy._y;
	this->_img = copy._img;
	this->_alive = copy._alive;

	return *this;
}

/*
** public
*/
void					AStuff::debug(std::string s) const
{
    mvprintw(0, 0, "%s x:%d y:%d img:%c alive:%c",
             s.c_str(), this->_x, this->_y, this->_img, this->_alive);

	std::cout << s
			  << " x: " << this->_x
			  << " y: " << this->_y
			  << " img: " << this->_img
			  << " alive: " << this->_alive << std::endl;

    refresh();
}


/*
** getter/setter
*/
int						AStuff::getX(void)		const { return this->_x; }
int						AStuff::getY(void)		const { return this->_y; }
char					AStuff::getImg(void)	const { return this->_img; }
bool					AStuff::getAlive(void)	const { return this->_alive; }
void					AStuff::setX(int x)			  { this->_x = x; }
void					AStuff::setY(int y)			  { this->_y = y; }
void					AStuff::setImg(char img)	  { this->_img = img; }
void					AStuff::setAlive(bool alive)  { this->_alive = alive; }
