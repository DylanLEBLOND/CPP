// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Fixed.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/18 16:15:20 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/18 23:10:34 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Fixed.hpp"

//static

int	const	Fixed::_nb_ft = 8;

//constructor and destructor

Fixed::Fixed(void) : _nb(0)
{
	std::cout << "Default Constructor called" << std::endl;
	return ;
}

Fixed::Fixed(int const n) : _nb(n << this->_nb_ft)
{
	std::cout << "Int Constructor called" << std::endl;
	return ;
}

Fixed::Fixed(float const n)
{
	this->_nb = roundf(n * (1 << this->_nb_ft));
	std::cout << "Float Constructor called" << std::endl;
	return ;
}

Fixed::Fixed(Fixed const &src)
{
	std::cout << "Copy Constructor called" << std::endl;
	*this = src;
	return ;
}

Fixed::~Fixed(void)
{
	std::cout << "Destructor called" << std::endl;
	return ;
}

//Comparaisons Operators Overload

bool	Fixed::operator>(Fixed const &src) const
{
	return this->_nb > src.getRawBits();
}

bool	Fixed::operator<(Fixed const &src) const
{
	return this->_nb < src.getRawBits();
}

bool	Fixed::operator>=(Fixed const &src) const
{
	return this->_nb >= src.getRawBits();
}

bool	Fixed::operator<=(Fixed const &src) const
{
	return this->_nb <= src.getRawBits();
}
bool	Fixed::operator==(Fixed const &src) const
{
	return this->_nb == src.getRawBits();
}

bool	Fixed::operator!=(Fixed const &src) const
{
	return this->_nb != src.getRawBits();
}

//Affectation Operators Overload

Fixed	&Fixed::operator=(Fixed const &src)
{
	this->_nb = src.getRawBits();
	return *this;
}

Fixed	&Fixed::operator++(void)
{
	this->_nb++;
	return *this;
}

Fixed	Fixed::operator++(int)
{
	Fixed	Before(*this);

	this->operator++();
	return Before;
}

Fixed	&Fixed::operator--(void)
{
	this->_nb--;
	return *this;
}

Fixed	Fixed::operator--(int)
{
	Fixed	Before(*this);

	this->operator--();
	return Before;
}

//Arithmetic Operatorcs Overload

Fixed	Fixed::operator+(Fixed const &src) const
{
	Fixed	r;

	r.setRawBits(this->_nb + src.getRawBits());
	return r;
}

Fixed	Fixed::operator-(Fixed const &src) const
{
	Fixed r;

	r.setRawBits(this->_nb - src.getRawBits());
	return r;
}

Fixed	Fixed::operator*(Fixed const &src) const
{
	Fixed r;

	r.setRawBits((float)this->_nb * (float)src.getRawBits() / (float)(1 << this->_nb_ft));
	return r;
}

Fixed	Fixed::operator/(Fixed const &src) const
{
	Fixed r;

	if (src.getRawBits() != 0)
		r.setRawBits((float)this->_nb / (float)src.getRawBits() * (float)(1 << this->_nb_ft));
	return r;
}
//Getter and Setter

float	Fixed::toFloat(void) const
{
	return (float)this->_nb / (float)(1 << this->_nb_ft);
}

int		Fixed::toInt(void) const
{
	return this->_nb >> this->_nb_ft;
}

int			 Fixed::getRawBits(void) const
{
	return this->_nb;
}

void		Fixed::setRawBits(int const raw)
{
	this->_nb = raw;
	return ;
}

//Non Member Functions

std::ostream    &operator<<(std::ostream &stream, Fixed const &src)
{
    stream << src.toFloat();
    return stream;
}

//Overload

Fixed			&Fixed::min(Fixed &s1, Fixed &s2)
{
	return s1 > s2 ? s2 : s1;
}

Fixed const		&Fixed::min(Fixed const &s1, const Fixed &s2)
{
	return s1 > s2 ? s2 : s1;
}

Fixed			&Fixed::max(Fixed &s1, Fixed &s2)
{
	return s1 < s2 ? s2 : s1;
}

Fixed const		&Fixed::max(Fixed const &s1, const Fixed &s2)
{
	return s1 < s2 ? s2 : s1;
}
