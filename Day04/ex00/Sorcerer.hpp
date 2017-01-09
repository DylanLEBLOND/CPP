// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Sorcerer.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/19 17:03:23 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/20 19:06:17 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SORCERER_HPP
# define SORCERER_HPP

# include <iostream>
# include "Victim.hpp"
# include "Peon.hpp"

class Sorcerer
{

private:

	Sorcerer(void);

protected:

	std::string name;
	std::string title;

public:

	Sorcerer(std::string const name, std::string const title);
	Sorcerer(Sorcerer const &copy);
	~Sorcerer(void);

	Sorcerer	&operator=(Sorcerer const &copy);

	void	introduce(void) const;
	void	polymorph(Victim const &teemo) const;
	void	polymorph(Peon const &teemo) const;

	std::string	getName(void) const;
	std::string	getTitle(void) const;
	void		setName(std::string const newname);
	void		setTitle(std::string const newtitle);
};

std::ostream	&operator<<(std::ostream &o, Sorcerer const &s);

#endif
