#ifndef SYNTACTICEXCEPTION_CLASS_HPP
# define SYNTACTICEXCEPTION_CLASS_HPP

# include <exception>		// std::exception
# include <string>			// std::string

class SyntacticException : public std::exception
{
private:

	std::string _message;
	SyntacticException();

public:

	SyntacticException(std::string const &message);
	SyntacticException(const char *message);
	SyntacticException(SyntacticException const &src);
	~SyntacticException();

	SyntacticException		&operator=(SyntacticException const &src);

	const char*				what() const throw();

	std::string				getMessage() const;
};

#endif // SYNTACTICEXCEPTION_CLASS_HPP
