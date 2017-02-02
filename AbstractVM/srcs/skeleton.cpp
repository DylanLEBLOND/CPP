#include <abstractVM.hpp>

void			getPushData(std::string const &line, eOperandType &operand, std::string &value)
{
	std::string	integer_type("(int8|int16|int32)");
	std::string	decimal_type("(float|double)");
	std::regex	check_syntax("^push ([[:alnum:]]+)\\((.*)\\)( ;.*)?$");
	std::regex	check_lexic_value("-?[[:digit:]]+(\\.[[:digit:]]+)?");
	std::regex	check_sementic_integer("push " + integer_type + "\\(-?[[:digit:]]+\\)( ;.*)?");
	std::regex	check_sementic_decimal("push " + decimal_type + "\\(-?[[:digit:]]+\\.[[:digit:]]+\\)( ;.*)?");
	std::smatch	match;

	operand = eOperandType::Unknown;
	value = "null";

	if (std::regex_search(line.begin(), line.end(), match, check_syntax))
	{
		if (! match[1].compare("int8"))
			operand = eOperandType::Int8;
		else if (! match[1].compare("int16"))
			operand = eOperandType::Int16;
		else if (! match[1].compare("int32"))
			operand = eOperandType::Int32;
		else if (! match[1].compare("float"))
			operand = eOperandType::Float;
		else if (! match[1].compare("double"))
			operand = eOperandType::Double;
		else
			throw LexicalException("expecting int8, int16, int32, float or double, but operand is : \"" + match.str(1) + "\"");

		if (std::regex_match(match.str(2), check_lexic_value))
		{
			if (operand == eOperandType::Float || operand == eOperandType::Double)
			{
				if (std::regex_match(line, check_sementic_decimal))
					value = match[2];
				else
					throw SemanticException ("expecting decimal value, but value is integer : \"" + match.str(2) + "\"");
			}
			else
			{
				if (std::regex_match(line, check_sementic_integer))
				value = match[2];
				else
					throw SemanticException ("expecting integer value, but value is decimal : \"" + match.str(2) + "\"");
			}
		}
		else
			throw LexicalException("expecting real number, but value is : \"" + match.str(2) + "\"");
	}
	else
		throw SyntacticException("correct syntax is : \"push operand(value)\"");
}

void			getAssertData(std::string const &line, eOperandType &operand, std::string &value)
{
	std::string	integer_type("(int8|int16|int32)");
	std::string	decimal_type("(float|double)");
	std::regex	check_syntax("^assert ([[:alnum:]]+)\\((.*)\\)( ;.*)?$");
	std::regex	check_lexic_value("-?[[:digit:]]+(\\.[[:digit:]]+)?");
	std::regex	check_sementic_integer("assert " + integer_type + "\\(-?[[:digit:]]+\\)( ;.*)?");
	std::regex	check_sementic_decimal("assert " + decimal_type + "\\(-?[[:digit:]]+\\.[[:digit:]]+\\)( ;.*)?");
	std::smatch	match;

	operand = eOperandType::Unknown;
	value = "null";

	if (std::regex_search(line.begin(), line.end(), match, check_syntax))
	{
		if (! match[1].compare("int8"))
			operand = eOperandType::Int8;
		else if (! match[1].compare("int16"))
			operand = eOperandType::Int16;
		else if (! match[1].compare("int32"))
			operand = eOperandType::Int32;
		else if (! match[1].compare("float"))
			operand = eOperandType::Float;
		else if (! match[1].compare("double"))
			operand = eOperandType::Double;
		else
			throw LexicalException("expecting int8, int16, int32, float or double, but operand is : \"" + match.str(1) + "\"");

		if (std::regex_match(match.str(2), check_lexic_value))
		{
			if (operand == eOperandType::Float || operand == eOperandType::Double)
			{
				if (std::regex_match(line, check_sementic_decimal))
					value = match[2];
				else
					throw SemanticException ("expecting decimal value, but value is integer : \"" + match.str(2) + "\"");
			}
			else
			{
				if (std::regex_match(line, check_sementic_integer))
				value = match[2];
				else
					throw SemanticException ("expecting integer value, but value is decimal : \"" + match.str(2) + "\"");
			}
		}
		else
			throw LexicalException("expecting real number, but value is : \"" + match.str(2) + "\"");
	}
	else
		throw SyntacticException("correct syntax is : \"assert operand(value)\"");
}

eInstruction	get_instruction(std::string const &line)
{
	if (line.find("push") == 0)
	{
		if (line.length() > 4 && line[4] != ' ')
			return eInstruction::Unknown;
		return eInstruction::Push;
	}

	if (line.find("pop") == 0)
	{
		if (line.length() > 3)
		{
			if (line[3] != ' ')
				return eInstruction::Unknown;
			if (line.length() > 4 && line[4] != ';')
				return eInstruction::Unknown;
		}
		return eInstruction::Pop;
	}

	if (line.find("dump") == 0)
	{
		if (line.length() > 4)
		{
			if (line[4] != ' ')
				return eInstruction::Unknown;
			if (line.length() > 5 && line[5] != ';')
				return eInstruction::Unknown;
		}
		return eInstruction::Dump;
	}

	if (line.find("assert") == 0)
	{
		if (line.length() > 6 && line[6] != ' ')
			return eInstruction::Unknown;
		return eInstruction::Assert;
	}

	if (line.find("add") == 0)
	{
		if (line.length() > 3)
		{
			if (line[3] != ' ')
				return eInstruction::Unknown;
			if (line.length() > 4 && line[4] != ';')
				return eInstruction::Unknown;
		}
		return eInstruction::Add;
	}

	if (line.find("sub") == 0)
	{
		if (line.length() > 3)
		{
			if (line[3] != ' ')
				return eInstruction::Unknown;
			if (line.length() > 4 && line[4] != ';')
				return eInstruction::Unknown;
		}
		return eInstruction::Sub;
	}

	if (line.find("mul") == 0)
	{
		if (line.length() > 3)
		{
			if (line[3] != ' ')
				return eInstruction::Unknown;
			if (line.length() > 4 && line[4] != ';')
				return eInstruction::Unknown;
		}
		return eInstruction::Mul;
	}

	if (line.find("div") == 0)
	{
		if (line.length() > 3)
		{
			if (line[3] != ' ')
				return eInstruction::Unknown;
			if (line.length() > 4 && line[4] != ';')
				return eInstruction::Unknown;
		}
		return eInstruction::Div;
	}

	if (line.find("mod") == 0)
	{
		if (line.length() > 3)
		{
			if (line[3] != ' ')
				return eInstruction::Unknown;
			if (line.length() > 4 && line[4] != ';')
				return eInstruction::Unknown;
		}
		return eInstruction::Mod;
	}

	if (line.find("print") == 0)
	{
		if (line.length() > 5)
		{
			if (line[5] != ' ')
				return eInstruction::Unknown;
			if (line.length() > 6 && line[6] != ';')
				return eInstruction::Unknown;
		}
		return eInstruction::Print;
	}

	if (line.find("exit") == 0)
	{
		if (line.length() > 4)
		{
			if (line[4] != ' ')
				return eInstruction::Unknown;
			if (line.length() > 5 && line[5] != ';')
				return eInstruction::Unknown;
		}
		return eInstruction::Exit;
	}

	return eInstruction::Unknown;
}
