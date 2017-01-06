# include "Operand.class.hpp"

/*
 * Constructors
 */
Operand::Operand(void) : _type(eOperandType::Unknown), _precision(0), _value (0), _value_str("null") {}

Operand::Operand(eOperandType type, std::string const &value_str)
{
	switch (type)
	{
		case eOperandType::Int8:
		case eOperandType::Int16:
		case eOperandType::Int32:
			if (! this->stringIsInteger (value_str))
				throw new  InvalidArgumentException ("Value is invalid");
			break;
		case eOperandType::Float:
		case eOperandType::Double:
			if (! this->stringIsFloating (value_str))
				throw new  InvalidArgumentException ("Value is invalid");
			break;
		default:		// Unknown
			throw new InvalidArgumentException ("Unknown Type");
			break;
	}

	this->_type = type;
	switch (this->_type)
	{
		case eOperandType::Int8:
			this->_precision = INT8_PRECISION;
			this->_value = this->getValueInt8(value_str);
			break;
		case eOperandType::Int16:
			this->_precision = INT16_PRECISION;
			this->_value = this->getValueInt16(value_str);
			break;
		case eOperandType::Int32:
			this->_precision = INT32_PRECISION;
			this->_value = this->getValueInt32(value_str);
			break;
		case eOperandType::Float:
			this->_precision = FLOAT_PRECISION;
			this->_value = this->getValueFloat(value_str);
			break;
		case eOperandType::Double:
			this->_precision = DOUBLE_PRECISION;
			this->_value = this->getValueDouble(value_str);
			break;
		default:		// Should never occurs
			throw new ShouldNeverOccurException (__FILE__, __LINE__);
			break;
	}
	this->_value_str = value_str;
}

Operand::Operand(IOperand const &src)
{
	switch (src.getType())
	{
		case eOperandType::Int8:
		case eOperandType::Int16:
		case eOperandType::Int32:
			if (! this->stringIsInteger (src.toString()))
				throw new  InvalidArgumentException ("Value is invalid");
			break;
		case eOperandType::Float:
		case eOperandType::Double:
			if (! this->stringIsFloating (src.toString()))
				throw new  InvalidArgumentException ("Value is invalid");
			break;
		default:		// Unknown
			throw new InvalidArgumentException ("Unknown Type");
			break;
	}

	this->_type = src.getType();
	switch (this->_type)
	{
		case eOperandType::Int8:
			this->_precision = INT8_PRECISION;
			this->_value = this->getValueInt8(src.toString());
			break;
		case eOperandType::Int16:
			this->_precision = INT16_PRECISION;
			this->_value = this->getValueInt16(src.toString());
			break;
		case eOperandType::Int32:
			this->_precision = INT32_PRECISION;
			this->_value = this->getValueInt32(src.toString());
			break;
		case eOperandType::Float:
			this->_precision = FLOAT_PRECISION;
			this->_value = this->getValueFloat(src.toString());
			break;
		case eOperandType::Double:
			this->_precision = DOUBLE_PRECISION;
			this->_value = this->getValueDouble(src.toString());
			break;
		default:		// Should never occurs
			throw new ShouldNeverOccurException (__FILE__, __LINE__);
			break;
	}
	this->_value_str = src.toString();
}

Operand::Operand(Operand const &src)
{
	*this = src;
}

/*
 * Destructor
 */
Operand::~Operand(void) {}

/*
 * Operator "=" Overload
 */
Operand					&Operand::operator=(Operand const &src)
{
	return *this;
}

/*
 * Getter
 */
unsigned int			Operand::getPrecision(void) const
{
	return this->_precision;
}

eOperandType			Operand::getType(void) const
{
	return this->_type;
}

template <typename T>
T						Operand::getValue(void) const
{
	return this->_value;
}

/*
 * toString
 */
std::string const		&Operand::toString(void) const
{
	return this->_value_str;
}

/*
 * Private
 */
bool					Operand::stringIsInteger (std::string const &str) const
{
	int i;

	if (str.length() == 0)
		return false;

	i = 0;
	if (str[0] == '-')
		i = 1;

	while (i < str.length())
	{
		if (!std::isdigit(str[i++]))
			return false;
	}

	return true;
}

bool					Operand::stringIsFloating (std::string const &str) const
{
	int i;
	int point_pos;

	if (str.length() == 0)
		return false;

	point_pos = str.find('.');
	if (point_pos == 0 || point_pos == str.length() - 1 || point_pos == std::string::npos)
		return false;

	i = 0;
	if (str[0] == '-')
		i = 1;

	while (i < str.length())
	{
		if (i == point_pos)
			i++;
		if (!std::isdigit(str[i++]))
			return false;
	}

	return true;
}

signed char				Operand::getValueInt8 (std::string const &str) const
{
	if (str[0] == '-')
	{
		if (str.compare (std::to_string(INT8_MIN)) < 0)
			throw new OverflowException (str);
	}
	else
	{
		if (str.compare (std::to_string(INT8_MAX)) < 0)
			throw new OverflowException (str);
	}

	return std::stoi (str);
}

signed short int		Operand::getValueInt16 (std::string const &str) const
{
	if (str[0] == '-')
	{
		if (str.compare (std::to_string(INT16_MIN)) < 0)
			throw new OverflowException (str);
	}
	else
	{
		if (str.compare (std::to_string(INT16_MAX)) < 0)
			throw new OverflowException (str);
	}

	return std::stoi (str);
}

signed long				Operand::getValueInt32 (std::string const &str) const
{
	if (str[0] == '-')
	{
		if (str.compare (std::to_string(INT32_MIN)) < 0)
			throw new OverflowException (str);
	}
	else
	{
		if (str.compare (std::to_string(INT32_MAX)) < 0)
			throw new OverflowException (str);
	}

	return std::stol (str);
}

float					Operand::getValueFloat (std::string const &str) const
{
	if (str[0] == '-')
	{
		if (str.compare (std::to_string(FLT_MIN)) < 0)
			throw new OverflowException (str);
	}
	else
	{
		if (str.compare (std::to_string(FLT_MAX)) < 0)
			throw new OverflowException (str);
		if (str.compare ("0") != 0 && str.compare(std::to_string(FLT_EPSILON)) > 0)
			throw new UnderflowException (str);
	}

	return std::stof (str);
}

double					Operand::getValueDouble (std::string const &str) const
{
	if (str[0] == '-')
	{
		if (str.compare (std::to_string(DBL_MIN)) < 0)
			throw new OverflowException (str);
	}
	else
	{
		if (str.compare (std::to_string(DBL_MAX)) < 0)
			throw new OverflowException (str);
		if (str.compare ("0") != 0 && str.compare(std::to_string(DBL_EPSILON)) > 0)
			throw new UnderflowException (str);
	}

	return std::stod (str);
}

/*
 * Public
 */
template <typename T>
IOperand const			*Operand::operator+(IOperand const &rhs) const
{
	Operand tmpOperand = new Operand (rhs);
	eOperandType newType;
	unsigned int newPrecision;

	T max;
	T min;

	newType = this->_type;
	if (this->_precision < rhs.getPrecision())
		newType = rhs.getType();

	switch (newType)
	{
		case eOperandType::Int8:
			min = INT8_MIN;
			max = INT8_MAX;
			break;
		case eOperandType::Int16:
			min = INT16_MIN;
			max = INT16_MAX;
			break;
		case eOperandType::Int32:
			min = INT32_MIN;
			max = INT32_MAX;
			break;
		case eOperandType::Float:
			min = FLT_MIN;
			max = FLT_MAX;
			break;
		case eOperandType::Double:
			min = DBL_MIN;
			max = DBL_MAX;
			break;
		default:		// Unknown
			throw new InvalidArgumentException ("Unknown Type");
			break;
	}

	if (this->_value > 0 && tmpOperand.getValue() > 0)
	{
		if (max - this->_value < tmpOperand.getValue())
			throw new OverflowException (this->_value_str + " + " + tmpOperand.toString() + " is greater than the greatest value possible for this type");


	}
	else if (this->_value > 0 && tmpOperand.getValue() < 0)
	{

	}
	else if (this->_value < 0 && tmpOperand.getValue() > 0)
	{

	}

	/* this->_value < 0 && tmpOperand.getValue() < 0 */
}

IOperand const			*Operand::operator-(IOperand const &rhs) const
{

}

IOperand const			*Operand::operator*(IOperand const &rhs) const
{

}

IOperand const			*Operand::operator/(IOperand const &rhs) const
{

}

IOperand const			*Operand::operator%(IOperand const &rhs) const
{

}

