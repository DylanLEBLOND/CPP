#ifndef ABSTRACTVM_HPP
# define ABSTRACTVM_HPP

# include <iostream>
# include <cstdlib>
# include <cstring>

#include "common.hpp"
# include "UnknownInstructionException.class.hpp"

//Operand Class
# include "Operand.class.hpp"

eInstruction	get_instruction(std::string line);

void			standard_workflow(void);
void			file_workflow(char *filename);

#endif // ABSTRACTVM_HPP
