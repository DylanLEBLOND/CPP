#ifndef DIVMODBYZEROEXCEPTION_CLASS_HPP
# define DIVMODBYZEROEXCEPTION_CLASS_HPP

# include <exception>		// std::exception
# include <string>			// std::string

class DivModByZeroException : public std::exception
{
private:

	std::string _message;
	DivModByZeroException();

public:

	DivModByZeroException(std::string const &message);
	DivModByZeroException(const char *message);
	DivModByZeroException(DivModByZeroException const &src);
	~DivModByZeroException();

	DivModByZeroException		&operator=(DivModByZeroException const &src);

	const char*				what() const throw();

	std::string				getMessage() const;
};

#endif // DIVMODBYZEROEXCEPTION_CLASS_HPP
