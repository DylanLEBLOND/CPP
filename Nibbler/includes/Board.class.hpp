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
# include <tgmath.h>

/*
 * Enumerations
 */
enum class eBoardMaps { Classic, Lines, Blocks, Tribal, Borderless, LinesBorderless, BlocksBorderless, UnknownMap };

enum class eBoardStatus { Playing, Player1Win, Player1Lose, Player2Win, Player2Lose, Draw, UnknownStatus };

enum eboadMode
{
	Default			= 0,		/* SiglePlayer / FriendlyFire / Finish Score (this flag and all others are mutually exclusive) */
	Multiplayer		= 1 << 0,	/* Multiplayer */
	NoFriendlyFire	= 1 << 1,	/* Cannot eat himself or an ally */
	Endless			= 1 << 2	/* The map doesn't end before at least one player is dead */
};

class Board
{
private:

	unsigned int						_width;
	unsigned int						_height;
	eBonusMapScale						_mapSize;
	eBoardMaps							_currentMap;
	std::vector< std::vector<int> >*	_boardCells;
	std::vector<t_cell>					_boardEmptyCells;
	unsigned int						_boardCompletedScore;
	bool								_initialized;

	Snake*								_snakeP1;
	Snake*								_snakeP2;
	eboadMode							_boardMode;
	eBoardStatus						_boardStatus;
	bool								_playersInitialized;

	Bonus								_bonus1;
	Bonus								_bonus2;

	void								loadMapClassic (void);
	void								loadMapLines (void);
	void								loadMapBlocks (void);
	void								loadMapTribal (void);
	void								loadMapBorderless (void);
	void								loadMapLinesBorderless (void);
	void								loadMapBlocksBorderless (void);

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
	int									getBoardCompletedScore (void) const;
	eboadMode							getBoardMode (void) const;
	eBoardStatus						getBoardStatus (void) const;
	bool								isInitialized (void) const;

	void								initBoard (unsigned int width, unsigned int height, eboadMode boardMode);
	void								setMultiPlayerMode (bool activate);
	void								loadMap (eBoardMaps map);
	void								initPlayers (Snake *snakeP1, Snake *snakeP2);
	void								runTurn (void);
	bool								snakesAreAlive (void);
	bool								boardIsCompleted (void);
	void								clearBoard (void);
};

#endif /* BOARD_CLASS_HPP */
