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
 * Structures
 */
typedef struct guiFuncStruct
{
	void *libHandle;
	IGUI *(*createGUI)(Board *, Snake *, Snake *);
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

void			standard_workflow(void);
void			file_workflow(char const *filename);

#endif // NIBBLER_HPP
