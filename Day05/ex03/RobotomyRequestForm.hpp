// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   RobotomyRequestForm.hpp                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/23 17:46:07 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/23 22:50:21 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ROBOTOMYREQUESTFORM_HPP
# define ROBOTOMYREQUESTFORM_HPP

# include "Form.hpp"

class RobotomyRequestForm : public Form
{
private:
	std::string	_target;

public:
	RobotomyRequestForm(std::string const target);
	RobotomyRequestForm(RobotomyRequestForm const &copy);
	~RobotomyRequestForm(void);
	RobotomyRequestForm &operator=(RobotomyRequestForm const &copy);

	bool			execute(Bureaucrat const &executor) const;
	std::string		getTarget(void) const;
};

#endif
