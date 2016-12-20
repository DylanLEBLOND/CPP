# include "Operand.class.hpp"


/*
** Constructors
*/
Operand::Operand(eOperandType type, std::string value)
{
	//TEMP VERIF if value is valid


	switch (type)
	{
		case Int8:
		case Int16:
		case Int32:
		case Float:
		case Double:
			break;
		default:
			/* Should never occur */
			return NULL;
	}
	_type = type;
	_value = value;
}

Operand::Operand(Operand const &src)
{
	*this = src;
}

/*
** Destructor
*/
Operand::~Operand(void) {}

/*
** Operator "=" Overload
*/
Operand		&Operand::operator=(Operand const &src)
{
	return *this;
}

/*
** Private
*/


/*
** Public
*/
