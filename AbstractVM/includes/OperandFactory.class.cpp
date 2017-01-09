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

OperandFactory::_pfuncArray = NULL;		//Default Value

/*
** Constructors
*/
OperandFactory::OperandFactory(void)
{
	this->_pfuncArray = new t_pfunc [5];

	this->_pfuncArray[Int8] = &this->createInt8;
	this->_pfuncArray[Int16] = &this->createInt16;
	this->_pfuncArray[Int32] = &this->createInt32;
	this->_pfuncArray[Float] = &this->createFloat;
	this->_pfuncArray[Double] = &this->createDouble;
}

OperandFactory::OperandFactory(OperandFactory const &copy)
{
	*this = copy;
}

/*
** Destructor
*/
OperandFactory::~OperandFactory(void)
{
	delete [] this->_pfuncArray;
}

/*
** = Operator Overload
*/
OperandFactory		&OperandFactory::operator=(OperandFactoryconst &copy)
{
	return *this;
}

/*
** Private
*/
#if 0
IOperand const		*OperandFactory::createInt8(std::string const & value) const
{
	return &(new Operand(value, Int8));
}

IOperand const		*OperandFactory::createInt16(std::string const & value) const
{
	return &(new Operand(value, Int16));
}

IOperand const		*OperandFactory::createInt32(std::string const & value) const
{
	return &(new Operand(value, Int32));
}

IOperand const		*OperandFactory::createFloat(std::string const & value) const
{
	return &(new Operand(value, Float));
}

IOperand const		*OperandFactory::createDouble(std::string const & value) const
{
	return &(new Operand(value, Double));
}
#endif

/*
** Public
*/
#if 0
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

	if (this->_pfuncArray == NULL)
		return NULL;

	return this->_pfuncArray[type](value);
}
#endif

