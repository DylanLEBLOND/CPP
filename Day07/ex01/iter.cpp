// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   iter.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/25 05:31:40 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/25 20:39:52 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>

template <typename T>
void	iter(T *tab, unsigned int const size, void (*f)(T const &))
{
	unsigned int	i = 0;

	while (i < size)
	{
		f(tab[i]);
		i++;
	}
	return ;
}

template <typename T>
void	putall(T const &nb)
{
	std::cout << nb << std::endl;;
	return ;
}

int		main(void)
{
	int		tab[] = {5, 26, 8};
	
	::iter(tab, 3, putall<int>);
	std::cout << std::endl;
	
	char	tib[] = {'D', 'y', 'l', 'a', 'n'};
	
	::iter(tib, 5, putall<char>);
	std::cout << std::endl;

	std::string	tob[] = {"Shaco", "Sucks", "As", "Fuck"};

	::iter(tob, 4, putall<std::string>);
	std::cout << std::endl;
	return (0);
}
