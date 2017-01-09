// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ScavTrap.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/19 22:39:25 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/19 23:06:02 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

# include "ClapTrap.hpp"
# include <iostream>
# include <ctime>
# include <cstdlib>

class	ScavTrap : public ClapTrap
{

public:
	int		Hp;
	int		Ep;
	int		Lv;

	ScavTrap(void);
	ScavTrap(std::string name);
	ScavTrap(ScavTrap const &duplicate);
	ScavTrap	&operator=(ScavTrap const &duplicate);
	~ScavTrap(void);

	void	rangedAttack(std::string const & target);
	void	meleeAttack(std::string const & target);
	void	takeDamage(unsigned int amount);
	void	beRepaired(unsigned int amount);
	void	challengeNewcomer(void);

private:
	
	std::string	_name;
	int	_MAd;
	int	_RAd;
	int	_ArDamRed;
	int	_MaxHp;
	int	_MaxEp;

};

#endif
