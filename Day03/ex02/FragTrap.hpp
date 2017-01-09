// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   FragTrap.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/19 02:03:55 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/19 23:05:36 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

# include "ClapTrap.hpp"
# include <iostream>
# include <ctime>
# include <cstdlib>

class	FragTrap : public ClapTrap
{

public:
	int		Hp;
	int		Ep;
	int		Lv;

	FragTrap(void);
	FragTrap(std::string name);
	FragTrap(FragTrap const &duplicate);
	FragTrap	&operator=(FragTrap const &duplicate);
	~FragTrap(void);

	void	rangedAttack(std::string const & target);
	void	meleeAttack(std::string const & target);
	void	takeDamage(unsigned int amount);
	void	beRepaired(unsigned int amount);
	void	vaulthunter_dot_exe(std::string const & target);

private:
	
	std::string	_name;
	int	_MAd;
	int	_RAd;
	int	_ArDamRed;
	int	_MaxHp;
	int	_MaxEp;

};

#endif
