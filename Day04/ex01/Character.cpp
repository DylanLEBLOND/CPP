// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Character.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/20 21:12:33 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/20 23:38:26 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Character.hpp"

//Constructors and Destructor

Character::Character(void) { return ; }

Character::Character(std::string const &name) :
	_name(name), _AP(40), _weap(NULL)
{
	std::cout << this->_name << " has been created." << std::endl;
	return ;
}

Character::Character(Character const &copy)
{
	*this = copy;
	std::cout << this->_name << " has been created." << std::endl;
    return ;
}

Character::~Character(void)
{
	std::cout << this->_name << " has been slain." << std::endl;
    return ;
}

//Operator Overload

Character &Character::operator=(Character const &copy)
{
	this->_name = copy.getName();
	this->_AP = copy.getAP();
	this->_weap = copy.getWeapon();

	return *this;
}

std::ostream	&operator<<(std::ostream &o, Character const &P1)
{
	if (P1.getWeapon())
		o << P1.getName() << " has " << P1.getAP() << " AP and wields a " << P1.getWeapon()->getName() << std::endl;
	else
		o << P1.getName() << " has " << P1.getAP() << " AP and is unarmed" << std::endl;
	return o;
}

//Functions

void    Character::recoverAP(void)
{
	if (this->_AP < 40)
	{
		this->_AP += 10;
		std::cout << "You recovered 10 AP" << std::endl;
	}
	else
		std::cout << "You can't gain more AP" << std::endl;
}

void    Character::equip(AWeapon* weap)
{
	this->_weap = weap;
	std::cout << this->_name << " gets " << weap->getName() << std::endl;
	return ;
}

void    Character::attack(Enemy* enemy)
{
	if (this->_AP == 0)
	{
		std::cout << "No AP, No Attack" << std::endl;
		return;
	}
	if (!this->_weap)
	{
		std::cout << "You don't have weapon for attack" << std::endl;
		return;
	}
	std::cout << this->_name << " attacks " << enemy->getType() << " with ";
	std::cout << this->_weap->getName() << std::endl;
	this->_weap->attack();
	enemy->takeDamage(this->_weap->getDamage());
	if (enemy->getHP() <= 0)
		delete enemy;
	this->_AP -= this->_weap->getAPCost();
	return ;
}

//Accessors

std::string const   Character::getName(void) const
{
	return this->_name;
}

int					Character::getAP(void) const
{
	return this->_AP;
}

AWeapon				*Character::getWeapon(void) const
{
	return this->_weap;
}
