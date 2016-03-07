// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Enemy.class.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/21 22:19:30 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/21 22:19:31 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ENEMY_CLASS_HPP

/*
** defines
*/
# define ENEMY_CLASS_HPP

/*
** includes
*/
# include "AUnit.class.hpp"

/*
** class
*/
class Enemy : public AUnit
{
	public:
		Enemy(char img = 'E');
		Enemy(Enemy const &copy);
		virtual ~Enemy(void);
		virtual Enemy	&operator=(Enemy const &copy);

		virtual void	move(char direction = LEFT);
};

#endif //ENEMY_CLASS_HPP
