// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Array.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/25 17:17:50 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/25 21:10:06 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <iostream>
# include <stdexcept>

template <typename T>
class Array
{
public:

private:
	T	*_tab;
	unsigned int _size;

public:
	Array<T>(void)
		{
			this->_tab = new T[0];
			return ;
		}
	Array<T>(unsigned int const size)
		{
			this->_tab = new T[size];
			this->_size = size;
			return ;
		}
	Array<T>(Array<T> const &copy)
		{
			*this = copy;
			return; 
		}
	~Array<T> (void)
		{
			delete [] this->_tab;
			return ;
		}

	Array<T> &operator=(Array<T> const &copy)
		{
			unsigned int i = 0;

			delete [] this->_tab;

			this->_tab = new T[copy.getSize()];
			this->_size = copy.getSize();

			while (i < this->_size)
			{
				this->_tab[i] = copy._tab[i];
				i++;
			}
			return *this;
		}
	T	&operator[](unsigned int size)
		{
			if (size < 0 || size >= this->_size)
				throw std::out_of_range("Out Of Range");
			return this->_tab[size];
		}
	T   &operator[](unsigned int const size) const
        {
            if (size < 0 || size >= this->_size)
                throw std::out_of_range("Out Of Range");
            return this->_tab[size];
        }
	unsigned int getSize(void) const
		{
			return this->_size;
		}
	T			*getTab(void) const
		{
			return this->_tab;
		}
};

#endif
