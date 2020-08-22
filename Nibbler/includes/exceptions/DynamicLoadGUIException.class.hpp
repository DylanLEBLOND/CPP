#ifndef DYNAMICLOADGUIEXCEPTION_CLASS_HPP
# define DYNAMICLOADGUIEXCEPTION_CLASS_HPP

/*
 * Personals Includes
 */
# include <IGUI.class.hpp>

/*
 * System Includes
 */
# include <exception>		// std::exception
# include <string>			// std::string

class DynamicLoadGUIException : public std::exception
{
private:

	std::string		_message;

	DynamicLoadGUIException (void);

public:

	DynamicLoadGUIException	(eGUI affectedGUI, std::string const &dlFunc, const char* dlErrorMessage);
	DynamicLoadGUIException	(eGUI affectedGUI, const char *dlFunc, const char* dlErrorMessage);
	DynamicLoadGUIException	(DynamicLoadGUIException const &src);
	~DynamicLoadGUIException (void);

	DynamicLoadGUIException		&operator= (DynamicLoadGUIException const &src);

	const char*					what (void) const throw();

	std::string					getMessage (void) const;
};

#endif // DYNAMICLOADGUIEXCEPTION_CLASS_HPP
