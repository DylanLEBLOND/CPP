// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SuperMutant.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/20 20:59:17 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/20 23:22:25 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "SuperMutant.hpp"

SuperMutant::SuperMutant(void) : Enemy(180, "Super Mutant")
{
	std::cout << "Gaaah. Me want smash heads !" << std::endl;
	return ;
}

SuperMutant::SuperMutant(SuperMutant const &copy) : Enemy(copy)
{
    return ;
}

SuperMutant::~SuperMutant(void)
{
	std::cout << "Aaargh ..." << std::endl;
}

SuperMutant   &SuperMutant::operator=(SuperMutant const &copy)
{
    this->_HP = copy.getHP();
    this->_type = copy.getType();
    return *this;
}

void		SuperMutant::takeDamage(int const amount)
{
	if (amount < 0)
		return;
	if (this->_HP + 3 - amount >= 0)
	{
		std::cout << this->_type << " took " << amount - 3 << " damage" << std::endl;
        this->_HP = this->_HP + 3 - amount;
	}
	else
        this->_HP = 0;
}
