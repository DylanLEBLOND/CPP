// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Bonus.class.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/08/10 16:19:09 by dle-blon          #+#    #+#             //
//   Updated: 2020/08/16 15:23:32 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef BONUS_CLASS_HPP
# define BONUS_CLASS_HPP

/*
 * Personals Includes
 */

/*
 * System Includes
 */
# include <iostream>
# include <stdlib.h>
# include <time.h>

/*
 * Enumerations
 */
enum eBonusValue : unsigned int { CommonValue = 1,
								  UncommonValue = 2,
								  RareValue = 3,
								  LegendaryValue = 5,
								  GodlikeValue = 10,
								  UnknownValue = 99 };

enum eBonusTime : int { CommonTime = 50,
						UncommonTime = 30,
						RareTime = 20,
						LegendaryTime = 10,
						GodlikeTime = 5,
						InfiniteTime = -1,
						UnknownTime = 0 };

enum class eBonusMapScale { Small, Medium, Large, UnknownMapScale };

class Bonus
{
private:

	unsigned int		_x;
	unsigned int		_y;
	eBonusValue			_value;
	int					_timeLeft;
	bool				_isActif;

public:

	Bonus (void);
	Bonus (Bonus const &src);
	~Bonus (void);

	Bonus				&operator= (Bonus const &src);

	unsigned int		getX (void) const;
	unsigned int		getY (void) const;
	eBonusValue			getValue (void) const;
	int					getTimeLeft (void) const;
	bool				isActif (void) const;

	void				generate (unsigned int x, unsigned int y, eBonusMapScale mapSize, bool infinite);
	void				update (void);
	void				clear (void);
};

#endif /* BONUS_CLASS_HPP */
