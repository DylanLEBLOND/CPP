// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   PresidentialPardonForm.cpp                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/23 17:48:18 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/23 23:12:06 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "PresidentialPardonForm.hpp"

//Constructors And Destructor

PresidentialPardonForm::PresidentialPardonForm(std::string const target):
	Form("PresidentialPardonForm", 25, 5), _target(target)
{
	return ;
} 

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const &copy):
	Form(copy), _target(copy.getTarget())
{
	return ;
}

PresidentialPardonForm::~PresidentialPardonForm(void)
{
	return ;
}

//Operators OverLoad

PresidentialPardonForm	&PresidentialPardonForm::operator=(PresidentialPardonForm const &copy)
{
	Form::operator=(copy);
	this->_target = copy.getTarget();
	return *this;
}

//Getters

std::string		PresidentialPardonForm::getTarget(void) const
{
	return this->_target;
}

//Functions

bool			PresidentialPardonForm::execute(Bureaucrat const &executor) const
{
	if (!this->getSigned())
		throw Form::GradeTooLowException("This Form is not Signed");
	if (executor.getGrade() > this->getexecGrade())
		throw Form::GradeTooLowException("Your Grade is Too Low to Exec this Form");
	std::cout << this->_target << " has been pardoned by Zafod Beeblebrox." << std::endl;
	return true;
}
