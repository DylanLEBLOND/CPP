// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Player.class.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/21 22:21:22 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/21 22:21:23 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Player.class.hpp"

/*
** constructor
*/
Player::Player(char img, std::string name) : AUnit(img),
											 _name(name),
											 _lives(3),
											 _score(0)
{
    this->_x = 1;
    this->_y = HEIGHT/2;
    
	if (DEBUG) this->debug("Player constructed (default).");
}

Player::Player(Player const &copy)
{
	*this = copy;

	if (DEBUG) this->debug("Player constructed (copy).");
}

/*
** destructor
*/
Player::~Player(void)
{
	if (DEBUG) this->debug("Player destructed.");
}

/*
** operator overload
*/
Player					&Player::operator=(Player const &copy)
{
	AUnit::operator=(copy);
	this->_lives = copy._lives;
	this->_score = copy._score;
	this->_name = copy._name;

	return *this;
}

/*
** public
*/
void					Player::move(char direction)
{
	AUnit::move(direction);
}

void					Player::debug(std::string s) const
{
    mvprintw(0, 0, "%s x:%d y:%d img:%c alive:%c",
             s.c_str(), this->_x, this->_y, this->_img, this->_alive);
    
	std::cout << s
			  << " x: " << this->_x
			  << " y: " << this->_y
			  << " img: " << this->_img
			  << " alive: " << this->_alive 
			  << " lives: " << this->_lives
			  << " score: " << this->_score
			  << " name: " << this->_name << std::endl;

    refresh();
}


/*
** getter/setter
*/
int						Player::getLives(void) const { return this->_lives; }
int						Player::getScore(void) const { return this->_score; }
std::string				Player::getName(void)  const { return this->_name;  }

void					Player::setLives(int lives)	{ this->_lives = lives; }
void					Player::setScore(int score)	{ this->_score = score; }
