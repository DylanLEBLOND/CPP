#ifndef NIBBLER_HPP
# define NIBBLER_HPP

/*
 * Personals Includes
 */
# include <Bonus.class.hpp>
# include <Snake.class.hpp>
# include <Board.class.hpp>
# include <IGUI.class.hpp>
# include <Exceptions.hpp>
# include <common.hpp>

/*
 * System Includes
 */
# include <string>
# include <dlfcn.h>
# include <fstream>
# include <cstdlib>
# include <cstring>
# include <ctype.h>

/*
 * Enumerations
 */
enum class eGameStatus { finish, restart, changeLevel, backMainMenu, quit, UnknownStatus };

/*
 * Structures
 */
typedef struct nibblerParametersStruct
{
	unsigned int	width;
	unsigned int	height;
	eboardMode		boardMode;

} nibblerParametersStruct, *nibblerParametersPointer;

typedef struct guiFuncStruct
{
	void *libHandle;
	IGUI *(*createGUI)(Board *);
	void (*destroyGUI)(IGUI *);

	guiFuncStruct (void)
	{
		this->libHandle = NULL;
		this->createGUI = NULL;
		this->destroyGUI = NULL;
	}

	guiFuncStruct (guiFuncStruct const &src)
	{
		*this = src;
	}

	guiFuncStruct &operator= (guiFuncStruct const &src)
	{
		this->libHandle = src.libHandle;
		this->createGUI = src.createGUI;
		this->destroyGUI = src.destroyGUI;

		return *this;
	}

} guiFuncStruct;

/*
 * Functions
 */
void		openGUILibrary (eGUI wantedGUI, guiFuncStruct *guiFunc);
void		closeGUILibrary (eGUI currentGUI, guiFuncStruct *guiFunc);

#endif // NIBBLER_HPP
