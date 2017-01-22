#ifndef FILESTREAMEXCEPTION_CLASS_HPP
# define FILESTREAMEXCEPTION_CLASS_HPP

# include <exception>		// std::exception
# include <string>			// std::string

class FileStreamException : public std::exception
{
private:

	std::string _message;
	FileStreamException();

public:

	FileStreamException(std::string const &message);
	FileStreamException(const char *message);
	FileStreamException(FileStreamException const &src);
	~FileStreamException();

	FileStreamException		&operator=(FileStreamException const &src);

	const char*				what() const throw();

	std::string				getMessage() const;
};

#endif // FILESTREAMEXCEPTION_CLASS_HPP
