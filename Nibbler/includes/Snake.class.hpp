// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Snake.class.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/08/10 16:10:47 by mnguyen           #+#    #+#             //
//   Updated: 2020/08/16 15:23:32 by mnguyen          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SNAKE_CLASS_HPP
# define SNAKE_CLASS_HPP

/*
 * Personals Includes
 */
# include <Exceptions.hpp>
# include <common.hpp>

/*
 * System Includes
 */
# include <iostream>
# include <algorithm>
# include <list>

/*
 * Enumerations
 */
enum class eSnakeDirection { North, South, East, West, UnknownDirection };

/*
 * Structures
 */
typedef struct s_cell
{
	int positionX;
	int positionY;

	s_cell &operator= (const s_cell &rhs)
	{
		this->positionX = rhs.positionX;
		this->positionY = rhs.positionY;
		return *this;
	}

	bool operator== (const s_cell &rhs)
	{
		return this->positionX == rhs.positionX && this->positionY == rhs.positionY;
	}
}				t_cell;

/*
 * Defines
 */
# define SNAKE_SCORE_MAX				NIBBLER_BOARD_MAX_WIDTH * NIBBLER_BOARD_MAX_HEIGHT + 1

class Snake
{
private:
	std::list<t_cell>		_snakeCells;
	eSnakeDirection			_currentDirection;
	bool					_canPassThroughWall;
	bool					_canEatHimself;
	unsigned int			_mapWidth;
	unsigned int			_mapHeight;
	int						_eatCounter;
	unsigned int			_score;
	bool					_isAlive;

public:

	Snake (void);
	Snake (Snake const &src);
	~Snake (void);

	Snake					&operator= (Snake const &src);

	bool					isAlive (void) const;
	std::list<t_cell>		getSnakeCells (void) const;
	eSnakeDirection			getCurrentDirection (void) const;
	bool					getCanPassThroughWall (void) const;
	bool					getCanEatHimself (void) const;
	unsigned int			getMapWidth (void) const;
	unsigned int			getMapHeight (void) const;
	unsigned int			getScore (void) const;

	void					setMapWidth (unsigned int newWidth);
	void					setMapHeight (unsigned int newHeight);

	void					initSnake (unsigned int initPosX, unsigned int initPosY,
									   unsigned int initSize, eSnakeDirection initDirection,
									   bool canPassThroughWall, bool canEatHimself);
	void					passThroughWall (bool active);
	void					eat (int value);
	void					dead (void);
	void					goLeft (void);
	void					goRight (void);
	void					goUp (void);
	void					goDown (void);
	void					moveStraight (void);
};

#endif /* SNAKE_CLASS_HPP */
