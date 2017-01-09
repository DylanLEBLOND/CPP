// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Victim.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/20 17:05:17 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/20 19:04:48 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

# include "Sorcerer.hpp"
# include "Victim.hpp"

//Constructors, Destructor

Victim::Victim(void) { return ; }


Victim::Victim(std::string const newname) : name(newname)
{
	std::cout << "Some random victim called " << this->name << " just popped !" << std::endl;
	return;
}

Victim::Victim(Victim const &copy)
{
	*this = copy;
	std::cout << "Some random victim called " << this->name << " just popped !" << std::endl;
	return ;
}

Victim::~Victim(void)
{
	std::cout << "Victim " << this->name << " just died for no apparent reason !" << std::endl;
	return ;
}

//Asignation overload

Victim		&Victim::operator=(Victim const &copy)
{
	this->name = copy.getName();
	return *this;
}

std::ostream	&operator<<(std::ostream &o, Victim const &vic)
{
	o << "I'm " << vic.getName() << ", and I like otters !" << std::endl;
	return o;
}

//Functions

void	Victim::introduce(void) const
{
	std::cout << *this;
	return ;
}

void	Victim::getPolymorphed(void) const
{
	std::cout << this->name << " has been turned into a cute little sheep !" << std::endl;
}

//Accessors

std::string		Victim::getName(void) const
{
	return this->name;
}

void			Victim::setName(std::string const newname)
{
	this->name = newname;
}
