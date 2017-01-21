#ifndef SYNTACTICEXCEPTION_CLASS_HPP
# define SYNTACTICEXCEPTION_CLASS_HPP

# include <exception>

#include "common.hpp"

class SyntacticException : public std::exception
{
private:

	std::string _instruction;
	SyntacticException();

public:

	SyntacticException(eInstruction instruction);
	SyntacticException(SyntacticException const &src);
	~SyntacticException();

	SyntacticException		&operator=(SyntacticException const &src);

	virtual const char*		what() const throw();

	std::string				getInstruction() const;
};

#endif // SYNTACTICEXCEPTION_CLASS_HPP
