// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IOperand.class.hpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/12/12 16:00:48 by dle-blon          #+#    #+#             //
//   Updated: 2016/12/15 16:18:00 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef IOPERAND_CLASS_HPP
# define IOPERAND_CLASS_HPP

enum eOperandType { Int8 = 0, Int16 = 1, Int32 = 2, Float = 3, Double = 4 };

class IOperand
{

public:
	
	virtual ~IOperand(void) {}

	virtual IOperand const *operator+(IOperand const &rhs) const = 0; // Sum
	virtual IOperand const *operator-(IOperand const &rhs) const = 0; // Difference
	virtual IOperand const *operator*(IOperand const &rhs) const = 0; // Product
	virtual IOperand const *operator/(IOperand const &rhs) const = 0; // Quotient
	virtual IOperand const *operator%(IOperand const &rhs) const = 0; // Modulo

	virtual int getPrecision(void) const = 0; // Precision of the type of the instance
	virtual eOperandType getType(void) const = 0; // Type of the instance

	virtual std::string const &toString(void) const = 0; // String representation of the instance

};

#endif
