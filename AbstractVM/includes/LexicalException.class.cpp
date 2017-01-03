#include "UnknownInstructionException.class.hpp"

virtual const char		*UnknownInstructionException::what() const throw()
{
	return "Unknown Instruction";
}
