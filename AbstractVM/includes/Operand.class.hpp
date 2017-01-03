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
#include "OperandFactory.class.hpp"

class Operand : public IOperand
{

private:

	static const int _int8_precision = 1;		//The number of byte
	static const int _int16_precision = 2;
	static const int _int32_precision = 4;
	static const int _float_precision = 4;
	static const int _double_precision = 8;

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

#endif /* OPERAND_CLASS_HPP */
