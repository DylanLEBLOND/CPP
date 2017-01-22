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
#include <IOperand.class.hpp>
#include <Exceptions.hpp>
#include <common.hpp>

/*
 * System Includes
 */
#include <string>		// std::string
#include <cstdint>		// limits INT8 INT16 INT32
#include <cfloat>		// limits FLOAT DOUBLE
#include <cmath>		// fabs isnan
#include <iomanip>		// setprecision
#include <sstream>		// stringstream

/*
 * PRECISION:
 * It's the number of bytes of type.
 * We use those values to defines the hierarchy of thes differents types
 */
#define INT8_PRECISION				1
#define INT16_PRECISION				2
#define INT32_PRECISION				4
#define FLOAT_PRECISION				5		// It's actually 4 like INT32 but with the mantisse we have a precision far bigger than INT32
#define DOUBLE_PRECISION			8

#define FLOATING_POINT_DIGITS		5		//The number of digits after the coma

class Operand : public IOperand
{

private:

	eOperandType _type;
	int _precision;
	std::string _value_str;

	Operand(void);

	bool					stringIsInteger (std::string const &str) const;
	bool					stringIsFloating (std::string const &str) const;

	signed long				getValueInteger (std::string const &str, signed long min, signed long max) const;
	double					getValueFloating (std::string const &str, double min, double max, bool isFloat) const;

	std::string				addInteger (std::string const &lhs, std::string const &rhs, signed long min, signed long max) const;
	std::string				addFloating (std::string const &lhs, std::string const &rhs, double min, double max, bool isFloat) const;

	std::string				subInteger (std::string const &lhs, std::string const &rhs, signed long min, signed long max) const;
	std::string				subFloating (std::string const &lhs, std::string const &rhs, double min, double max, bool isFloat) const;

	std::string				mulInteger (std::string const &lhs, std::string const &rhs, signed long min, signed long max) const;
	std::string				mulFloating (std::string const &lhs, std::string const &rhs, double min, double max, bool isFloat) const;

	std::string				divInteger (std::string const &lhs, std::string const &rhs, signed long min) const;
	std::string				divFloating (std::string const &lhs, std::string const &rhs, double min, double max, bool isFloat) const;

	std::string				modulo (std::string const &lhs, std::string const &rhs, signed long min) const;


public:

	Operand(eOperandType type, std::string const &value_str);
	Operand(IOperand const &src);
	Operand(Operand const &src);
	~Operand(void);
	Operand					&operator=(Operand const &src);
	Operand					&operator=(IOperand const &src);

	int						getPrecision(void) const;
	eOperandType			getType(void) const;

	std::string const		&toString(void) const;		// return _value_str

	IOperand const			*operator+(IOperand const &rhs) const;
	IOperand const			*operator-(IOperand const &rhs) const;
	IOperand const			*operator*(IOperand const &rhs) const;
	IOperand const			*operator/(IOperand const &rhs) const;
	IOperand const			*operator%(IOperand const &rhs) const;
};

#endif /* OPERAND_CLASS_HPP */
