// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/22 23:03:56 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/23 22:04:41 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Form.hpp"

int		main(void)
{

//Bureaucrat

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

//Form

	Form *f0 = new Form("Got CPP Piscine", 7, 6);
	Form *f1 = new Form("Beat Math", 3, 3);
	Form *f2 = new Form("Go Eat", 140, 150);
	Form *f3;
	Form *f4;
	Form *f5;
	Form *f6;

	try
    {
		f3 = new Form("Work", 0, 15);
    }
    catch (std::exception const &err)
    {
		std::cerr << err.what() << std::endl;
        delete f3;
    }
    try
    {
        f4 = new Form("Week", 151, 15);
    }
    catch (std::exception const &err)
    {
		std::cerr << err.what() << std::endl;
        delete f4;
    }

	try
	{
		f5 = new Form("Waak", 15, 0);
	}
	catch (std::exception const &err)
	{
		std::cerr << err.what() << std::endl;
		delete f5;
	}
    try
    {
        f6 = new Form("Wuuk", 15, 151);
    }
    catch (std::exception const &err)
    {
		std::cerr << err.what() << std::endl;
        delete f6;
    }
	
	std::cout << *f0 << *f1 << *f2;

	b->signForm(*f0);
	a->signForm(*f1);
	c->signForm(*f2);

	delete a;
	delete b;
	delete c;
	delete f1;
	return 0;
}
