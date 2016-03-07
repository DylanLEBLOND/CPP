// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Obstacle.class.hpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/21 22:19:48 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/21 22:19:49 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef OBSTACLE_CLASS_HPP

/*
** defines
*/
# define OBSTACLE_CLASS_HPP

/*
** includes
*/
# include "AStuff.class.hpp"

/*
** class
*/
class Obstacle : public AStuff
{
	public:
		Obstacle(char img = 'O');
		Obstacle(Obstacle const &copy);
		virtual ~Obstacle(void);
		virtual Obstacle	&operator=(Obstacle const &copy);

		virtual void		move(char direction = LEFT);
};

#endif //OBSTACLE_CLASS_HPP
