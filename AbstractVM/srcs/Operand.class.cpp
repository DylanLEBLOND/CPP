#include <Operand.class.hpp>

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
				throw InvalidArgumentException("Value is invalid");
			this->getValueInteger(value_str, INT8_MIN, INT8_MAX);
			break;
		case eOperandType::Int16:
			if (! this->stringIsInteger(value_str))
				throw InvalidArgumentException("Value is invalid");
			this->getValueInteger(value_str, INT16_MIN, INT16_MAX);
			break;
		case eOperandType::Int32:
			if (! this->stringIsInteger(value_str))
				throw InvalidArgumentException("Value is invalid");
			std::cout << "ICICI" << std::endl;
			this->getValueInteger(value_str, INT32_MIN, INT32_MAX);
			break;
		case eOperandType::Float:
			if (! this->stringIsFloating(value_str))
				throw InvalidArgumentException("Value is invalid");
			this->getValueFloating(value_str, FLT_MIN, FLT_MAX, true);
			break;
		case eOperandType::Double:
			if (! this->stringIsFloating(value_str))
				throw InvalidArgumentException("Value is invalid");
			this->getValueFloating(value_str, DBL_MIN, DBL_MAX, false);
			break;
		default:		// Unknown
			throw InvalidArgumentException("Unknown Type");
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
			throw ShouldNeverOccurException(__FILE__, __LINE__);
			break;
	}

	if (this->_type == eOperandType::Float || this->_type == eOperandType::Double)
	{
		std::stringstream stream;

		stream << std::fixed << std::setprecision (FLOATING_POINT_DIGITS) << stod (value_str);
		this->_value_str = stream.str();
	}
	else
		this->_value_str = value_str;
}

Operand::Operand(IOperand const &src)
{
	std::string src_value_str = src.toString();

	switch(src.getType())
	{
		case eOperandType::Int8:
			if (! this->stringIsInteger(src_value_str))
				throw InvalidArgumentException("Value is invalid");
			this->getValueInteger(src_value_str, INT8_MIN, INT8_MAX);
			break;
		case eOperandType::Int16:
			if (! this->stringIsInteger(src_value_str))
				throw InvalidArgumentException("Value is invalid");
			this->getValueInteger(src_value_str, INT16_MIN, INT16_MAX);
			break;
		case eOperandType::Int32:
			if (! this->stringIsInteger(src_value_str))
				throw InvalidArgumentException("Value is invalid");
			this->getValueInteger(src_value_str, INT32_MIN, INT32_MAX);
			break;
		case eOperandType::Float:
			if (! this->stringIsFloating(src_value_str))
				throw InvalidArgumentException("Value is invalid");
			this->getValueFloating(src_value_str, FLT_MIN, FLT_MAX, true);
			break;
		case eOperandType::Double:
			if (! this->stringIsFloating(src_value_str))
				throw InvalidArgumentException("Value is invalid");
			this->getValueFloating(src_value_str, DBL_MIN, DBL_MAX, false);
			break;
		default:		// Unknown
			throw InvalidArgumentException("Unknown Type");
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
			throw ShouldNeverOccurException(__FILE__, __LINE__);
			break;
	}

	if (this->_type == eOperandType::Float || this->_type == eOperandType::Double)
	{
		std::stringstream stream;

		stream << std::fixed << std::setprecision (FLOATING_POINT_DIGITS) << stod (src_value_str);
		this->_value_str = stream.str();
	}
	else
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
	this->_type = src.getType();
	this->_precision = src.getPrecision();
	this->_value_str = src.toString();

	return *this;
}

Operand					&Operand::operator=(IOperand const &src)
{
	this->_type = src.getType();
	this->_precision = src.getPrecision();
	this->_value_str = src.toString();

	return *this;
}


/*
 * Getter
 */
int						Operand::getPrecision(void) const
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
	size_t i;

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
	size_t i;
	size_t point_pos;

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

signed long				Operand::getValueInteger(std::string const &str, signed long min, signed long max) const
{
	std::string min_str = std::to_string(min);
	std::string max_str = std::to_string(max);

	if (str[0] == '-')
	{
		if (str.length() >= min_str.length() && str.compare(min_str) > 0)
			throw OverflowException(str);
	}
	else
	{
		if (str.length() >= max_str.length() && str.compare(max_str) > 0)
			throw OverflowException(str);
	}

	return std::stol(str);
}

double					Operand::getValueFloating (std::string const &str, double min, double max, bool isFloat) const
{
	std::string min_str = std::to_string(min);
	std::string max_str = std::to_string(max);

	if (str[0] == '-')
	{
		if (str.length() >= min_str.length() && str.compare(min_str) > 0)
			throw OverflowException(str);
	}
	else
	{
		if (str.length() >= max_str.length() && str.compare(max_str) > 0)
			throw OverflowException(str);
	}
	try
	{
		if (isFloat)
			std::stof (str);
		else
			std::stod (str);
	}
	catch (std::out_of_range &u)
	{
		throw UnderflowException (str);
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
		throw OverflowException("( " + lhs + " ) + ( " + rhs + " )");
	if (a < 0 && b < 0 && b < min - a)
		throw OverflowException("( " + lhs + " ) + ( " + rhs + " )");

	return std::to_string(a + b);
}

std::string				Operand::addFloating(std::string const &lhs, std::string const &rhs, double min, double max, bool isFloat) const
{
	double a;
	double b;
	std::stringstream stream;

	a = std::stod(lhs);
	b = std::stod(rhs);

	if (a > 0 && b > 0 && b > max - a)
		throw OverflowException("( " + lhs + " ) + ( " + rhs + " )");
	if (a < 0 && b < 0 && a < min - a)
		throw OverflowException("( " + lhs + " ) + ( " + rhs + " )");

	try
	{
		std::stringstream underflowStream;

		if (isFloat)
		{
			underflowStream << std::fixed << std::setprecision (38) << a + b;
			stof (underflowStream.str());
		}
		else
		{
			underflowStream << std::fixed << std::setprecision (308) << a + b;
			stod (underflowStream.str());
		}
	}
	catch (std::out_of_range &u)
	{
		throw UnderflowException("( " + lhs + " ) + ( " + rhs + " )");
	}

	stream << std::fixed << std::setprecision (FLOATING_POINT_DIGITS) << a + b;
	return stream.str();
}

std::string				Operand::subInteger(std::string const &lhs, std::string const &rhs, signed long min, signed long max) const
{
	signed long a;
	signed long b;

	a = std::stol(lhs);
	b = std::stol(rhs);

	if (a > 0 && b < 0 && b > a - max)
		throw OverflowException("( " + lhs + " ) - ( " + rhs + " )");
	if (a < 0 && b > 0 && b < a - min)
		throw OverflowException("( " + lhs + " ) - ( " + rhs + " )");

	return std::to_string(a - b);
}

std::string				Operand::subFloating(std::string const &lhs, std::string const &rhs, double min, double max, bool isFloat) const
{
	double a;
	double b;
	std::stringstream stream;

	a = std::stod(lhs);
	b = std::stod(rhs);

	if (a > 0 && b < 0 && b > a - max)
		throw OverflowException("( " + lhs + " ) - ( " + rhs + " )");
	if (a < 0 && b > 0 && b < a - min)
		throw OverflowException("( " + lhs + " ) - ( " + rhs + " )");

	try
	{
		std::stringstream underflowStream;

		if (isFloat)
		{
			underflowStream << std::fixed << std::setprecision (38) << a - b;
			stof (underflowStream.str());
		}
		else
		{
			underflowStream << std::fixed << std::setprecision (308) << a - b;
			stod (underflowStream.str());
		}
	}
	catch (std::out_of_range &u)
	{
		throw UnderflowException("( " + lhs + " ) - ( " + rhs + " )");
	}

	stream << std::fixed << std::setprecision (FLOATING_POINT_DIGITS) << a - b;
	return stream.str();
}

std::string				Operand::mulInteger(std::string const &lhs, std::string const &rhs, signed long min, signed long max) const
{
	signed long a;
	signed long b;

	a = std::stol(lhs);
	b = std::stol(rhs);

	if (((a > 0 && b > 0) || (a < 0 && b < 0)) && b > max / a)
		throw OverflowException("( " + lhs + " ) * ( " + rhs + " )");
	if (((a > 0 && b < 0) || (a < 0 && b > 0)) && b < min / a)
		throw OverflowException("( " + lhs + " ) * ( " + rhs + " )");

	return std::to_string(a * b);
}

std::string				Operand::mulFloating(std::string const &lhs, std::string const &rhs, double min, double max, bool isFloat) const
{
	double a;
	double b;
	std::stringstream stream;

	a = std::stod(lhs);
	b = std::stod(rhs);

	if (((a > 1 && b > 1) || (a < -1 && b < -1)) && b > max / a)
		throw OverflowException("( " + lhs + " ) * ( " + rhs + " )");
	if (((a > 1 && b < -1) || (a < -1 && b > -1)) && b < min / a)
		throw OverflowException("( " + lhs + " ) * ( " + rhs + " )");

	try
	{
		std::stringstream underflowStream;

		if (isFloat)
		{
			underflowStream << std::fixed << std::setprecision (38) << a * b;
			stof (underflowStream.str());
		}
		else
		{
			underflowStream << std::fixed << std::setprecision (308) << a * b;
			stod (underflowStream.str());
		}
	}
	catch (std::out_of_range &u)
	{
		throw UnderflowException("( " + lhs + " ) * ( " + rhs + " )");
	}

	stream << std::fixed << std::setprecision (FLOATING_POINT_DIGITS) << a * b;
	return stream.str();
}

std::string				Operand::divInteger(std::string const &lhs, std::string const &rhs) const
{
	signed long a;
	signed long b;

	a = std::stol(lhs);
	b = std::stol(rhs);

	if (b == 0)
		throw DivModByZeroException("( " + lhs + " ) / ( " + rhs + " )");

	return std::to_string(a / b);
}

std::string				Operand::divFloating (std::string const &lhs, std::string const &rhs, double min, double max, bool isFloat) const
{
	double a;
	double b;
	std::stringstream stream;

	a = std::stod(lhs);
	b = std::stod(rhs);

	if (b == 0)
		throw DivModByZeroException("( " + lhs + " ) / ( " + rhs + " )");

	if ((0 < b && b < 1) && a > max * b)
		throw OverflowException("( " + lhs + " ) / ( " + rhs + " )");
	if ((-1 < b && b < 0) && a < min * b)
			throw OverflowException("( " + lhs + " ) / ( " + rhs + " )");

	try
	{
		std::stringstream underflowStream;

		if (isFloat)
		{
			underflowStream << std::fixed << std::setprecision (38) << a / b;
			stof (underflowStream.str());
		}
		else
		{
			underflowStream << std::fixed << std::setprecision (308) << a / b;
			stod (underflowStream.str());
		}
	}
	catch (std::out_of_range &u)
	{
		throw UnderflowException("( " + lhs + " ) / ( " + rhs + " )");
	}

	stream << std::fixed << std::setprecision (FLOATING_POINT_DIGITS) << a / b;
	return stream.str();
}

std::string				Operand::modulo(std::string const &lhs, std::string const &rhs) const
{
	signed long a;
	signed long b;

	a = std::stol(lhs);
	b = std::stol(rhs);

	if (b == 0)
		throw DivModByZeroException("( " + lhs + " ) % ( " + rhs + " )");

	return std::to_string(a % b);
}


/*
 * Public
 */
IOperand const			*Operand::operator+(IOperand const &rhs) const
{
	eOperandType Type;
	std::string Value;
	Operand tmpOperand (rhs);

	Type = this->_type;
	if (this->_precision < tmpOperand.getPrecision())
		Type = tmpOperand.getType();

	switch(Type)
	{
		case eOperandType::Int8:
			Value = this->addInteger(this->_value_str, tmpOperand.toString(), INT8_MIN, INT8_MAX);
			break;
		case eOperandType::Int16:
			Value = this->addInteger(this->_value_str, tmpOperand.toString(), INT16_MIN, INT16_MAX);
			break;
		case eOperandType::Int32:
			Value = this->addInteger(this->_value_str, tmpOperand.toString(), INT32_MIN, INT32_MAX);
			break;
		case eOperandType::Float:
			Value = this->addFloating(this->_value_str, tmpOperand.toString(), -FLT_MAX, FLT_MAX, true);
			break;
		case eOperandType::Double:
			Value = this->addFloating(this->_value_str, tmpOperand.toString(), -DBL_MAX, DBL_MAX, false);
			break;
		default:		// Unknown
			throw InvalidArgumentException("Unknown Type");
			break;
	}

	return new Operand(Type, Value);
}

IOperand const			*Operand::operator-(IOperand const &rhs) const
{
	eOperandType Type;
	std::string Value;
	Operand tmpOperand (rhs);

	Type = this->_type;
	if (this->_precision < tmpOperand.getPrecision())
		Type = tmpOperand.getType();

	switch(Type)
	{
		case eOperandType::Int8:
			Value = this->subInteger(this->_value_str, tmpOperand.toString(), INT8_MIN, INT8_MAX);
			break;
		case eOperandType::Int16:
			Value = this->subInteger(this->_value_str, tmpOperand.toString(), INT16_MIN, INT16_MAX);
			break;
		case eOperandType::Int32:
			Value = this->subInteger(this->_value_str, tmpOperand.toString(), INT32_MIN, INT32_MAX);
			break;
		case eOperandType::Float:
			Value = this->subFloating(this->_value_str, tmpOperand.toString(), -FLT_MAX, FLT_MAX, true);
			break;
		case eOperandType::Double:
			Value = this->subFloating(this->_value_str, tmpOperand.toString(), -DBL_MAX, DBL_MAX, false);
			break;
		default:		// Unknown
			throw InvalidArgumentException("Unknown Type");
			break;
	}

	return new Operand(Type, Value);
}

IOperand const			*Operand::operator*(IOperand const &rhs) const
{
	eOperandType Type;
	std::string Value;
	Operand tmpOperand (rhs);

	Type = this->_type;
	if (this->_precision < tmpOperand.getPrecision())
		Type = tmpOperand.getType();

	switch(Type)
	{
		case eOperandType::Int8:
			Value = this->mulInteger(this->_value_str, tmpOperand.toString(), INT8_MIN, INT8_MAX);
			break;
		case eOperandType::Int16:
			Value = this->mulInteger(this->_value_str, tmpOperand.toString(), INT16_MIN, INT16_MAX);
			break;
		case eOperandType::Int32:
			Value = this->mulInteger(this->_value_str, tmpOperand.toString(), INT32_MIN, INT32_MAX);
			break;
		case eOperandType::Float:
			Value = this->mulFloating(this->_value_str, tmpOperand.toString(), -FLT_MAX, FLT_MAX, true);
			break;
		case eOperandType::Double:
			Value = this->mulFloating(this->_value_str, tmpOperand.toString(), -DBL_MAX, DBL_MAX, false);
			break;
		default:		// Unknown
			throw InvalidArgumentException("Unknown Type");
			break;
	}

	return new Operand(Type, Value);
}

IOperand const			*Operand::operator/(IOperand const &rhs) const
{
	eOperandType Type;
	std::string Value;
	Operand tmpOperand (rhs);

	Type = this->_type;
	if (this->_precision < tmpOperand.getPrecision())
		Type = tmpOperand.getType();

	switch(Type)
	{
		case eOperandType::Int8:
		case eOperandType::Int16:
		case eOperandType::Int32:
			Value = this->divInteger(this->_value_str, tmpOperand.toString());
			break;
		case eOperandType::Float:
			Value = this->divFloating(this->_value_str, tmpOperand.toString(), -FLT_MAX, FLT_MAX, true);
			break;
		case eOperandType::Double:
			Value = this->divFloating(this->_value_str, tmpOperand.toString(), -DBL_MAX, DBL_MAX, false);
			break;
		default:		// Unknown
			throw InvalidArgumentException("Unknown Type");
			break;
	}

	return new Operand(Type, Value);
}

IOperand const			*Operand::operator%(IOperand const &rhs) const
{
	eOperandType Type;
	std::string Value;
	Operand tmpOperand (rhs);

	Type = this->_type;
	if (this->_precision < tmpOperand.getPrecision())
		Type = tmpOperand.getType();

	switch(Type)
	{
		case eOperandType::Int8:
		case eOperandType::Int16:
		case eOperandType::Int32:
			Value = this->modulo(this->_value_str, tmpOperand.toString());
			break;
		case eOperandType::Float:
		case eOperandType::Double:
			throw ModuloFloatingException("( " + this->_value_str + " ) % ( " + tmpOperand.toString() + " )");
			break;
		default:		// Unknown
			throw InvalidArgumentException("Unknown Type");
			break;
	}

	return new Operand(Type, Value);
}

