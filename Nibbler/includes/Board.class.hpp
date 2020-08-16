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

/*
 * System Includes
 */


class Board
{
private:

	int _size;

public:

	Board(void);
	Board (int size);
	Board(Board const &src);
	~Board(void);

	Board		&operator=(Board const &src);

	int			getSize(void) const;
};

#endif /* BOARD_CLASS_HPP */
