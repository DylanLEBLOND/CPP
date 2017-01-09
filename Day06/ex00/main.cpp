// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/24 16:58:13 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/24 22:31:47 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Convert.hpp"

int		main(int ac, char **av)
{
	char	c;
	int		i;
	float	f;
	double	d;

	if (ac > 2)
		std::cout << "Too Much Parameters" << std::endl;
	else if (ac < 2)
		std::cout << "Not Enough Parameters" << std::endl;
	else
	{
		Convert conv(av[1]);

		std::cout << std::fixed;
		std::cout << std::setprecision(1);
		if (conv.getValue() == "inf" || conv.getValue() == "inff")
		{
			std::cout << "char: Impossible" << std::endl;
			std::cout << "int: Impossible" << std::endl;
			std::cout << "float: inff" << std::endl;
			std::cout << "double: inf" << std::endl;
		}
		else if (conv.getValue() == "-inf" || conv.getValue() == "-inff")
		{
			std::cout << "char: Impossible" << std::endl;
			std::cout << "int: Impossible" << std::endl;
			std::cout << "float: -inf" << std::endl;
			std::cout << "double: -inf" << std::endl;
		}
		else if (conv.getValue() == "nan")
		{
			std::cout << "char: Impossible" << std::endl;
			std::cout << "int: Impossible" << std::endl;
			std::cout << "float: nanf" << std::endl;
			std::cout << "double: nan" << std::endl;
		}
		else if (conv.getType() == 'c')
		{
			c = static_cast<char>(conv.getValue().c_str()[1]);
			i = static_cast<int>(c);
			f = static_cast<float>(c);
			d = static_cast<double>(c);
			std::cout << "char: " << c << std::endl;
			std::cout << "int: " << i << std::endl;
			std::cout << "float: " << f << "f" << std::endl;
			std::cout << "double: " << d << std::endl;
		}
		else if (conv.getType() == 'i')
		{
			try
			{
				i = std::stoi(conv.getValue().c_str());
			}
			catch (std::exception const &err)
			{
				conv.getOver();
				return 0;
			}
			if (i > CHAR_MAX || i < CHAR_MIN)
				std::cout << "char: Impossible" << std::endl;
			else if (i < 32 || i == 127)
				std::cout << "char: Non displayable" << std::endl;
			else
			{
				c = static_cast<char>(i);
				std::cout << "char: '" << c << "'" << std::endl;
			}
			f = static_cast<float>(i);
			d = static_cast<double>(i);
			std::cout << "int: " << i << std::endl;
			std::cout << "float: " << f << "f" << std::endl;
			std::cout << "double: " << d << std::endl;
		}
		else if (conv.getType() == 'f')
		{
			try
			{
				f = std::stof(conv.getValue().c_str());
			}
			catch (std::exception const &err)
			{
				conv.getOver();
				return (0);
			}
			if (f > static_cast<float>(CHAR_MAX) || f < static_cast<float>(CHAR_MIN))
				std::cout << "char: Impossible" << std::endl;
			else if (static_cast<int>(f) < 32 || static_cast<int>(f) == 127)
				std::cout << "char: Non displayable" << std::endl;
			else
				std::cout << "char: '" << (c = static_cast<char>(f)) << "'" << std::endl;
			if (atol(av[1]) > static_cast<float>(INT_MAX) || atol(av[1]) < static_cast<float>(INT_MIN))
				std::cout << "int: Impossible" << std::endl;
			else
				std::cout << "int: " << (i = static_cast<int>(f)) << std::endl;
			d = static_cast<double>(f);
			std::cout << "float: " << f << "f" << std::endl;
			std::cout << "double: " << d << std::endl;
		}
		else
		{
			try
            {
                d = std::stod(conv.getValue().c_str());
            }
            catch (std::exception const &err)
            {
                conv.getOver();
                return (0);
            }
            if (d >= static_cast<double>(CHAR_MAX) || d < static_cast<double>(CHAR_MIN))
				std::cout << "char: Impossible" << std::endl;
            else if (static_cast<int>(d) < 32 || static_cast<int>(d) == 127)
				std::cout << "char: Non displayable" << std::endl;
            else
				std::cout << "char: '" << (c = static_cast<char>(d)) << "'" << std::endl;
            if (atol(av[1]) > static_cast<double>(INT_MAX) || atol(av[1]) < static_cast<double>(INT_MIN))
				std::cout << "int: Impossible" << std::endl;
            else
				std::cout << "int: " << (i = static_cast<int>(d)) << std::endl;
			if (d > static_cast<double>(FLT_MAX) || d < -1.0 * static_cast<double>(FLT_MAX))
				std::cout << "float: Impossible" << std::endl;
            else
				std::cout << "float: " << (f = static_cast<float>(d)) << "f" << std::endl;
			std::cout << "double: " << d << std::endl;
		}
	}
	return 0;
}
