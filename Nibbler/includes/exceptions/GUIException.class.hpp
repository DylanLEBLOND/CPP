#ifndef GUIEXCEPTION_CLASS_HPP
# define GUIEXCEPTION_CLASS_HPP

/*
 * Personals Includes
 */

/*
 * System Includes
 */
# include <exception>		// std::exception
# include <string>			// std::string

class GUIException : public std::exception
{
private:

	std::string			_message;

	GUIException (void);

public:

	GUIException (std::string const &affectedGUI, std::string const &GUIFunc);
	GUIException (std::string const &affectedGUI, std::string const &GUIFunc, std::string const &GUIErrorMessage);
	GUIException (const char *affectedGUI, const char *GUIFunc);
	GUIException (const char *affectedGUI, const char *GUIFunc, const char *GUIErrorMessage);
	GUIException (GUIException const &src);
	~GUIException (void);

	GUIException		&operator= (GUIException const &src);

	const char*			what (void) const throw();

	std::string			getMessage (void) const;
};

#endif // GUIEXCEPTION_CLASS_HPP
