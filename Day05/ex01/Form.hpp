// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Form.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/22 23:57:57 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/23 22:05:29 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FORM_HPP
# define FORM_HPP

# include <iostream>
# include <stdexcept>
# include "Bureaucrat.hpp"

class Form
{
private:
	int		 const		_signGrade;
	int		 const		_execGrade;
	std::string const	_name;
	bool				_signed;
	Form(void);

public:
	Form(std::string const name, int const signGrade, int const execGrade);
	Form(Form const &copy);
	~Form(void);
	Form	&operator=(Form const &copy);

	std::string		getName(void) const;
	int				getsignGrade(void) const;
	int				getexecGrade(void) const;
	bool			getSigned(void) const;
	bool			beSigned(Bureaucrat const &b);

	class GradeTooLowException : public std::exception
	{
	public:

		std::string msg;

		GradeTooLowException(char const *message) throw();
		GradeTooLowException(GradeTooLowException const &copy) throw();
		virtual ~GradeTooLowException(void) throw();
		GradeTooLowException	&operator=(GradeTooLowException const &copy);

		virtual char const *what(void) const throw();
	};

	class GradeTooHighException : public std::exception
	{
	public:

		std::string msg;

		GradeTooHighException(char const *message) throw();
		GradeTooHighException(GradeTooHighException const &copy) throw();
		virtual ~GradeTooHighException(void) throw();
		GradeTooHighException    &operator=(GradeTooHighException const &copy);

		virtual char const *what(void) const throw();
	};
};

std::ostream	&operator<<(std::ostream &o, Form const &b);

#endif
