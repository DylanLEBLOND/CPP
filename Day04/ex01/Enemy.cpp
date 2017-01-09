// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Enemy.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/20 20:18:10 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/20 22:30:47 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Enemy.hpp"

//constructors and destructors

Enemy::Enemy(void) { return; }

Enemy::Enemy(int hp, std::string const &type) :
	_HP(hp), _type(type)
{
	std::cout << this->_type << " appeared" << std::endl;
	return ;
}

Enemy::Enemy(Enemy const &copy) :
	_HP(copy.getHP()), _type(copy.getType())
{
	return ;
}

Enemy::~Enemy(void)
{
	std::cout << this->_type << " has been slain" << std::endl;
	return ;
}

Enemy	&Enemy::operator=(Enemy const &copy)
{
	this->_HP = copy.getHP();
	this->_type = copy.getType();
	return *this;
}

//Functions

void	Enemy::takeDamage(int const amount)
{
	if (amount < 0)
		return ;
	if (this->_HP - amount >= 0)
	{
		std::cout << this->_type << " took " << amount << " damage" << std::endl;
		this->_HP -= amount;
	}
	else
        this->_HP = 0;
}

//Accessors

int					Enemy::getHP(void) const
{
	return this->_HP;
}

std::string	const	Enemy::getType(void) const
{
	return this->_type;
}
