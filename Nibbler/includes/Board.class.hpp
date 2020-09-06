// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Board.class.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/08/10 16:19:09 by dle-blon          #+#    #+#             //
//   Updated: 2020/08/16 15:23:32 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef BOARD_CLASS_HPP
# define BOARD_CLASS_HPP

/*
 * Personals Includes
 */
# include <Exceptions.hpp>
# include <Snake.class.hpp>
# include <Bonus.class.hpp>

/*
 * System Includes
 */
# include <vector>
# include <algorithm>
# include <stdlib.h>
# include <time.h>

/*
 * Enumerations
 */
enum class eBoardMaps { Square, Open, UnknownMap };

class Board
{
private:

	unsigned int						_width;
	unsigned int						_height;
	std::vector< std::vector<int> >*	_boardCells;
	std::vector<t_cell>					_boardEmptyCells;
	bool								_initialized;

	bool								_multiPlayer;
	bool								_friendlyFire;

	Snake*								_snakeP1;
	Snake*								_snakeP2;
	bool								_playersInitialized;

	Bonus								_bonus1;
	Bonus								_bonus2;

	void								loadMapSquare (void);
	void								loadMapOpen (void);

	void								updateBonus (void);
	void								checkSnakesCollision (void);

public:

	Board (void);
	Board (Board const &src);
	~Board (void);

	Board								&operator= (Board const &src);

	unsigned int						getWidth (void) const;
	unsigned int						getHeight (void) const;
	std::vector< std::vector<int> >		*getBoardCells (void) const;
	bool								isInitialized (void) const;

	void								initBoard (unsigned int width, unsigned int height);
	void								initPlayers (Snake *snakeP1, Snake *snakeP2, bool multiPlayer, bool friendlyFire);
	void								loadMap (eBoardMaps map);
	void								runTurn (void);
	bool								snakesAreAlive (void);
	void								clearBoard (void);
};

#endif /* BOARD_CLASS_HPP */
