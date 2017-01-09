// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Character.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/20 21:12:21 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/20 21:57:05 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CHARACTER_HPP
# define CHARACTER_HPP

# include <iostream>
# include "AWeapon.hpp"
# include "PlasmaRifle.hpp"
# include "PowerFist.hpp"
# include "SuperMutant.hpp"
# include "RadScorpion.hpp"

class Character
{

private:

	Character(void);

protected:

	std::string	_name;
	int			_AP;
	AWeapon		*_weap;

public:

	Character(std::string const &name);
	Character(Character const &copy);
	~Character(void);
	Character &operator=(Character const &copy);

	void	recoverAP(void);
	void	equip(AWeapon* weap);
	void	attack(Enemy* enemy);

	std::string const	getName(void) const;
	int					getAP(void) const;
	AWeapon				*getWeapon(void) const;

};

std::ostream	&operator<<(std::ostream &o, Character const &P1);

#endif
