#ifndef UNKNOWNINSTRUCTIONEXCEPTION_CLASS_HPP
# define UNKNOWNINSTRUCTIONEXCEPTION_CLASS_HPP

# include <exception>

class UnknownInstructionException : public std::exception
{
public:

	virtual const char* what() const throw();
};

#endif // UNKNOWNINSTRUCTIONEXCEPTION_CLASS_HPP
