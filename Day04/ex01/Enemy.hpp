// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Enemy.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/20 20:18:21 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/20 21:05:11 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ENEMY_HPP
# define ENEMY_HPP

#include <iostream>

class Enemy
{

private:

	Enemy(void);

protected:

	int			_HP;
	std::string	_type;

public:

	Enemy(int hp, std::string const &type);
	Enemy(Enemy const &copy);
	virtual ~Enemy(void);
	Enemy	&operator=(Enemy const &copy);

	std::string const	getType(void) const;
	int					getHP(void) const;
	virtual void		takeDamage(int const amount);
};
#endif
