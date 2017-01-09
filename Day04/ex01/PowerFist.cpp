// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   PowerFist.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/20 20:14:39 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/20 23:24:26 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "PowerFist.hpp"

PowerFist::PowerFist(void) : AWeapon("Power Fist", 8, 50)
{
	return ;
}

PowerFist::PowerFist(PowerFist const &copy) : AWeapon(copy)
{
    return ;
}

PowerFist::~PowerFist(void)
{
	return ;
}

PowerFist &PowerFist::operator=(PowerFist const &copy)
{
    this->_name = copy.getName();
    this->_dam = copy.getDamage();
    this->_APcost = copy.getAPCost();

    return *this;
}

void	PowerFist::attack(void) const
{
	std::cout << "* pschhh... SBAM! *" << std::endl;
	return ;
}
