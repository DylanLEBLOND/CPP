// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Fixed.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/18 15:40:52 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/18 16:05:45 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>

class Fixed
{

public:

	Fixed(void);
	Fixed(Fixed const &src);
	~Fixed(void);

	Fixed	&operator=(Fixed const &src);
	int		getRawBits(void) const;
	void	setRawBits(int const raw);

private:

	int					_nb;
	static int const	_nb_ft;
};

#endif
