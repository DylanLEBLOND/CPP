// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/22 23:03:56 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/23 19:26:09 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Bureaucrat.hpp"

int		main(void)
{
	Bureaucrat	*a = new Bureaucrat("Akali", 1);
	Bureaucrat  *b = new Bureaucrat("Zed", 50);
	Bureaucrat  *c = new Bureaucrat("Shaco", 150);
	Bureaucrat	*d;
	Bureaucrat	*e;

	try
	{
		d = new Bureaucrat("Dylan", 0);
	}
	catch (std::exception const &err)
	{
		std::cerr << err.what() << std::endl;
		delete d;
	}
	try
	{
		e = new Bureaucrat("Dylan", 151);
	}
	catch (std::exception const &err)
	{
		std::cerr << err.what() << std::endl;
		delete e;
	}

	std::cout << *a << *b << *c;

	b->upgrade();
	std::cout << *b;
	b->downgrade();
	std::cout << *b;

	try
	{
		a->upgrade();
	}
	catch (std::exception const &err)
	{
		std::cerr << err.what() << std::endl;
	}
	std::cout << *a;

	try
    {
        c->downgrade();
    }
    catch (std::exception const &err)
    {
		std::cerr << err.what() << std::endl;
    }
	std::cout << *c;
	delete a;
	delete b;
	delete c;
	return 0;
}
