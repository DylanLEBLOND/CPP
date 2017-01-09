// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   whatever.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <dle-blon@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/25 05:05:48 by dle-blon          #+#    #+#             //
//   Updated: 2015/06/25 18:49:31 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>

template < typename T >
void	swap(T &a, T &b)
{
	T c = a;
	a = b;
	b = c;
	return;
}

template < typename U >
U const	min(U &a, U &b)
{
	return (a < b ? a : b);
}


template < typename V >
V const max(V &a, V &b)
{
    return (a > b ? a : b);
}

int main( void )
{
	int a(2);
	int b(3);

	std::cout << "Before Swap : a = " << a << ", b = " << b << std::endl;
	::swap<int>(a, b);
	std::cout << "After Swap : a = " << a << ", b = " << b << std::endl;

	std::cout << "min( a, b ) = " << ::min<int>( a, b ) << std::endl;
	std::cout << "max( a, b ) = " << ::max<int>( a, b ) << std::endl;

	std::string c = "chaine1";
	std::string d = "chaine2";

	std::cout << "Before Swap : c = " << c << ", d = " << d << std::endl;
	::swap<std::string>(c, d);
	std::cout << "After Swap : c = " << c << ", d = " << d << std::endl;

	std::cout << "min( c, d ) = " << ::min<std::string>( c, d ) << std::endl;
	std::cout << "max( c, d ) = " << ::max<std::string>( c, d ) << std::endl;
 
	float e = 42.42f;
    float f = 21.21f;

	std::cout << "Before Swap : e = " << e << ", f = " << f << std::endl;
    ::swap<float>(e, f);
	std::cout << "After Swap : e = " << e << ", f = " << f << std::endl;

	std::cout << "min( e, f ) = " << ::min<float>( e, f ) << std::endl;
	std::cout << "max( e, f ) = " << ::max<float>( e, f ) << std::endl;

	return 0;
}
