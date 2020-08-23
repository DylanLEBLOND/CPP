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

/*
 * System Includes
 */
# include <stdlib.h>
# include <time.h>

class Board
{
private:

	unsigned int		_width;
	unsigned int		_height;
	bool				_multiPlayer;
	Snake*				_snakeP1;
	Snake*				_snakeP2;

	void				generateBonus (unsigned int number);

public:

	Board (void);
	Board (Board const &src);
	~Board (void);

	Board				&operator= (Board const &src);

	unsigned int		getWidth (void) const;
	unsigned int		getHeight (void) const;
	bool				getMultiPlayer (void) const;

	void				initBoard (unsigned int width, unsigned int height, bool multiPlayer);
	void				initPlayers (Snake *snakeP1, Snake *snakeP2);
	void				runTurn (void);
	bool				snakesAreAlive (void);
};

#endif /* BOARD_CLASS_HPP */
