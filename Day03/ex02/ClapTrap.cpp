// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ClapTrap.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/19 22:59:18 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/19 23:18:25 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ClapTrap.hpp"

//Constructor, Destructor And Affectation Overload

ClapTrap::ClapTrap(void): Hp(20), Ep(50), Lv(1), _name("ClapTrap 001"), _MAd(50),
                          _RAd(10), _ArDamRed(10), _MaxHp(200), _MaxEp(50)
{
	srand(time(NULL));
	std::cout << "Congratulation, you got a new default Claptrap, the \"";
	std::cout << this->_name << "\"" << std::endl;
	return ;
}

ClapTrap::ClapTrap(std::string name): Hp(200), Ep(50), Lv(1), _MAd(50), _RAd(10),
									  _ArDamRed(10), _MaxHp(200), _MaxEp(50)
{
	srand(time(NULL));
	this->_name = name;
	std::cout << "Congratulation, your ClapTrap \"";
	std::cout << this->_name << "\" is available" << std::endl;
    return ;
}

ClapTrap::ClapTrap(ClapTrap const &duplicate): Hp(200), Ep(50), Lv(1), _MAd(50), _RAd(10),
											   _ArDamRed(10), _MaxHp(200), _MaxEp(50)
{
	srand(time(NULL));
	std::cout << "Congratulation, you got the copy of the ClapTrap \"";
	std::cout << duplicate._name << "\"" << std::endl;
	*this = duplicate;
    return ;
}

ClapTrap	&ClapTrap::operator=(ClapTrap const &duplicate)
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

ClapTrap::~ClapTrap(void)
{
	std::cout << "You take too much damages you are dead" << std::endl;
	return;
}

//Fuctions

void    ClapTrap::rangedAttack(std::string const & target)
{
	std::cout << "FR4G-TP " << this->_name << " attacks " << target;
	std::cout << " at range, causing " << this->_RAd << " points of damage !" << std::endl;
	return ;
}

void    ClapTrap::meleeAttack(std::string const & target)
{
	std::cout << "FR4G-TP " << this->_name << " attacks " << target;
	std::cout << " at melee, causing " << this->_MAd << " points of damage !" << std::endl;
    return ;
}

void    ClapTrap::takeDamage(unsigned int amount)
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

void    ClapTrap::beRepaired(unsigned int amount)
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
