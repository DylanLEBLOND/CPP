// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Fixed.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/18 15:40:37 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/18 23:38:48 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Fixed.hpp"

//Static

int	const	Fixed::_nb_ft = 8;

//Constructors && Destructor

Fixed::Fixed(void) : _nb(0)
{
	std::cout << "A Fixed Point Number has been created with the default constructor" << std::endl;
	return ;
}

Fixed::Fixed(Fixed const &src) : _nb(src.getRawBits())
{
	std::cout << "A Fixed Point Number has been created with the copy constructor" << std::endl;
	return ;
}

Fixed::~Fixed(void)
{
	std::cout << "Destructor has been called" << std::endl;
	return ;
}

//Assignation Operator overload

Fixed	&Fixed::operator=(Fixed const &src)
{
	std::cout << "Assignation overload has been called." << std::endl;
	this->_nb = src.getRawBits();
	return *this;
}

//Get And Set

int		Fixed::getRawBits(void) const
{
	std::cout << "Getter has been called" << std::endl;
	return this->_nb;
}

void	Fixed::setRawBits(int const raw)
{
	std::cout << "Setter has been called" << std::endl;
	this->_nb = raw;
	return ;
}
