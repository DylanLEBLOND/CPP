// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/20 19:36:07 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/20 23:38:03 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Character.hpp"

int		main(void)
{
	Character akali("Akali");

	std::cout << akali;
	
	PowerFist	a;
	PlasmaRifle	b;
	Enemy		*c = new Enemy(5, "Shaco");
	Enemy		*d = new Enemy(160, "Mundo");
	SuperMutant	e;
	RadScorpion	*f = new RadScorpion();

	akali.attack(c);
	std::cout << akali;
	akali.equip(&a);
	akali.attack(c);
	std::cout << akali;
	while (akali.getAP())
	{
		akali.attack(d);
		std::cout << akali;
	}
	akali.attack(d);
	std::cout << akali;
	while (akali.getAP() < 40)
		akali.recoverAP();
	akali.equip(&b);
	while (e.getHP() && akali.getAP())
		akali.attack(&e);
	std::cout << "PLANTE" << std::endl;
	while (akali.getAP() < 40)
        akali.recoverAP();
	while (f->getHP())
        akali.attack(f);
	return (0);
}
