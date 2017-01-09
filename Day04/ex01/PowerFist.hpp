// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   PowerFist.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/20 20:15:47 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/20 23:16:45 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef POWERFIST_HPP
# define POWERFIST_HPP

#include "AWeapon.hpp"

class PowerFist : public AWeapon
{

public:
	PowerFist(void);
	PowerFist(PowerFist const &copy);
	~PowerFist(void);
	PowerFist &operator=(PowerFist const &copy);

	virtual void	attack(void) const;
};
#endif
