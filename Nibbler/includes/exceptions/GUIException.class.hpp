#ifndef GUIEXCEPTION_CLASS_HPP
# define GUIEXCEPTION_CLASS_HPP

/*
 * Personals Includes
 */
# include <IGUI.class.hpp>

/*
 * System Includes
 */
# include <exception>		// std::exception
# include <string>			// std::string

class GUIException : public std::exception
{
private:

	std::string		_message;

	GUIException (void);

public:

	GUIException	(eGUI affectedGUI, std::string const &GUIFunc);
	GUIException	(eGUI affectedGUI, const char *GUIFunc);
	GUIException	(GUIException const &src);
	~GUIException (void);

	GUIException		&operator= (GUIException const &src);

	const char*			what (void) const throw();

	std::string			getMessage (void) const;
};

#endif // GUIEXCEPTION_CLASS_HPP
