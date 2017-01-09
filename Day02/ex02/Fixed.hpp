// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Fixed.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/18 16:17:29 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/18 21:44:28 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <cmath>

class Fixed
{

public:

	Fixed(void);
	Fixed(int const n);
	Fixed(float const n);
	Fixed(Fixed const &src);
	~Fixed(void);

	Fixed	&operator=(Fixed const &src);
	Fixed	&operator++(void);
	Fixed	operator++(int);
	Fixed	&operator--(void);
	Fixed	operator--(int);

	Fixed	operator+(Fixed const &src) const;
	Fixed	operator-(Fixed const &src) const;
	Fixed	operator*(Fixed const &src) const;
	Fixed	operator/(Fixed const &src) const;

	static Fixed		&min(Fixed &s1, Fixed &s2);
	static Fixed const	&min(Fixed const &s1, const Fixed &s2);
	static Fixed		&max(Fixed &s1, Fixed &s2);
	static Fixed const	&max(Fixed const &s1, const Fixed &s2);

	bool			operator>(Fixed const &src) const;
	bool			operator<(Fixed const &src) const;
	bool			operator>=(Fixed const &src) const;
	bool			operator<=(Fixed const &src) const;
	bool			operator==(Fixed const &src) const;
	bool			operator!=(Fixed const &src) const;

	float	toFloat(void) const;
	int		toInt(void) const;
	int			 getRawBits(void) const;
	void	setRawBits(int const raw);

private:

	int					_nb;
	static int		 const	_nb_ft;
};

std::ostream	&operator<<(std::ostream &stream, Fixed const &src);

#endif
