// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   PlasmaRifle.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/20 19:28:45 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/20 23:12:20 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef PLASMARIFLE_HPP
# define PLASMARIFLE_HPP

#include "AWeapon.hpp"

class PlasmaRifle : public AWeapon
{

public:
	PlasmaRifle(void);
	PlasmaRifle(PlasmaRifle const &copy);
	~PlasmaRifle(void);
	PlasmaRifle &operator=(PlasmaRifle const &copy);

	virtual void	attack(void) const;
};
#endif
