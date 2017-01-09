// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Intern.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/23 23:28:05 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/23 23:40:02 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Intern.hpp"

Intern::Intern(void)
{
	return ;
}

Intern::Intern(Intern const &copy)
{
	*this = copy;
	return ;
}

Intern::~Intern(void)
{
	return ;
}

Intern &Intern::operator=(Intern const &copy)
{
	static_cast<void>(copy);
	return *this;
}

Form    *Intern::makeForm(std::string name, std::string target)
{
	Form *a;

	if (name == "robotomy request")
		a = new RobotomyRequestForm(target);
	else if (name == "shrubbery creation")
		a = new ShrubberyCreationForm(target);
	else if (name == "presidential pardon")
		a = new PresidentialPardonForm(target);
	else
		a = NULL;

	if (a)
		std::cout << "Intern creates " << a->getName() << "." << std::endl;
    else
		std::cout << "Intern creatation failed." << std::endl;
	return a;
}
