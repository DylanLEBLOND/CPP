// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   NinjaTrap.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/19 23:22:33 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/19 23:39:12 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef NINJATRAP_HPP
# define NINJATRAP_HPP

# include "ClapTrap.hpp"
# include "FragTrap.hpp"
# include "ScavTrap.hpp"
# include <iostream>
# include <ctime>
# include <cstdlib>

class	NinjaTrap : public ClapTrap
{

public:
	int		Hp;
	int		Ep;
	int		Lv;

	NinjaTrap(void);
	NinjaTrap(std::string name);
	NinjaTrap(NinjaTrap const &duplicate);
	NinjaTrap	&operator=(NinjaTrap const &duplicate);
	~NinjaTrap(void);

	void	rangedAttack(std::string const & target);
	void	meleeAttack(std::string const & target);
	void	takeDamage(unsigned int amount);
	void	beRepaired(unsigned int amount);
	void	ninjaShoebox(ClapTrap const &target);
	void	ninjaShoebox(FragTrap const &target);
	void	ninjaShoebox(ScavTrap const &target);
	void	ninjaShoebox(NinjaTrap const &target);

private:
	
	std::string	_name;
	int	_MAd;
	int	_RAd;
	int	_ArDamRed;
	int	_MaxHp;
	int	_MaxEp;

};

#endif
