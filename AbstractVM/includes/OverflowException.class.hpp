#ifndef OVERFLOWEXCEPTION_CLASS_HPP
# define OVERFLOWEXCEPTION_CLASS_HPP

# include <exception>		// std::exception
# include <string>			// std::string

class OverflowException : public std::exception
{
private:

	std::string _message;
	OverflowException();

public:

	OverflowException(std::string &message);
	OverflowException(OverflowException const &src);
	~OverflowException();

	OverflowException		&operator=(OverflowException const &src);

	virtual const char*		what() const throw();

	std::string				getMessage() const;
};

#endif // OVERFLOWEXCEPTION_CLASS_HPP
