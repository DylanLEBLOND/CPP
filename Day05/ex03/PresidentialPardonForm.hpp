// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   PresidentialPardonForm.hpp                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/23 17:48:15 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/23 22:51:43 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef PRESIDENTIALPARDONFORM_HPP
# define PRESIDENTIALPARDONFORM_HPP

# include "Form.hpp"

class PresidentialPardonForm : public Form
{
private:

	std::string	_target;

public:

	PresidentialPardonForm(std::string const target);
	PresidentialPardonForm(PresidentialPardonForm const &copy);
	virtual ~PresidentialPardonForm(void);
	PresidentialPardonForm	&operator=(PresidentialPardonForm const &copy);

	bool			execute(Bureaucrat const &executor) const;
	std::string		getTarget(void) const;
};

#endif
