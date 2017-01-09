// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   NinjaTrap.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/19 23:22:20 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/19 23:41:30 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "NinjaTrap.hpp"

//Constructor, Destructor And Affectation Overload

NinjaTrap::NinjaTrap(void): Hp(60), Ep(120), Lv(1), _name("NinjaTrap"), _MAd(60),
                          _RAd(5), _ArDamRed(0), _MaxHp(60), _MaxEp(120)
{
	srand(time(NULL));
	std::cout << "The unseen blade is the deadliest." << std::endl;
	return ;
}

NinjaTrap::NinjaTrap(std::string name): Hp(60), Ep(120), Lv(1), _MAd(60), _RAd(5),
									  _ArDamRed(0), _MaxHp(60), _MaxEp(120)
{
	srand(time(NULL));
	this->_name = name;
	std::cout << "Brave the shadows, find the truth." << std::endl;
    return ;
}

NinjaTrap::NinjaTrap(NinjaTrap const &duplicate): Hp(60), Ep(120), Lv(1), _MAd(60), _RAd(5),
											   _ArDamRed(0), _MaxHp(60), _MaxEp(120)
{
	srand(time(NULL));
	std::cout << "KAGE BUNSHIN NO JUTSU" << std::endl;
	*this = duplicate;
    return ;
}

NinjaTrap	&NinjaTrap::operator=(NinjaTrap const &duplicate)
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

NinjaTrap::~NinjaTrap(void)
{
	std::cout << "" << std::endl;
	return;
}

//Fuctions

void    NinjaTrap::rangedAttack(std::string const & target)
{
	std::cout << "I am the blade in the darkness." << std::endl;
	return ;
}

void    NinjaTrap::meleeAttack(std::string const & target)
{
	std::cout << "None escape their shadow." << std::endl;
    return ;
}

void    NinjaTrap::takeDamage(unsigned int amount)
{
	if ((int)amount - this->_ArDamRed > 0 && this->Hp > 0)
	{
		std::cout << "The merest shade of me... is enough to defeat you!" << std::endl;
		if (this->Hp - (int)amount + this->_ArDamRed >= 0)
			this->Hp = this->Hp - (int)amount + this->_ArDamRed;
		else
			this->Hp = 0;
	}
	else
		std::cout << "Ignorance is fatal." << std::endl;
    return ;
}

void    NinjaTrap::beRepaired(unsigned int amount)
{
	if ((int)amount + this->Hp <= this->_MaxHp)
	{
		this->Hp += (int)amount;
		std::cout << "The shadow is within" << std::endl;
	}
	else if (this->Hp < this->_MaxHp)
	{
		std::cout << "The shadows have enlightened me." << std::endl;
		this->Hp = 100;
	}
	else
		std::cout << "The shadows have enlightened me." << std::endl;
    return ;
}

void	NinjaTrap::ninjaShoebox(ClapTrap const &target)
{
	if (this->Ep < 40)
	{
		std::cout << "N1NJ4-TP " << this->_name
				  << ": Not enough mana." << std::endl;
		return ;
	}

	std::string     t[] = { "dance!", "eat my shoes!",
							"chew what?", "hold my box..." };
//    srand(static_cast<unsigned int>(time(NULL))); //TODO: bjorked?
	this->Ep -= 40;

	std::cout << "N1NJ4-TP " << this->_name 
			  << ": Come here FATHERTRAP " << target.getName() << ", and "
			  << t[rand() % static_cast<int>(sizeof(t) / sizeof(*t))]
			  << std::endl;
}

void	NinjaTrap::ninjaShoebox(FragTrap const &target)
{
	if (this->Ep < 40)
	{
		std::cout << "N1NJ4-TP " << this->_name
				  << ": Not enough mana." << std::endl;
		return ;
	}

	std::string     t[] = { "dance!", "eat my shoes!",
							"chew what?", "hold my box..." };
//    srand(static_cast<unsigned int>(time(NULL))); //TODO: bjorked?
	this->Ep -= 40;

	std::cout << "N1NJ4-TP " << this->_name 
			  << ": Come here FRAGTRAP " << target.getName() << ", and "
			  << t[rand() % static_cast<int>(sizeof(t) / sizeof(*t))]
			  << std::endl;
}

void	NinjaTrap::ninjaShoebox(ScavTrap const &target)
{
	if (this->Ep < 40)
	{
		std::cout << "N1NJ4-TP " << this->_name
				  << ": Not enough mana." << std::endl;
		return ;
	}

	std::string     t[] = { "dance!", "eat my shoes!",
							"chew what?", "hold my box..." };
//    srand(static_cast<unsigned int>(time(NULL))); //TODO: bjorked?
	this->Ep -= 40;

	std::cout << "N1NJ4-TP " << this->_name 
			  << ": Come here SCAVTRAP " << target.getName() << ", and "
			  << t[rand() % static_cast<int>(sizeof(t) / sizeof(*t))]
			  << std::endl;
}

void	NinjaTrap::ninjaShoebox(NinjaTrap const &target)
{
	if (this->Ep < 40)
	{
		std::cout << "N1NJ4-TP " << this->_name
				  << ": Not enough mana." << std::endl;
		return ;
	}

	std::string     t[] = { "dance!", "eat my shoes!",
							"... chew what?", "hold my box..." };
//    srand(static_cast<unsigned int>(time(NULL))); //TODO: bjorked?
	this->Ep -= 40;

	std::cout << "N1NJ4-TP " << this->_name 
			  << ": Come here NINJATRAP " << target.getName() << ", and "
			  << t[rand() % static_cast<int>(sizeof(t) / sizeof(*t))]
			  << std::endl;
}
