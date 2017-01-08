# include "Operand.class.hpp"

/*
 * Constructors
 */
Operand::Operand(void) : _type(eOperandType::Unknown), _precision(0), _value_str("null") {}

Operand::Operand(eOperandType type, std::string const &value_str)
{
	switch(type)
	{
		case eOperandType::Int8:
			if (! this->stringIsInteger(value_str))
				throw new  InvalidArgumentException("Value is invalid");
			this->getValueInt8(value_str);
			break;
		case eOperandType::Int16:
			if (! this->stringIsInteger(value_str))
				throw new  InvalidArgumentException("Value is invalid");
			this->getValueInt16(value_str);
			break;
		case eOperandType::Int32:
			if (! this->stringIsInteger(value_str))
				throw new  InvalidArgumentException("Value is invalid");
			this->getValueInt32(value_str);
			break;
		case eOperandType::Float:
			if (! this->stringIsFloating(value_str))
				throw new  InvalidArgumentException("Value is invalid");
			this->getValueFloat(value_str);
			break;
		case eOperandType::Double:
			if (! this->stringIsFloating(value_str))
				throw new  InvalidArgumentException("Value is invalid");
			this->getValueDouble(value_str);
			break;
		default:		// Unknown
			throw new InvalidArgumentException("Unknown Type");
			break;
	}

	this->_type = type;
	switch(this->_type)
	{
		case eOperandType::Int8:
			this->_precision = INT8_PRECISION;
			break;
		case eOperandType::Int16:
			this->_precision = INT16_PRECISION;
			break;
		case eOperandType::Int32:
			this->_precision = INT32_PRECISION;
			break;
		case eOperandType::Float:
			this->_precision = FLOAT_PRECISION;
			break;
		case eOperandType::Double:
			this->_precision = DOUBLE_PRECISION;
			break;
		default:		// Should never occurs
			throw new ShouldNeverOccurException(__FILE__, __LINE__);
			break;
	}
	this->_value_str = value_str;
}

Operand::Operand(IOperand const &src)
{
	std::string src_value_str = src.toString();

	switch(src.getType())
	{
		case eOperandType::Int8:
			if (! this->stringIsInteger(src_value_str))
				throw new  InvalidArgumentException("Value is invalid");
			this->getValueInt8(src_value_str);
			break;
		case eOperandType::Int16:
			if (! this->stringIsInteger(src_value_str))
				throw new  InvalidArgumentException("Value is invalid");
			this->getValueInt16(src_value_str);
			break;
		case eOperandType::Int32:
			if (! this->stringIsInteger(src_value_str))
				throw new  InvalidArgumentException("Value is invalid");
			this->getValueInt32(src_value_str);
			break;
		case eOperandType::Float:
			if (! this->stringIsFloating(src_value_str))
				throw new  InvalidArgumentException("Value is invalid");
			this->getValueFloat(src_value_str);
			break;
		case eOperandType::Double:
			if (! this->stringIsFloating(src_value_str))
				throw new  InvalidArgumentException("Value is invalid");
			this->getValueDouble(src_value_str);
			break;
		default:		// Unknown
			throw new InvalidArgumentException("Unknown Type");
			break;
	}

	this->_type = src.getType();
	switch(this->_type)
	{
		case eOperandType::Int8:
			this->_precision = INT8_PRECISION;
			break;
		case eOperandType::Int16:
			this->_precision = INT16_PRECISION;
			break;
		case eOperandType::Int32:
			this->_precision = INT32_PRECISION;
			break;
		case eOperandType::Float:
			this->_precision = FLOAT_PRECISION;
			break;
		case eOperandType::Double:
			this->_precision = DOUBLE_PRECISION;
			break;
		default:		// Should never occurs
			throw new ShouldNeverOccurException(__FILE__, __LINE__);
			break;
	}
	this->_value_str = src_value_str;
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
bool					Operand::stringIsInteger(std::string const &str) const
{
	int i;

	if (str.length() == 0)
		return false;

	i = 0;
	if (str[0] == '-')
		i = 1;

	while(i < str.length())
	{
		if (!std::isdigit(str[i++]))
			return false;
	}

	return true;
}

bool					Operand::stringIsFloating(std::string const &str) const
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

	while(i < str.length())
	{
		if (i == point_pos)
			i++;
		if (!std::isdigit(str[i++]))
			return false;
	}

	return true;
}

signed char				Operand::getValueInt8(std::string const &str) const
{
	if (str[0] == '-')
	{
		if (str.compare(std::to_string(INT8_MIN)) < 0)
			throw new OverflowException(str);
	}
	else
	{
		if (str.compare(std::to_string(INT8_MAX)) < 0)
			throw new OverflowException(str);
	}

	return std::stoi(str);
}

signed short int		Operand::getValueInt16(std::string const &str) const
{
	if (str[0] == '-')
	{
		if (str.compare(std::to_string(INT16_MIN)) < 0)
			throw new OverflowException(str);
	}
	else
	{
		if (str.compare(std::to_string(INT16_MAX)) < 0)
			throw new OverflowException(str);
	}

	return std::stoi(str);
}

signed long				Operand::getValueInt32(std::string const &str) const
{
	if (str[0] == '-')
	{
		if (str.compare(std::to_string(INT32_MIN)) < 0)
			throw new OverflowException(str);
	}
	else
	{
		if (str.compare(std::to_string(INT32_MAX)) < 0)
			throw new OverflowException(str);
	}

	return std::stol(str);
}

float					Operand::getValueFloat(std::string const &str) const
{
	if (str[0] == '-')
	{
		if (str.compare(std::to_string(FLT_MIN)) < 0)
			throw new OverflowException(str);
	}
	else
	{
		if (str.compare(std::to_string(FLT_MAX)) < 0)
			throw new OverflowException(str);
		if (str.compare("0") != 0 && str.compare(std::to_string(FLT_EPSILON)) > 0)
			throw new UnderflowException(str);
	}

	return std::stof(str);
}

double					Operand::getValueDouble(std::string const &str) const
{
	if (str[0] == '-')
	{
		if (str.compare(std::to_string(DBL_MIN)) < 0)
			throw new OverflowException(str);
	}
	else
	{
		if (str.compare(std::to_string(DBL_MAX)) < 0)
			throw new OverflowException(str);
		if (str.compare("0") != 0 && str.compare(std::to_string(DBL_EPSILON)) > 0)
			throw new UnderflowException(str);
	}

	return std::stod(str);
}

std::string				Operand::addInteger(std::string const &lhs, std::string const &rhs, signed long min, signed long max) const
{
	signed long a;
	signed long b;

	a = std::stol(lhs);
	b = std::stol(rhs);

	if (a > 0 && b > 0 && b > max - a)
		throw new OverflowException("(" + lhs + ") + (" + rhs + ")");
	if (a < 0 && b < 0 && b < min - a)
		throw new OverflowException("(" + lhs + ") + (" + rhs + ")");

	return std::to_string(a + b);
}

std::string				Operand::addFloating(std::string const &lhs, std::string const &rhs, double min, double max, double epsilon) const
{
	double a;
	double b;


	a = std::stod(lhs);
	b = std::stod(rhs);

	if (a > 0 && b > 0 && b > max - a)
		throw new OverflowException("(" + lhs + ") + (" + rhs + ")");
	if (a < 0 && b < 0 && b < min - a)
		throw new OverflowException("(" + lhs + ") + (" + rhs + ")");

	if (a > 0 && b < 0 && b < epsilon - a)
		throw new UnderflowException("(" + lhs + ") + (" + rhs + ")");
	if (a < 0 && b > 0 && b > -epsilon - a)
		throw new UnderflowException("(" + lhs + ") + (" + rhs + ")");

	return std::to_string(a + b);
}

std::string				Operand::subInteger(std::string const &lhs, std::string const &rhs, signed long min, signed long max) const
{
	signed long a;
	signed long b;

	a = std::stol(lhs);
	b = std::stol(rhs);

	if (a > 0 && b < 0 && b > a - max)
		throw new OverflowException("(" + lhs + ") + (" + rhs + ")");
	if (a < 0 && b > 0 && b < a - min)
		throw new OverflowException("(" + lhs + ") + (" + rhs + ")");

	return std::to_string(a + b);
}

/*
 * Public
 */
IOperand const			*Operand::operator+(IOperand const &rhs) const
{
	eOperandType newType;
	std::string newValue;
	unsigned int newPrecision;
	Operand tmpOperand = new Operand(rhs);

	newType = this->_type;
	if (this->_precision < tmpOperand.getPrecision())
		newType = tmpOperand.getType();

	switch(newType)
	{
		case eOperandType::Int8:
			newValue = this->addInteger(this->_value_str, tmpOperand.toString(), INT8_MIN, INT8_MAX);
			break;
		case eOperandType::Int16:
			newValue = this->addInteger(this->_value_str, tmpOperand.toString(), INT16_MIN, INT16_MAX);
			break;
		case eOperandType::Int32:
			newValue = this->addInteger(this->_value_str, tmpOperand.toString(), INT32_MIN, INT32_MAX);
			break;
		case eOperandType::Float:
			newValue = this->addFloating(this->_value_str, tmpOperand.toString(), FLT_MIN, FLT_MAX, FLT_EPSILON);
			break;
		case eOperandType::Double:
			newValue = this->addFloating(this->_value_str, tmpOperand.toString(), DBL_MIN, DBL_MAX, DBL_EPSILON);
			break;
		default:		// Unknown
			throw new InvalidArgumentException("Unknown Type");
			break;
	}

	return &(new Operand(newType, newValue));
}
#if 0
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
#endif
