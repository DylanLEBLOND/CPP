// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Operand.class.hpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/12/15 16:19:09 by dle-blon          #+#    #+#             //
//   Updated: 2016/12/15 16:56:32 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef OPERAND_CLASS_HPP
# define OPERAND_CLASS_HPP

#include "IOperand.class.hpp"

class Operand : public IOperand
{

private:

	eOperandType _type;
	int _precision;
	std::string _value;

public:

	Operand(eOperandType type, std::string value);
	Operand(Operand const &src);
	~Operand(void);
	Operand	&operator=(Operand const &src);

	int getPrecision(void) const;
	eOperandType getType(void) const;

	std::string const &toString(void) const;

	IOperand const *operator+(IOperand const &rhs) const;
	IOperand const *operator-(IOperand const &rhs) const;
	IOperand const *operator*(IOperand const &rhs) const;
	IOperand const *operator/(IOperand const &rhs) const;
	IOperand const *operator%(IOperand const &rhs) const;
};

#endif
