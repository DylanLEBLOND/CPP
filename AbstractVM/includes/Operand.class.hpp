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

	static const int _int8_precision = 3;
	static const std::string _int8_min = "-128";
	static const std::string _int8_max = "127";

	static const int _int16_precision = 4;
	static const std::string _int16_min = "-32768";
	static const std::string _int16_max = "32767";

	static const int _int32_precision = 5;
	static const std::string _int32_min = "-2147483648";
	static const std::string _int32_max = "2147483647";

	static const int _float_precision = 7;
	static const std::string _float_min = "-3.40282e+38";
	static const std::string _float_max = "3.40282e+38";

	static const int _double_precision = 15;
	static const std::string _double_min = "-1.79769e+308";
	static const std::string _double_max = "1.79769e+308";

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
