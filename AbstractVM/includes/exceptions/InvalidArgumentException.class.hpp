#ifndef INVALIDARGUMENTEXCEPTION_CLASS_HPP
# define INVALIDARGUMENTEXCEPTION_CLASS_HPP

# include <exception>
# include <string>

class InvalidArgumentException : public std::exception
{
private:

	std::string _message;
	InvalidArgumentException();

public:

	InvalidArgumentException(std::string const &message);
	InvalidArgumentException(const char *message);
	InvalidArgumentException(InvalidArgumentException const &src);
	~InvalidArgumentException();

	InvalidArgumentException		&operator=(InvalidArgumentException const &src);

	const char*						what() const throw();

	std::string						getMessage() const;
};

#endif // INVALIDARGUMENTEXCEPTION_CLASS_HPP
