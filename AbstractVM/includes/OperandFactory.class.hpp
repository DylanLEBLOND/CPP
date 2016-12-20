// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   OperandFactory.class.hpp                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dle-blon <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/12/15 13:45:14 by dle-blon          #+#    #+#             //
//   Updated: 2016/12/15 16:17:57 by dle-blon         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef OPERANDFACTORY_CLASS_HPP
# define OPERANDFACTORY_CLASS_HPP

//# include <IOperand.class.hpp>
# include "IOperand.class.hpp"
# include "Operand.class.hpp"

typedef IOperand (OperandFactory::*t_pfunc) (std::string const &value) const;

class OperandFactory
{

private:

	static t_pfunc _pfuncArray[5];

	OperandFactory(OperandFactory const &src);
	~OperandFactory(void);
	OperandFactory &operator=(OperandFactory const &src);

	IOperand const *createInt8(std::string const &value) const;
	IOperand const *createInt16(std::string const &value) const;
	IOperand const *createInt32(std::string const &value) const;
	IOperand const *createFloat(std::string const &value) const;
	IOperand const *createDouble(std::string const &value) const;

public:

	OperandFactory(void);

	IOperand const * createOperand(eOperandType type, std::string const &value) const;

};

#endif
