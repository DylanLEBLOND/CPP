// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Peon.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/20 18:28:33 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/20 19:07:51 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef PEON_HPP
# define PEON_HPP

class Peon : public Victim
{

public:

	Peon(std::string const name);
	Peon(Peon const &copy);
	~Peon(void);

	Peon	&operator=(Peon const &copy);

	void	getPolymorphed(void) const;

};

#endif
