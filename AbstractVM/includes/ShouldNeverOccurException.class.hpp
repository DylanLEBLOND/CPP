#ifndef SHOULDNEVEROCCUREXCEPTION_CLASS_HPP
# define SHOULDNEVEROCCUREXCEPTION_CLASS_HPP

# include <exception>		// std::exception
# include <string>			// std::string

class ShouldNeverOccurException : public std::exception
{
private:

	std::string 	_file;
	unsigned int 	_line;
	ShouldNeverOccurException(void);

public:

	ShouldNeverOccurException(char const &file, unsigned int line);
	ShouldNeverOccurException(ShouldNeverOccurException const &src);
	~ShouldNeverOccurException(void);

	ShouldNeverOccurException		&operator=(ShouldNeverOccurException const &src);

	virtual const char*				what(void) const throw();

	char const						*getFile(void) const;
	unsigned int					getLine(void) const;
};

#endif // SHOULDNEVEROCCUREXCEPTION_CLASS_HPP
