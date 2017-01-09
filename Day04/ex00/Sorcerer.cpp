// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Sorcerer.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/19 17:03:14 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/20 22:47:53 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

# include "Sorcerer.hpp"

//Constructors, Destructor

Sorcerer::Sorcerer(void) { return ; }

Sorcerer::Sorcerer(std::string const newname, std::string const newtitle):
	name(newname), title(newtitle)
{
	std::cout << this->name << ", " << this->title << ", is born !" << std::endl;
	return ;
}

Sorcerer::Sorcerer(Sorcerer const &copy)
{
	*this = copy;
	std::cout << this->name << ", " << this->title << ", is born !" << std::endl;
}

Sorcerer::~Sorcerer(void)
{
	std::cout << this->name << ", " << this->title << ", is dead.";
	std::cout << " Consequences will never be the same !" << std::endl;
	return ;
}

//Asignation overload

Sorcerer		&Sorcerer::operator=(Sorcerer const &copy)
{
	this->name = copy.getName();
	this->title = copy.getTitle();
	return *this;
}

std::ostream	&operator<<(std::ostream &o, Sorcerer const &s)
{
	o << "I'm " << s.getName() << ", " << s.getTitle();
	o << ", and I like ponies !" << std::endl;
	return o;
}

//Functions

void	Sorcerer::introduce(void) const
{
	std::cout << *this;
	return ;
}

void	Sorcerer::polymorph(Victim const &teemo) const
{
	teemo.getPolymorphed();
	return ;
}

void	Sorcerer::polymorph(Peon const &teemo) const
{
	teemo.getPolymorphed();
	return ;
}

//Accessors

std::string		Sorcerer::getName(void) const
{
	return this->name;
}

std::string		Sorcerer::getTitle(void) const
{
	return this->title;
}

void			Sorcerer::setName(std::string const newname)
{
	this->name = newname;
}

void			Sorcerer::setTitle(std::string const newtitle)
{
	this->title = newtitle;
}
