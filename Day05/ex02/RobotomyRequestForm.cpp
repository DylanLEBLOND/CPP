// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   RobotomyRequestForm.cpp                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/23 17:46:56 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/23 23:10:50 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "RobotomyRequestForm.hpp"

//Constructors and Destructor

RobotomyRequestForm::RobotomyRequestForm(std::string const target):
	Form("RobotomyRequestForm", 72, 45), _target(target)
{
	return ;
} 

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const &copy):
	Form(copy), _target(copy.getTarget())
{
	return ;
}

RobotomyRequestForm::~RobotomyRequestForm(void)
{
	return ;
}

//Operators Overload

RobotomyRequestForm &RobotomyRequestForm::operator=(RobotomyRequestForm const &copy)
{
	Form::operator=(copy);
	this->_target = copy.getTarget();

	return *this;
}

//Getter

std::string	RobotomyRequestForm::getTarget(void) const
{
	return this->_target;
}

//Function

bool		RobotomyRequestForm::execute(Bureaucrat const &executor) const
{
    if (!this->getSigned())
        throw ("This Form is not Signed");
    if (executor.getGrade() > this->getexecGrade())
        throw Form::GradeTooLowException("Your Grade is Too Low to Exec this Form");
	std::cout << "* drill noise * " << std::endl;
	if (rand() % 2)
		std::cout << this->_target << " was successfully robotomized." << std::endl;
	else
		std::cout << "Robotomy failed to " << this->_target << "." << std::endl;
    return true;
}
