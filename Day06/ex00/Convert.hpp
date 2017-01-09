// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Convert.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/24 17:01:44 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/24 22:00:37 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CONVERT_HPP
# define CONVERT_HPP

# include <iostream>
# include <iomanip>
# include <climits>
# include <cfloat>
# include <string>

class Convert
{

private:
	std::string _value;

	Convert(void);

public:
	Convert(std::string const value);
	Convert(Convert const &copy);
	~Convert(void);
	Convert	&operator=(Convert const &copy);

	char	getType(void) const;
	void	getOver(void) const;
	bool	justChar(void) const;

	std::string	getValue(void) const;
};

#endif
