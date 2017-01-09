// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Intern.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/23 23:28:03 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/23 23:39:53 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef INTERN_HPP
# define INTERN_HPP

# include "ShrubberyCreationForm.hpp"
# include "RobotomyRequestForm.hpp"
# include "PresidentialPardonForm.hpp"

class Intern
{
public:

	Intern(void);
	Intern(Intern const &copy);
	~Intern(void);
	Intern &operator=(Intern const &copy);

	Form	*makeForm(std::string name, std::string target);
};

#endif
