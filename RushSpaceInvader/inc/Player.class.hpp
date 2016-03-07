// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Player.class.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/21 22:19:57 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/21 22:19:59 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef PLAYER_CLASS_HPP

/*
** defines
*/
# define PLAYER_CLASS_HPP

/*
** includes
*/
# include "AUnit.class.hpp"

/*
** class
*/
class Player : public AUnit
{
	public:
		Player(char img = 'S', std::string name = "Player1");
		Player(Player const &copy);
		virtual ~Player(void);
		virtual Player	&operator=(Player const &copy);

		virtual void	move(char direction = RIGHT);
		virtual void	debug(std::string s) const;

		int			 	getLives(void)	const;
		int				getScore(void)	const;
		std::string		getName(void)	const;
		void			setLives(int lives);
		void			setScore(int score);

	protected:
		std::string		_name;
		int				_lives;
		int				_score;
};

#endif //PLAYER_CLASS_HPP
