// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Snake.class.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/08/10 16:10:47 by dle-blon          #+#    #+#             //
//   Updated: 2020/08/16 15:23:32 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SNAKE_CLASS_HPP
# define SNAKE_CLASS_HPP

/*
 * Personals Includes
 */

/*
 * System Includes
 */
# include <iostream>
# include <list>

/*
 * Structures
 */
typedef struct s_cell
{
	int positionX;
	int positionY;
}				t_cell;

class Snake
{
private:
	std::list<t_cell>		_snakeCells;
	int						_currrentSize;
	bool					_canPassThroughWall;

public:

	Snake (void);
	Snake (unsigned int initPosX, unsigned int initPosY, unsigned int initSize, bool canPassThroughWall);
	Snake (Snake const &src);
	~Snake (void);

	Snake		&operator= (Snake const &src);

	bool		getCanPassThroughWall (void) const;
	void		getHeadPosition (int *positionX, int *positionY) const;

	void		grow (int value);
	void		passThroughWall (bool active);
	void		moveLeft (void);
	void		moveRight (void);
	void		moveUp (void);
	void		moveDown (void);
};

#endif /* SNAKE_CLASS_HPP */
