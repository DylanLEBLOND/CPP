// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/23 22:58:04 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/23 23:39:16 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "Intern.hpp"

int	main(void)
{
    srand(static_cast<unsigned int>(time(NULL)));
	std::cout << "PART 00" << std::endl;
	// -------------------PART 00------------------------------ //
	Bureaucrat b1("b1", 5);
	Bureaucrat b2("b2", 147);

	try
	{
		Bureaucrat *b3 = new Bureaucrat("b3", 1000);
		delete b3;
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	for (int i = 0; i < 8; i++)
	{
		try
		{
			b1.upgrade();
			b2.downgrade();
		}
		catch (std::exception &e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}
		std::cout << b1;
		std::cout << b2;
	}



//PART1 is now broken, since Form class became abstract

    
	std::cout << std::endl << "PART 02" << std::endl;
	// -------------------PART 02------------------------------ //
	PresidentialPardonForm f1("target1");
	RobotomyRequestForm f2("target2");
	ShrubberyCreationForm f3("IsNotStrawberry");

	std::cout << f1;
	std::cout << f2;
	std::cout << f3;

	try
	{
		b1.signForm(f1);
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	std::cout << f1;

	try
	{
		b2.signForm(f1);
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	std::cout << f1;

	try
	{
		b1.signForm(f2);
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	std::cout << f2;

	try
	{
		b2.signForm(f2);
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	std::cout << f2;

	try
	{
		b1.signForm(f3);
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	std::cout << f3;

	try
	{
		b2.signForm(f3);
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	std::cout << f3;

	try
	{
		b2.signForm(f2);
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	std::cout << f2;


    try
    {
        b2.executeForm(f1);
        b2.executeForm(f2);
        b2.executeForm(f3);
    }
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	std::cout << f1;
	std::cout << f2;
	std::cout << f3;

    b1.executeForm(f1);
    b1.executeForm(f2);
    b1.executeForm(f3);

	std::cout << std::endl << "PART 03" << std::endl;
	// -------------------PART 03------------------------------ //
    Intern  someRandomIntern;
    Form*   rrf1;
    Form*   rrf2;
    Form*   rrf3;
    
    rrf1 = someRandomIntern.makeForm("robotomy request", "Bender");
    rrf2 = someRandomIntern.makeForm("presidential pardon", "Bender");
    rrf3 = someRandomIntern.makeForm("shrubbery creation", "Bender");

	std::cout << *rrf1;
	std::cout << *rrf2;
	std::cout << *rrf3; 
	return (0);
}
