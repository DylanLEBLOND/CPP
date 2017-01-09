// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Peon.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/20 18:29:27 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/20 19:07:48 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

# include "Sorcerer.hpp"

//Constructors, Destructor

Peon::Peon(std::string const newname) : Victim(newname)
{
	std::cout << "Zog zog." << std::endl;
	return;
}

Peon::Peon(Peon const &copy): Victim(copy)
{
	std::cout << "Zog zog." << std::endl;
	return ;
}

Peon::~Peon(void)
{
	std::cout << "Bleuark..." << std::endl;
	return ;
}

//Asignation overload

Peon		&Peon::operator=(Peon const &copy)
{
	this->name = copy.getName();
	return *this;
}

//functionm

void	Peon::getPolymorphed(void) const
{
	std::cout << this->name << " has been turned into a pink pony !" << std::endl;
}
