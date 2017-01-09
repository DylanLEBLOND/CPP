// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   PlasmaRifle.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/20 19:28:39 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/20 23:22:51 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "PlasmaRifle.hpp"

PlasmaRifle::PlasmaRifle(void) : AWeapon("Plasma Rifle", 5, 21)
{
	return ;
}

PlasmaRifle::PlasmaRifle(PlasmaRifle const &copy) : AWeapon(copy)
{
    return ;
}

PlasmaRifle::~PlasmaRifle(void)
{
	return ;
}

PlasmaRifle &PlasmaRifle::operator=(PlasmaRifle const &copy)
{
	this->_name = copy.getName();
    this->_dam = copy.getDamage();
    this->_APcost = copy.getAPCost();

    return *this;
}

void	PlasmaRifle::attack(void) const
{
	std::cout << "* piouuu piouuu piouuu *" << std::endl;
	return ;
}
