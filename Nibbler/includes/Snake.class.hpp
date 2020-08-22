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
# include <algorithm>
# include <list>

/*
 * Enumerations
 */
enum class eSnakeDirection { North, South, East, West, Unknown };

/*
 * Structures
 */
typedef struct s_cell
{
	int positionX;
	int positionY;

	bool operator== (const s_cell &rhs)
	{
		return this->positionX == rhs.positionX && this->positionY == rhs.positionY;
	}
}				t_cell;

class Snake
{
private:
	std::list<t_cell>		_snakeCells;
	eSnakeDirection			_currentDirection;
	bool					_canPassThroughWall;
	unsigned int			_mapSize;
	int						_eatCounter;
	bool					_isAlive;

public:

	Snake (void);
	Snake (unsigned int initPosX, unsigned int initPosY, unsigned int initSize, bool canPassThroughWall);
	Snake (Snake const &src);
	~Snake (void);

	Snake					&operator= (Snake const &src);

	bool					getIsAlive (void) const;
	std::list<t_cell>		getSnakeCells (void) const;
	eSnakeDirection			getCurrentDirection (void) const;
	bool					getCanPassThroughWall (void) const;
	unsigned int			getMapSize (void) const;

	void					setMapSize (unsigned int newSize);

	void					passThroughWall (bool active);
	void					eat (int value);
	void					goLeft (void);
	void					goRight (void);
	void					goUp (void);
	void					goDown (void);
	void					moveStraight (void);
};

#endif /* SNAKE_CLASS_HPP */
