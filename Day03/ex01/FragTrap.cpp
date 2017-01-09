// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   FragTrap.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/19 02:04:30 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/19 23:17:45 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "FragTrap.hpp"

//Constructor, Destructor And Affectation Overload

FragTrap::FragTrap(void): Hp(100), Ep(100), Lv(1), _name("FragTrap 001"), _MAd(30),
                          _RAd(20), _ArDamRed(5), _MaxHp(100), _MaxEp(100)
{
	srand(time(NULL));
	std::cout << "Congratulation, you got a new default Fragtrap, the \"";
	std::cout << this->_name << "\"" << std::endl;
	return ;
}

FragTrap::FragTrap(std::string name): Hp(100), Ep(100), Lv(1), _MAd(30), _RAd(20),
									  _ArDamRed(5), _MaxHp(100), _MaxEp(100)
{
	srand(time(NULL));
	this->_name = name;
	std::cout << "Congratulation, your FragTrap \"";
	std::cout << this->_name << "\" is available" << std::endl;
    return ;
}

FragTrap::FragTrap(FragTrap const &duplicate): Hp(100), Ep(100), Lv(1), _MAd(30), _RAd(20),
											   _ArDamRed(5), _MaxHp(100), _MaxEp(100)
{
	srand(time(NULL));
	std::cout << "Congratulation, you got the copy of the FragTrap \"";
	std::cout << duplicate._name << "\"" << std::endl;
	*this = duplicate;
    return ;
}

FragTrap	&FragTrap::operator=(FragTrap const &duplicate)
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

FragTrap::~FragTrap(void)
{
	std::cout << "You take too much damages you are dead" << std::endl;
	return;
}

//Fuctions

void    FragTrap::rangedAttack(std::string const & target)
{
	std::cout << "FR4G-TP " << this->_name << " attacks " << target;
	std::cout << " at range, causing " << this->_RAd << " points of damage !" << std::endl;
	return ;
}

void    FragTrap::meleeAttack(std::string const & target)
{
	std::cout << "FR4G-TP " << this->_name << " attacks " << target;
	std::cout << " at melee, causing " << this->_MAd << " points of damage !" << std::endl;
    return ;
}

void    FragTrap::takeDamage(unsigned int amount)
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
		std::cout << "Yes, the FR4G-TP's shield absorbed all damage" << std::endl;
    return ;
}

void    FragTrap::beRepaired(unsigned int amount)
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

void	FragTrap::vaulthunter_dot_exe(std::string const &target)
{
	std::string	attacks[5] = {
		"Death Ball",
		"A",
		"SegFault",
		"Laser",
		"B"};

	if (this->Ep - 25 < 0)
	{
		std::cout << "You are out of Energy you can make nothing now :/" << std::endl;
		return;
	}
	if (rand() % 5 != 0)
		std::cout << "FR4G-TP " << this->_name
				  << " attacks " << target
				  << " with " << attacks[rand() % static_cast<int>(sizeof(attacks) / sizeof(*attacks))]
				  << ", causing " << rand() % 50
				  << " points of damage !" << std::endl;
	else
	{
		std::cout << "FR4G-TP " << this->_name
				  << " failed his attack to " << target
				  << " with " << attacks[rand() % static_cast<int>(sizeof(attacks) / sizeof(*attacks))]
				  << " and took himself 25 points of damage !" << std::endl;
		if (this->Hp - 25 >= 0)
			this->Hp -= 25;
		else
			this->Hp = 0;
	}
	this->Ep -= 25;
	return ;
}
