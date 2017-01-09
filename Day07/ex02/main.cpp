// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/25 17:48:29 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/25 21:09:47 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Array.hpp"

int		main(void)
{
	unsigned int i = 0;
	Array<int> t(5);
	int tab[5] = {21, 42, 84, 168, 336};

	std::cout << "size = " << t.getSize() << std::endl;
	while (i < t.getSize())
	{
		t[i] = tab[i];
		std::cout << t[i] << std::endl;
		i++;
	}
	try
	{
		int	a = t[10];
		std::cout << a << std::endl;
	}
	catch (std::exception &err1)
	{
		std::cerr << err1.what() << std::endl;
	}

//String
	std::cout << "************************************************" << std::endl;

	unsigned int j = 0;
    Array<std::string> u(10);
	std::string mess[10] = {"Akali", "will", "beats", "your", "ass", "and", "win", "this", "game", "hahaha"};

	std::cout << "size = " << u.getSize() << std::endl;
    while (j < u.getSize())
	{
		u[j] = mess[j];
		std::cout << u[j];
		if (j < u.getSize() - 1)
			std::cout << " ";
		j++;
	}
	std::cout <<std::endl;
    try
    {
		std::string b = u[15];
		std::cout << b << std::endl;
    }
    catch (std::exception &err2)
    {
		std::cerr << err2.what() << std::endl;
    }
	return (0);
}
