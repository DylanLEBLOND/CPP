// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/23 17:32:24 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/23 22:50:12 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

# include "Form.hpp"
# include <fstream>

class ShrubberyCreationForm : public Form
{
private:
	std::string	_target;

public:
	ShrubberyCreationForm(std::string const target);
	ShrubberyCreationForm(ShrubberyCreationForm const &copy);
	~ShrubberyCreationForm(void);
	ShrubberyCreationForm &operator=(ShrubberyCreationForm const &copy);

	bool			execute(Bureaucrat const &executor) const;
	std::string		getTarget(void) const;
};

#endif
