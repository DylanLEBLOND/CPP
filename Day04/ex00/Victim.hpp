// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Victim.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/20 16:56:08 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/20 19:03:14 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef VICTIM_HPP
# define VICTIM_HPP

class Victim
{

private:

	Victim(void);

protected:

	std::string name;

public:

	Victim(std::string const name);
	Victim(Victim const &copy);
	~Victim(void);

	Victim	&operator=(Victim const &copy);

	void	introduce(void) const;
	void	getPolymorphed(void) const;

	std::string	getName(void) const;
	void		setName(std::string const newname);

};

std::ostream	&operator<<(std::ostream &o, Victim const &vic);

#endif
