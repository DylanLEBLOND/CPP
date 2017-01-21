#ifndef MODULOFLOATINGEXCEPTION_CLASS_HPP
# define MODULOFLOATINGEXCEPTION_CLASS_HPP

# include <exception>		// std::exception
# include <string>			// std::string

class ModuloFloatingException : public std::exception
{
private:

	std::string _message;
	ModuloFloatingException();

public:

	ModuloFloatingException(std::string const &message);
	ModuloFloatingException(const char *message);
	ModuloFloatingException(ModuloFloatingException const &src);
	~ModuloFloatingException();

	ModuloFloatingException		&operator=(ModuloFloatingException const &src);

	const char*				what() const throw();

	std::string				getMessage() const;
};

#endif // MODULOFLOATINGEXCEPTION_CLASS_HPP
