// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Form.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/22 23:58:01 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/23 22:02:49 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Bureaucrat.hpp"
#include "Form.hpp"

//Constructors and Destructors

Form::Form(void):
	_signGrade(0), _execGrade(0), _name("Poney"), _signed(false)

{ return ; }

Form::Form(std::string const name, int const signGrade, int const execGrade) :
	_signGrade(signGrade), _execGrade(execGrade), _name(name), _signed(false)
{
	if (this->_execGrade > 150)
		throw Form::GradeTooLowException("Exec Grade Too Low");
	if (this->_execGrade < 1)
		throw Form::GradeTooHighException("Exec Grade Too High");
	if (this->_signGrade > 150)
		throw Form::GradeTooLowException("Sign Grade Too Low");
	if (this->_signGrade < 1)
		throw Form::GradeTooHighException("Sign Grade Too High");
	return ;
}

Form::Form(Form const &copy) : 
	_signGrade(copy.getsignGrade()), _execGrade(copy.getexecGrade()),
	_name(copy.getName()), _signed(copy.getSigned())
{
	return ;
}

Form::~Form(void)
{
	return ;
}

//Operators

Form		&Form::operator=(Form const &copy)
{
	this->_signed = copy.getSigned();
	return *this;
}

std::ostream	&operator<<(std::ostream &o, Form const &b)
{
	o << "Form name : " << b.getName() << " | is signed : " << b.getSigned();
	o << " | required grade to sign it : " << b.getsignGrade() << " | ";
	o << " required grade to execute it : " << b.getexecGrade() << std::endl;
	return o;
}

//Accessors

std::string	Form::getName(void) const
{
	return this->_name;
}

int			Form::getsignGrade(void) const
{
	return this->_signGrade;
}

int         Form::getexecGrade(void) const
{
    return this->_execGrade;
}

bool		Form::getSigned(void) const
{
	return this->_signed;
}

//Exceptions

Form::GradeTooLowException::GradeTooLowException(char const *message) throw()
    : msg(message)
{
    return ;
}

Form::GradeTooLowException::GradeTooLowException(GradeTooLowException const &copy) throw()
    : exception(copy), msg(copy.msg)
{
    return ;
}

Form::GradeTooLowException::~GradeTooLowException(void) throw()
{
    return ;
}

Form::GradeTooLowException	&Form::GradeTooLowException::operator=(GradeTooLowException const &copy)
{
	exception::operator=(copy);
	this->msg = copy.msg;

	return *this;
}

char     const *Form::GradeTooLowException::what(void) const throw()
{
    return this->msg.c_str();
}

Form::GradeTooHighException::GradeTooHighException(char const *message) throw()
    :msg(message)
{
    return ;
}

Form::GradeTooHighException::GradeTooHighException(GradeTooHighException const &copy) throw()
    : exception(copy), msg(copy.msg)
{
    return ;
}

Form::GradeTooHighException::~GradeTooHighException(void) throw()
{
    return ;
}

Form::GradeTooHighException  &Form::GradeTooHighException::operator=(GradeTooHighException const &copy)
{
	exception::operator=(copy);
    this->msg = copy.msg;

    return *this;
}

char     const *Form::GradeTooHighException::what(void) const throw()
{
    return this->msg.c_str();
}

//Functions

bool		Form::beSigned(Bureaucrat const &b)
{
	if (b.getGrade() <= this->_signGrade)
		return (this->_signed = true);
	else
		throw Form::GradeTooLowException("Your Grade is Too Low to Sign this Form");
}
