#ifndef ABSTRACTVM_HPP
# define ABSTRACTVM_HPP

# include <iostream>
# include <fstream>
# include <cstdlib>
# include <cstring>

# include <common.hpp>
# include <Exceptions.hpp>
# include <Operand.class.hpp>
# include <Stack.class.hpp>


eInstruction	get_instruction(std::string const &line);
void			getPushData(std::string const &line, eOperandType &operand, std::string &value);
void			getAssertData(std::string const &line, eOperandType &operand, std::string &value);


void			standard_workflow(void);
void			file_workflow(char const *filename);

#endif // ABSTRACTVM_HPP
