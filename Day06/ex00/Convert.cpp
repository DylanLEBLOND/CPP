// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Convert.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/24 17:01:42 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/24 22:00:31 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Convert.hpp"

//Constructors and destructors

Convert::Convert(void) { return; }

Convert::Convert(std::string const value) : _value(value)
{
	return ;
}

Convert::Convert(Convert const &copy) : _value(copy.getValue())
{
	return ;
}

Convert::~Convert(void){ return ; }

Convert		&Convert::operator=(Convert const &copy)
{
	this->_value = copy.getValue();
	return *this;
}

//Getters

std::string	Convert::getValue(void) const
{
	return this->_value;
}

//functions

void		Convert::getOver(void) const
{
	std::cout << "char: Impossible" << std::endl;
	std::cout << "int: Impossible" << std::endl;
	std::cout << "float: Impossible" << std::endl;
	std::cout << "double: Impossible" << std::endl;
	return ;
}

char		Convert::getType(void) const
{
	int		v = 0;
	int		f = 0;
	unsigned int i = 0;

	if (this->justChar())
		return 'c';
	else
	{
		while (i < this->_value.length())
		{
			if (this->_value.c_str()[i] == '.')
				v = 1;
			else if (this->_value.c_str()[i] == 'f')
				f = 1;
			i++;
		}
		if (!v)
			return 'i';
		else if (f)
			return 'f';
	}
	return 'd';
}

bool		Convert::justChar(void) const
{
	int				c = 0;
	unsigned int	i = 0;

	while (i < this->_value.length())
	{
		if (this->_value.c_str()[i] == '\'')
			c = 1;
		i++;
	}
	if (c)
		return true;
	return false;
}
