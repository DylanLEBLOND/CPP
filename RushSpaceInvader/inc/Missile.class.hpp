// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Missile.class.hpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/21 22:19:39 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/21 22:19:40 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MISSILE_CLASS_HPP

/*
** defines
*/
# define MISSILE_CLASS_HPP

/*
** includes
*/
# include "AStuff.class.hpp"

/*
** class
*/
class Missile : public AStuff
{
	public:
		Missile(char img = 'M');
		Missile(Missile const &copy);
		virtual ~Missile(void);
		virtual Missile		&operator=(Missile const &copy);

		virtual void		move(char direction = RIGHT);
};

#endif //MISSILE_CLASS_HPP
