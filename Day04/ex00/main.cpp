// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/20 15:53:17 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/20 22:59:11 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Sorcerer.hpp"

class	Adc : public Victim
{
public:

    Adc(std::string const name);
    Adc(Adc const &copy);
    ~Adc(void);

    Adc    &operator=(Adc const &copy);

    void    getPolymorphed(void) const;
};

Adc::Adc(std::string const newname) : Victim(newname)
{
	std::cout << "A wild adc is farming bot" << std::endl;
    return;
}

Adc::Adc(Adc const &copy): Victim(copy)
{
	std::cout << "A wild adc is farming bot" << std::endl;
    return ;
}

Adc::~Adc(void)
{
	std::cout << "You have been slain (" << this->name << " dead face)" << std::endl;
    return ;
}

Adc        &Adc::operator=(Adc const &copy)
{
    this->name = copy.getName();
    return *this;
}

void    Adc::getPolymorphed(void) const
{
	std::cout << this->name << " has been slain by an Assassin!" << std::endl;
}

class   Akali : public Sorcerer
{

public:

    Akali(std::string const name, std::string const title);
    Akali(Akali const &copy);
    ~Akali(void);

    Akali    &operator=(Akali const &copy);

    void    polymorph(Adc const &cait) const;

};

Akali::Akali(std::string const newname, std::string const newtitle): Sorcerer(newname, newtitle)
{
	std::cout << "I suggest you run... I want to savor this." << std::endl;
    return ;
}

Akali::Akali(Akali const &copy): Sorcerer(copy)
{
	std::cout << "I suggest you run... I want to savor this." << std::endl;
    return ;
}

Akali::~Akali(void)
{
	std::cout << "SHUTDOWN (Bounty: 500G)" << std::endl;
    return;
}

Akali        &Akali::operator=(Akali const &copy)
{
    this->name = copy.getName();
    this->title = copy.getTitle();
    return *this;
}

void    Akali::polymorph(Adc const &cait) const
{
    cait.getPolymorphed();
    return ;
}

int		main(void)
{
	Sorcerer	s("Dylan", "Suprem Mage");

	s.introduce();

	Victim		c("Teemo");

	c.introduce();

	s.polymorph(c);

	Peon	e("Bambi");

	std::cout << e;

	s.polymorph(e);

	Akali	mars("Akali", "Legendary");

	std::cout << mars;

	Adc		cait("Shaco");

	cait.introduce();

	mars.polymorph(cait);
	return 0;
}
