#ifndef LEXICALEXCEPTION_CLASS_HPP
# define LEXICALEXCEPTION_CLASS_HPP

# include <exception>

class LexicalException : public std::exception
{
public:

	virtual const char* what() const throw();
};

#endif // LEXICALEXCEPTION_CLASS_HPP
