// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Bureaucrat.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/22 22:49:33 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/23 18:53:17 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>
# include <stdexcept>

class Form;

class Bureaucrat
{

private:
	int			_grade;
	std::string	_name;
	Bureaucrat(void);

public:

	Bureaucrat(std::string const name, int const grade);
	Bureaucrat(Bureaucrat const	&copy);
	~Bureaucrat(void);
	Bureaucrat	&operator=(Bureaucrat const &copy);

	std::string	getName(void) const;
	int			getGrade(void) const;

	void		upgrade(void);
	void		downgrade(void);
	void		signForm(Form &form);

	class GradeTooLowException : public std::exception
	{
	public:

		std::string msg;

		GradeTooLowException(char const *message) throw();
		GradeTooLowException(GradeTooLowException const &copy) throw();
		virtual ~GradeTooLowException(void) throw();
		GradeTooLowException &operator=(GradeTooLowException const &copy);

		virtual char const *what(void) const throw();
	};

	class GradeTooHighException : public std::exception
	{
	public:

		std::string msg;

		GradeTooHighException(char const *message) throw();
		GradeTooHighException(GradeTooHighException const &copy) throw();
		virtual ~GradeTooHighException(void) throw();
		GradeTooHighException &operator=(GradeTooHighException const &copy);

		virtual char const *what(void) const throw();
	};

};

std::ostream	&operator<<(std::ostream &o, Bureaucrat const &b);

#endif
