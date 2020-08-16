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


class Snake
{
private:

public:

	Snake(void);
	Snake(Snake const &src);
	~Snake(void);

	Snake		&operator=(Snake const &src);
};

#endif /* SNAKE_CLASS_HPP */
