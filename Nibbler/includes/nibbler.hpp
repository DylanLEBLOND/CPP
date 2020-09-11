#ifndef NIBBLER_HPP
# define NIBBLER_HPP

/*
 * Personals Includes
 */
# include <common.hpp>

/*
 * System Includes
 */
# include <string>
# include <dlfcn.h>

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
	eBoardMaps		selectedMap;
	eboadMode		boardMode;

} nibblerParametersStruct, *nibblerParametersPointer;

typedef struct guiFuncStruct
{
	void *libHandle;
	IGUI *(*createGUI)(Board *);
	void (*setPlayers)(IGUI *, Snake *, Snake *);
	void (*destroyGUI)(IGUI *);

	guiFuncStruct (void)
	{
		this->libHandle = NULL;
		this->createGUI = NULL;
		this->setPlayers = NULL;
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
		this->setPlayers = src.setPlayers;
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
