// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/24 22:34:17 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/24 22:41:58 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <cstdlib>
#include <ctime>

struct Data
{
	std::string s1;
	int		n;
	std::string s2;
};

static void	 *serialize(void)
{
	char	rdm[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char	 c;
	std::string s = "";

	for (c = 0; c < 8; c++)
		s.push_back(rdm[rand() % static_cast<int>(sizeof(rdm) - 1)]);

	for (c = 0; c < 8; c++)
		s.push_back(rdm[rand() % 10]); //:D

	for (c = 0; c < 8; c++)
		s.push_back(rdm[rand() % static_cast<int>(sizeof(rdm) - 1)]);

	return reinterpret_cast<void *>(const_cast<char *>(s.c_str()));
}

static Data *deserialize(void *raw)
{
	Data *data = new Data;

	data->s1 = reinterpret_cast<char *>(raw);

	data->s2 = data->s1.substr(16);
	data->n = atoi(data->s1.substr(8, 8).c_str());
	data->s1 = data->s1.substr(0, 8);

	return data;
}

int	main(void)
{
	srand(static_cast<unsigned int>(time(NULL)));
	Data *data = deserialize(serialize());

	std::cout << data->s1 << std::endl
				<< data->n << std::endl
				<< data->s2 << std::endl;

	return (0);
}
