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
enum class eBoardMaps { Classic,
						Lines,
						Blocks,
						Borderless,
						LinesBorderless,
						BlocksBorderless,
						Tribal,
						LinesTribal,
						BlocksTribal,
						UnknownMap };

enum class eBoardStatus { Playing,
						  Player1Win,
						  Player1Lose,
						  Player2Win,
						  Player2Lose,
						  Draw,
						  Forfeit,
						  UnknownStatus };

enum eboadMode : unsigned int
{
	Default			= 0,		/* SinglePlayer / BasicFood / FriendlyFire / Finish Score (this flag and all others are mutually exclusive) */
	SpecialFood		= 1 << 0,	/* Food had differents values and disappear after a certain time */
	Multiplayer		= 1 << 1,	/* Multiplayer */
	NoFriendlyFire	= 1 << 2,	/* Cannot eat himself or an ally */
	Endless			= 1 << 3	/* The map doesn't end before at least one player is dead */
};

/*
 * Defines
 */
# ifdef DEBUG_MODE

#  ifndef print_trace
#   define print_trace(message, eol)				\
{													\
	std::cout << (message);							\
	if (eol)										\
		std::cout << std::endl;						\
}
#endif

# else

#  ifndef print_trace
#   define print_trace(message, eol) {}
#  endif

# endif

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
	void								loadMapBorderless (void);
	void								loadMapLinesBorderless (void);
	void								loadMapBlocksBorderless (void);
	void								loadMapTribal (void);
	void								loadMapLinesTribal (void);
	void								loadMapBlocksTribal (void);

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
	void								forfeitBoard (void);
	bool								snakesAreAlive (void);
	bool								boardIsCompleted (void);
	void								clearBoard (void);
};

#endif /* BOARD_CLASS_HPP */
