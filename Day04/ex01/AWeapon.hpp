// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AWeapon.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/20 19:09:34 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/20 23:24:01 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef AWEAPON_HPP
# define AWEAPON_HPP

#include <iostream>

class AWeapon
{
private:

	AWeapon(void);

protected:

	std::string	_name;
	int			_dam;
	int			_APcost;

public:

	AWeapon(std::string const & name, int apcost, int damage);
	AWeapon(AWeapon const &copy);
	virtual	~AWeapon();
	AWeapon	&operator=(AWeapon const &copy);

	std::string const	getName() const;
	int					getAPCost() const;
	int					getDamage() const;
	virtual void		attack() const = 0;
};
#endif
