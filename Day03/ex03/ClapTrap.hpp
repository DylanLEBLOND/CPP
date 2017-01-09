// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ClapTrap.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/19 23:00:41 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/19 23:10:26 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# include <iostream>
# include <ctime>
# include <cstdlib>

class	ClapTrap
{

public:
	int		Hp;
	int		Ep;
	int		Lv;

	ClapTrap(void);
	ClapTrap(std::string name);
	ClapTrap(ClapTrap const &duplicate);
	ClapTrap	&operator=(ClapTrap const &duplicate);
	~ClapTrap(void);

	void	rangedAttack(std::string const & target);
	void	meleeAttack(std::string const & target);
	void	takeDamage(unsigned int amount);
	void	beRepaired(unsigned int amount);

private:
	
	std::string	_name;
	int	_MAd;
	int	_RAd;
	int	_ArDamRed;
	int	_MaxHp;
	int	_MaxEp;

};

#endif
