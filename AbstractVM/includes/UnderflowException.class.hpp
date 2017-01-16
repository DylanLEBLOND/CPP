#ifndef UNDERFLOWEXCEPTION_CLASS_HPP
# define UNDERFLOWEXCEPTION_CLASS_HPP

# include <exception>		// std::exception
# include <string>			// std::string

class UnderflowException : public std::exception
{
private:

	std::string _message;
	UnderflowException();

public:

	UnderflowException(std::string const &message);
	UnderflowException(const char *message);
	UnderflowException(UnderflowException const &src);
	~UnderflowException();

	UnderflowException		&operator=(UnderflowException const &src);

	const char*				what() const throw();

	std::string				getMessage() const;
};

#endif // UNDERFLOWEXCEPTION_CLASS_HPP
