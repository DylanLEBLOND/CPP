#ifndef LEXICALEXCEPTION_CLASS_HPP
# define LEXICALEXCEPTION_CLASS_HPP

# include <exception>		// std::exception
# include <string>			// std::string

class LexicalException : public std::exception
{
private:

	std::string _message;
	LexicalException();

public:

	LexicalException(std::string const &message);
	LexicalException(const char *message);
	LexicalException(LexicalException const &src);
	~LexicalException();

	LexicalException		&operator=(LexicalException const &src);

	const char*				what() const throw();

	std::string				getMessage() const;
};

#endif // LEXICALEXCEPTION_CLASS_HPP
