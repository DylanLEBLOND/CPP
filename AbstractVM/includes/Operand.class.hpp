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

/*
 * Personals Includes
 */
#include "IOperand.class.hpp"
#include "Exceptions.h"

/*
 * System Includes
 */
#include <string>		// std::string
#include <cstdint>		// limits INT8 INT16 INT32
#include <cfloat>		// limits FLOAT DOUBLE

/*
 * PRECISION:
 * It's the number of bytes of type.
 * We use those values to defines the hierarchy of thes differents types
 */
#define INT8_PRECISION		1
#define INT16_PRECISION		2
#define INT32_PRECISION		4
#define FLOAT_PRECISION		5		// It's actually 4 like INT32 but with the mantisse we have a precision far bigger than INT32
#define DOUBLE_PRECISION	8

class Operand : public IOperand
{

private:

	eOperandType _type;
	unsigned int _precision;
	template <typename T>
	T _value;
	std::string _value_str;

	Operand(void);

	bool					stringIsInteger (std::string const &str) const;
	bool					stringIsFloating (std::string const &str) const;

	signed char				getValueInt8 (std::string const &str) const;
	signed short int		getValueInt16 (std::string const &str) const;
	signed long				getValueInt32 (std::string const &str) const;
	float					getValueFloat (std::string const &str) const;
	double					getValueDouble (std::string const &str) const;

public:

	Operand(eOperandType type, std::string const &value_str);
	Operand(IOperand const &src);
	Operand(Operand const &src);
	~Operand(void);
	Operand					&operator=(Operand const &src);

	unsigned int			getPrecision(void) const;
	eOperandType			getType(void) const;
	template <typename T>
	T						getValue(void) const;

	std::string const		&toString(void) const;

	template <typename T>
	IOperand const			*operator+(IOperand const &rhs) const;
	template <typename T>
	IOperand const			*operator-(IOperand const &rhs) const;
	template <typename T>
	IOperand const			*operator*(IOperand const &rhs) const;
	template <typename T>
	IOperand const			*operator/(IOperand const &rhs) const;
	template <typename T>
	IOperand const			*operator%(IOperand const &rhs) const;
};

#endif /* OPERAND_CLASS_HPP */
