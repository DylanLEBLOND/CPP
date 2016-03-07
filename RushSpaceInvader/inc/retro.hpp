// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   retro.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/21 22:20:09 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/21 22:20:12 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef RETRO_CLASS_HPP

/*
** defines
*/
# define RETRO_CLASS_HPP
# define EXIT    27

/*
** includes
*/
# include "Player.class.hpp"
# include "Enemy.class.hpp"
# include "Missile.class.hpp"
# include "Obstacle.class.hpp"
# include <ctime>
# include <sys/time.h>
# include <unistd.h> //debug

/*
** prototypes
*/
char		promptUser(void);
bool        moveAll(char key, Obstacle **o, Enemy **e, Player *p);
bool		checkAllCollisions(Obstacle **o, Enemy **e, Player *p);
void		framePrint(Obstacle **o, Enemy **e, Player p);
void		gameLoop(void);

#endif //RETRO_CLASS_HPP
