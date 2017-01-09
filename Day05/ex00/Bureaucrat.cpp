// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Bureaucrat.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/22 22:50:04 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/23 18:52:56 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Bureaucrat.hpp"

//Constructors and Destructors

Bureaucrat::Bureaucrat(void){ return ; }

Bureaucrat::Bureaucrat(std::string const name, int const grade)
{
	this->_name = name;
	if (grade > 150)
		throw Bureaucrat::GradeTooLowException("Grade Too Low");
	else if (grade < 1)
		throw Bureaucrat::GradeTooHighException("Grade Too High");
	else
		this->_grade = grade;
	return ;
}

Bureaucrat::Bureaucrat(Bureaucrat const &copy)
{
	*this = copy;
	return ;
}

Bureaucrat::~Bureaucrat(void)
{
	return ;
}

//Operators

Bureaucrat		&Bureaucrat::operator=(Bureaucrat const &copy)
{
	this->_name = copy.getName();
	this->_grade = copy.getGrade();
	return *this;
}

std::ostream	&operator<<(std::ostream &o, Bureaucrat const &b)
{
	o << b.getName() << ", bureaucrat grade " << b.getGrade() << std::endl;
	return o;
}

//Accessors

std::string	Bureaucrat::getName(void) const
{
	return this->_name;
}

int			Bureaucrat::getGrade(void) const
{
	return this->_grade;
}

//Exceptions

Bureaucrat::GradeTooLowException::GradeTooLowException(char const *message) throw()
	:msg(message)
{
	return;
}

Bureaucrat::GradeTooLowException::GradeTooLowException(GradeTooLowException const &copy) throw()
    : exception(copy), msg(copy.msg)
{
    return;
}

Bureaucrat::GradeTooLowException::~GradeTooLowException(void) throw()
{
    return;
}

Bureaucrat::GradeTooLowException &Bureaucrat::GradeTooLowException::operator=(GradeTooLowException const &copy)
{
	exception::operator=(copy);
	this->msg = copy.msg;

	return *this;
}

char const *Bureaucrat::GradeTooLowException::what(void) const throw()
{
    return this->msg.c_str();
}

Bureaucrat::GradeTooHighException::GradeTooHighException(char const *message) throw()
    :msg(message)
{
    return;
}

Bureaucrat::GradeTooHighException::GradeTooHighException(GradeTooHighException const &copy) throw()
    : exception(copy), msg(copy.msg)
{
    return;
}

Bureaucrat::GradeTooHighException::~GradeTooHighException(void) throw()
{
    return;
}

Bureaucrat::GradeTooHighException &Bureaucrat::GradeTooHighException::operator=(GradeTooHighException const &copy)
{
	exception::operator=(copy);
    this->msg = copy.msg;

    return *this;
}

char const *Bureaucrat::GradeTooHighException::what(void) const throw()
{
    return this->msg.c_str();
}

//Functions

void		Bureaucrat::upgrade(void)
{
	if (this->_grade - 1 < 1)
		throw Bureaucrat::GradeTooHighException("Can't be Highest");
	else
		this->_grade--;
	return ;
}

void		Bureaucrat::downgrade(void)
{
	if (this->_grade + 1 > 150)
		throw Bureaucrat::GradeTooLowException("Can't be Lowest");
	else
		this->_grade++;
	return ;
}
