// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SuperMutant.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/20 20:52:01 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/20 23:36:40 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SUPERMUTANT_HPP
# define SUPERMUTANT_HPP

# include "Enemy.hpp"

class SuperMutant : public Enemy
{

public:

	SuperMutant(void);
	SuperMutant(SuperMutant const &copy);
	virtual ~SuperMutant(void);

	SuperMutant   &operator=(SuperMutant const &copy);

	virtual void	takeDamage(int const amount);
};

#endif
