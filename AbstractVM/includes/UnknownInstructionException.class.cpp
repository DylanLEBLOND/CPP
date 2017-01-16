#include "UnknownInstructionException.class.hpp"

const char		*UnknownInstructionException::what() const throw()
{
	return "Unknown Instruction Exception";
}
