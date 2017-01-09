// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Fixed.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/18 16:15:20 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/18 19:32:14 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Fixed.hpp"

//static

int	const	Fixed::_nb_ft = 8;

//constructor and destructor

Fixed::Fixed(void) : _nb(0 << this->_nb_ft)
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

//Operators Overload

Fixed	&Fixed::operator=(Fixed const &src)
{
	std::cout << "Assignation Overload called" << std::endl;
	this->_nb = src.getRawBits();
	return *this;
}

std::ostream	&operator<<(std::ostream &stream, Fixed const &src)
{
	stream << src.toFloat();
	return stream;
}

//Getter and Setter

float	Fixed::toFloat(void) const
{
	std::cout << "toFloat called" << std::endl;
	return (float)this->_nb / (float)(1 << this->_nb_ft);
}

int		Fixed::toInt(void) const
{
	std::cout << "toInt called" << std::endl;
	return this->_nb >> this->_nb_ft;
}

int			 Fixed::getRawBits(void) const
{
	std::cout << "Getter has been called" << std::endl;
	return this->_nb;
}

void		Fixed::setRawBits(int const raw)
{
	std::cout << "Setter has been called" << std::endl;
	this->_nb = raw;
	return ;
}
