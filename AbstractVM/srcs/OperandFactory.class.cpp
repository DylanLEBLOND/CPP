// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   OperandFactory.class.cpp                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/12/15 14:25:43 by dle-blon          #+#    #+#             //
//   Updated: 2016/12/15 16:29:34 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

//# include <OperandFactory.class.hpp>
# include "OperandFactory.class.hpp"

OperandFactory::_pfuncArray[] = { OperandFactory::createInt8,
								  OperandFactory::createInt16,
								  OperandFactory::createInt32,
								  OperandFactory::createFloat,
								  OperandFactory::createDouble };

/*
** Constructors
*/
OperandFactory::OperandFactory(void) {}

OperandFactory::OperandFactory(OperandFactory const &src) {}

/*
** Destructor
*/
OperandFactory::~OperandFactory(void) {}

/*
** Operator "=" Overload
*/
OperandFactory		&OperandFactory::operator=(OperandFactory const &src)
{
	return *this;
}

/*
** Private
*/
IOperand const		*OperandFactory::createInt8(std::string const & value) const
{
	return &(new Operand(Int8, value));
}

IOperand const		*OperandFactory::createInt16(std::string const & value) const
{
	return &(new Operand(Int16, value));
}

IOperand const		*OperandFactory::createInt32(std::string const & value) const
{
	return &(new Operand(Int32, value));
}

IOperand const		*OperandFactory::createFloat(std::string const & value) const
{
	return &(new Operand(Float, value));
}

IOperand const		*OperandFactory::createDouble(std::string const & value) const
{
	return &(new Operand(Double, value));
}

/*
** Public
*/
IOperand const		*OperandFactory::createOperand(eOperandType type, std::string const & value) const
{
	switch (type)
	{
		case Int8:
		case Int16:
		case Int32:
		case Float:
		case Double:
			break;
		default:
			return NULL;
	}

	return this->_pfuncArray[type](value);
}
