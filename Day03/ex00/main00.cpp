// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/19 04:03:59 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/19 22:52:47 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ex00/FragTrap.hpp"

int		main(void)
{
	FragTrap ft1("Alf");
	FragTrap ft2("Bob");
	FragTrap ft3(ft1);
	std::cout << std::endl;


	ft3 = ft2;
	std::cout << std::endl;

	ft1.rangedAttack("Bob");
	std::cout << std::endl;

	ft1.meleeAttack("Bob");
	std::cout << std::endl;

	ft1.takeDamage(3);
	std::cout << std::endl;

	ft1.beRepaired(3);
	std::cout << std::endl;

	ft1.takeDamage(1000);
	std::cout << std::endl;

	ft1.beRepaired(1000);
	std::cout << std::endl;

	ft1.beRepaired(3);
	std::cout << std::endl;

	ft1.Ep = 100;
	std::cout << std::endl;

	ft1.vaulthunter_dot_exe("1");
	ft1.vaulthunter_dot_exe("2");
	ft1.vaulthunter_dot_exe("3");
	ft1.vaulthunter_dot_exe("4");
	ft1.vaulthunter_dot_exe("5");
	std::cout << std::endl;

	return (0);
}
