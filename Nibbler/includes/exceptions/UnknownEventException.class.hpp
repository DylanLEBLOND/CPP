#ifndef UNKNOWNEVENTEXCEPTION_CLASS_HPP
# define UNKNOWNEVENTEXCEPTION_CLASS_HPP

/*
 * Personals Includes
 */
# include <IGUI.class.hpp>

/*
 * System Includes
 */
# include <exception>		// std::exception
# include <string>			// std::string

class UnknownEventException : public std::exception
{
private:

	std::string		_message;

	UnknownEventException(void);

public:

	UnknownEventException(eGUI affectedGUI, eGUIEvent receivedEvent);
	UnknownEventException(UnknownEventException const &src);
	~UnknownEventException(void);

	UnknownEventException		&operator=(UnknownEventException const &src);

	const char*					what(void) const throw();

	std::string					getMessage (void) const;
};

#endif // UNKNOWNEVENTEXCEPTION_CLASS_HPP
