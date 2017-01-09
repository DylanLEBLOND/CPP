// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AWeapon.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/20 19:09:32 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/20 20:13:33 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "AWeapon.hpp"

//Constructors & Destructor

//AWeapon:AWeapon(void) { return; }

AWeapon::AWeapon(std::string const &name, int apcost, int damage):
	_name(name), _dam(damage), _APcost(apcost)
{
	return ;
}

AWeapon::AWeapon(AWeapon const &copy)
{
	*this = copy;
	return ; 
}

AWeapon::~AWeapon(void)
{
	return ;
}

AWeapon		&AWeapon::operator=(AWeapon const &copy)
{
	this->_name = copy.getName();
	this->_dam = copy.getDamage();
	this->_APcost = copy.getAPCost();

	return *this;
}

//Accessors

std::string const   AWeapon::getName() const
{
	return this->_name;
}

int                 AWeapon::getAPCost() const
{
	return this->_APcost;
}

int                 AWeapon::getDamage() const
{
	return this->_dam;
}
