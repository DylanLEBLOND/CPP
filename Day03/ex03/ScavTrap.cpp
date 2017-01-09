// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ScavTrap.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/19 22:39:44 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/19 23:15:59 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ScavTrap.hpp"

//Constructor, Destructor And Affectation Overload

ScavTrap::ScavTrap(void): Hp(100), Ep(50), Lv(1), _name("ScavTrap 001"), _MAd(20),
                          _RAd(15), _ArDamRed(3), _MaxHp(100), _MaxEp(50)
{
	srand(time(NULL));
	std::cout << "Congratulation, you got a new default Scavtrap, the \"";
	std::cout << this->_name << "\"" << std::endl;
	return ;
}

ScavTrap::ScavTrap(std::string name): Hp(100), Ep(50), Lv(1), _MAd(20), _RAd(15),
									  _ArDamRed(3), _MaxHp(100), _MaxEp(50)
{
	srand(time(NULL));
	this->_name = name;
	std::cout << "Congratulation, your ScavTrap \"";
	std::cout << this->_name << "\" is available" << std::endl;
    return ;
}

ScavTrap::ScavTrap(ScavTrap const &duplicate): Hp(100), Ep(50), Lv(1), _MAd(20), _RAd(15),
											   _ArDamRed(3), _MaxHp(100), _MaxEp(50)
{
	srand(time(NULL));
	std::cout << "Congratulation, you got the copy of the ScavTrap \"";
	std::cout << duplicate._name << "\"" << std::endl;
	*this = duplicate;
    return ;
}

ScavTrap	&ScavTrap::operator=(ScavTrap const &duplicate)
{
	this->_name = duplicate._name;
	this->Hp = duplicate.Hp;
	this->_MaxHp = duplicate._MaxHp;
	this->Ep = duplicate.Ep;
	this->_MaxEp = duplicate._MaxEp;
	this->Lv = duplicate.Lv;
	this->_MAd = duplicate._MAd;
	this->_RAd = duplicate._RAd;
	this->_ArDamRed = duplicate._ArDamRed;
	return *this;
}

ScavTrap::~ScavTrap(void)
{
	std::cout << "You take too much damages you are dead" << std::endl;
	return;
}

//Fuctions

void    ScavTrap::rangedAttack(std::string const & target)
{
	std::cout << "SC4V-TP " << this->_name << " attacks " << target;
	std::cout << " at range, causing " << this->_RAd << " points of damage !" << std::endl;
	return ;
}

void    ScavTrap::meleeAttack(std::string const & target)
{
	std::cout << "SC4V-TP " << this->_name << " attacks " << target;
	std::cout << " at melee, causing " << this->_MAd << " points of damage !" << std::endl;
    return ;
}

void    ScavTrap::takeDamage(unsigned int amount)
{
	if ((int)amount - this->_ArDamRed > 0 && this->Hp > 0)
	{
		std::cout << "Oh no, you took (" << amount << " - " << this->_ArDamRed;
		std::cout << ") " << (int)amount - this->_ArDamRed << " damage points" << std::endl;
		if (this->Hp - (int)amount + this->_ArDamRed >= 0)
			this->Hp = this->Hp - (int)amount + this->_ArDamRed;
		else
			this->Hp = 0;
	}
	else
		std::cout << "Yes, the SC4V-TP's shield absorbed all damage" << std::endl;
    return ;
}

void    ScavTrap::beRepaired(unsigned int amount)
{
	if ((int)amount + this->Hp <= this->_MaxHp)
	{
		this->Hp += (int)amount;
		std::cout << "You have gain " << amount << " Hp (" << this->Hp << ")" << std::endl;
	}
	else if (this->Hp < this->_MaxHp)
	{
		std::cout << "You have gain " << this->_MaxHp - this->Hp << " Hp (100)" << std::endl;
		this->Hp = 100;
	}
	else
		std::cout << "Your Hit Points (Hp) are already full (" << this->Hp << ")" << std::endl;
    return ;
}

void	ScavTrap::challengeNewcomer(void)
{
	std::string	challs[5] = {
		"Smash Mat",
		"Cry Like A Baby",
		"Bof I'm Tired",
		"Perfect Kills",
		"FIOWRJGRW"};

	if (this->Ep - 25 < 0)
	{
		std::cout << "You are out of Energy you can make nothing now :/" << std::endl;
		return;
	}
	std::cout << "You got the challenge : "
			  << challs[rand() % static_cast<int>(sizeof(challs) / sizeof(*challs))]
			  << "." << std::endl;
	this->Ep -= 25;
	return ;
}
