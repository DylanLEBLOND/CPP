// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AStuff.class.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/21 22:19:03 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/21 22:19:06 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ASTUFF_CLASS_HPP

/*
** defines
*/
# define ASTUFF_CLASS_HPP

# define DEBUG 0

# define NB_ENEMY 16 //TODO: edit value
# define NB_OBSTACLE 16 //TODO: edit value
# define NB_MISSILE 16 //TODO: edit value

# define WIDTH 50 //Edit
# define HEIGHT 50 //Edit

# define FRAME 100 //miliseconds

# define LEFT 'a'
# define RIGHT 'd'
# define UP 'w'
# define DOWN 's'
# define SHOOT ' ' //this need to be 0!

/*
** includes
*/
# include <iostream>
# include <ncurses.h>
# include <cstdlib>

/*
** class
*/
class AStuff
{
	public:
		AStuff(char img = 'S');
		AStuff(AStuff const &copy);
		virtual ~AStuff(void);
		virtual AStuff		&operator=(AStuff const &copy);

		int					getX(void)		const;
		int					getY(void)		const;
		char				getImg(void)	const;
		bool				getAlive(void)	const;
		void				setX(int x);
		void				setY(int y);
		void				setImg(char img);
		void				setAlive(bool alive);

		virtual void		move(char direction = RIGHT) = 0;
		virtual void		debug(std::string s) const;

	protected:
		char	_img;
		int		_x;
		int		_y;
		bool	_alive;
};

#endif //ASTUFF_CLASS_HPP
