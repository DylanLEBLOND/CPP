// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   RadScorpion.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/20 21:06:10 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/20 23:36:22 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef RADSCORPION_HPP
# define RADSCORPION_HPP

# include "Enemy.hpp"

class RadScorpion : public Enemy
{

public:

	RadScorpion(void);
	RadScorpion(RadScorpion const &copy);
	virtual ~RadScorpion(void);

	RadScorpion   &operator=(RadScorpion const &copy);
};

#endif
