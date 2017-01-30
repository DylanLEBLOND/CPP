#ifndef SEMANTICEXCEPTION_CLASS_HPP
# define SEMANTICEXCEPTION_CLASS_HPP

# include <exception>		// std::exception
# include <string>			// std::string

class SemanticException : public std::exception
{
private:

	std::string _message;
	SemanticException();

public:

	SemanticException(std::string const &message);
	SemanticException(const char *message);
	SemanticException(SemanticException const &src);
	~SemanticException();

	SemanticException		&operator=(SemanticException const &src);

	const char*				what() const throw();

	std::string				getMessage() const;
};

#endif // SEMANTICEXCEPTION_CLASS_HPP
