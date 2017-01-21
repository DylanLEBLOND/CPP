#ifndef STACKEXCEPTION_CLASS_HPP
# define STACKEXCEPTION_CLASS_HPP

# include <exception>		// std::exception
# include <string>			// std::string

class StackException : public std::exception
{
private:

	std::string _message;
	StackException();

public:

	StackException(std::string const &message);
	StackException(const char *message);
	StackException(StackException const &src);
	~StackException();

	StackException		&operator=(StackException const &src);

	const char*				what() const throw();

	std::string				getMessage() const;
};

#endif // STACKEXCEPTION_CLASS_HPP
