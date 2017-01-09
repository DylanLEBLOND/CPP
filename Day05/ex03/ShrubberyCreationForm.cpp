// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/23 17:35:23 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/23 23:21:49 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ShrubberyCreationForm.hpp"

//Constructors and Destructor

ShrubberyCreationForm::ShrubberyCreationForm(std::string const target):
	Form("ShrubberyCreationForm", 145, 137), _target(target)
{
	return ;
} 

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &copy):
	Form(copy), _target(copy.getTarget())
{
	return ;
}

ShrubberyCreationForm::~ShrubberyCreationForm(void)
{
	return ;
}

//Operator Overload

ShrubberyCreationForm &ShrubberyCreationForm::operator=(ShrubberyCreationForm const &copy)
{
	Form::operator=(copy);
	this->_target = copy.getTarget();

	return *this;
}

//Getter

std::string		ShrubberyCreationForm::getTarget(void) const
{
	return this->_target;
}

//Function

bool		ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
	std::string		name = this->_target + "_shrubbery";
	std::ofstream	out(name, std::ofstream::binary);

	if (!this->getSigned())
		throw Form::GradeTooLowException("This Form is not Signed");
	if (executor.getGrade() > this->getexecGrade())
		throw Form::GradeTooLowException("Your Grade is Too Low to Exec this Form");
	out.write("This is a Majestic Tree : \"-Y-\"\n", 33);
	out.close();
	return true;
}
