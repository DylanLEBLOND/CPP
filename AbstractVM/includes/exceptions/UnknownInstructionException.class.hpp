#ifndef UNKNOWNINSTRUCTIONEXCEPTION_CLASS_HPP
# define UNKNOWNINSTRUCTIONEXCEPTION_CLASS_HPP

# include <exception>		// std::exception
# include <string>			// std::string

class UnknownInstructionException : public std::exception
{
private:

	std::string _message;
	UnknownInstructionException();

public:

	UnknownInstructionException(std::string const &message);
	UnknownInstructionException(const char *message);
	UnknownInstructionException(UnknownInstructionException const &src);
	~UnknownInstructionException();

	UnknownInstructionException		&operator=(UnknownInstructionException const &src);

	const char*				what() const throw();

	std::string				getMessage() const;
};

#endif // UNKNOWNINSTRUCTIONEXCEPTION_CLASS_HPP
