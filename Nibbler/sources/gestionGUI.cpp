#include <nibbler.hpp>

/*
 * OpenGUIs
 */
static void		openSDL (guiFuncStruct *guiFunc)
{
	guiFunc->libHandle = dlopen ("./libguisdl.so", RTLD_LAZY);
	if (guiFunc->libHandle == NULL)
	{
		throw DynamicLoadGUIException (eGUIString (eGUI::SDL), "dlopen", dlerror());
	}

	guiFunc->createGUI = (IGUI *(*)(Board *)) dlsym (guiFunc->libHandle, "createGUI");
	if (guiFunc->createGUI == NULL)
	{
		throw DynamicLoadGUIException (eGUIString (eGUI::SDL), "dlsym createGUI", dlerror());
	}

	guiFunc->destroyGUI = (void (*)(IGUI *)) dlsym (guiFunc->libHandle, "destroyGUI");
	if (guiFunc->destroyGUI == NULL)
	{
		throw DynamicLoadGUIException (eGUIString (eGUI::SDL), "dlsym destroyGUI", dlerror());
	}
}

static void		openSFML (guiFuncStruct *guiFunc)
{
	guiFunc->libHandle = dlopen ("./libguisfml.so", RTLD_LAZY);
	if (guiFunc->libHandle == NULL)
	{
		throw DynamicLoadGUIException (eGUIString (eGUI::SFML), "dlopen", dlerror());
	}

	guiFunc->createGUI = (IGUI *(*)(Board *)) dlsym (guiFunc->libHandle, "createGUI");
	if (guiFunc->createGUI == NULL)
	{
		throw DynamicLoadGUIException (eGUIString (eGUI::SFML), "dlsym createGUI", dlerror());
	}

	guiFunc->destroyGUI = (void (*)(IGUI *)) dlsym (guiFunc->libHandle, "destroyGUI");
	if (guiFunc->destroyGUI == NULL)
	{
		throw DynamicLoadGUIException (eGUIString (eGUI::SFML), "dlsym destroyGUI", dlerror());
	}
}

static void		openAllegro (guiFuncStruct *guiFunc)
{
	guiFunc->libHandle = dlopen ("./libguiallegro.so", RTLD_LAZY);
	if (guiFunc->libHandle == NULL)
	{
		throw DynamicLoadGUIException (eGUIString (eGUI::Allegro), "dlopen", dlerror());
	}

	guiFunc->createGUI = (IGUI *(*)(Board *)) dlsym (guiFunc->libHandle, "createGUI");
	if (guiFunc->createGUI == NULL)
	{
		throw DynamicLoadGUIException (eGUIString (eGUI::Allegro), "dlsym createGUI", dlerror());
	}

	guiFunc->destroyGUI = (void (*)(IGUI *)) dlsym (guiFunc->libHandle, "destroyGUI");
	if (guiFunc->destroyGUI == NULL)
	{
		throw DynamicLoadGUIException (eGUIString (eGUI::Allegro), "dlsym destroyGUI", dlerror());
	}
}

void			openGUILibrary (eGUI wantedGUI, guiFuncStruct *guiFunc)
{
	switch (wantedGUI)
	{
		case eGUI::SDL:
			print_trace ("Open GUI: SDL", true);
			openSDL (guiFunc);
			break;
		case eGUI::SFML:
			print_trace ("Open GUI: SFML", true);
			openSFML (guiFunc);
			break;
		case eGUI::Allegro:
			print_trace ("Open GUI: Allegro", true);
			openAllegro (guiFunc);
			break;
		default:
			throw ShouldNeverOccurException (__FILE__, __LINE__);
	}
}

/*
 * closeGUI
 */

static void		closeSDL (guiFuncStruct *guiFunc)
{
	if (dlclose (guiFunc->libHandle))
	{
		throw DynamicLoadGUIException (eGUIString (eGUI::SDL), "dlclose", dlerror());
	}
}

static void		closeSFML (guiFuncStruct *guiFunc)
{
	if (dlclose (guiFunc->libHandle))
	{
		throw DynamicLoadGUIException (eGUIString (eGUI::SFML), "dlclose", dlerror());
	}
}

static void		closeAllegro (guiFuncStruct *guiFunc)
{
	if (dlclose (guiFunc->libHandle))
	{
		throw DynamicLoadGUIException (eGUIString (eGUI::Allegro), "dlclose", dlerror());
	}
}

void			closeGUILibrary (eGUI currentGUI, guiFuncStruct *guiFunc)
{
	switch (currentGUI)
	{
		case eGUI::SDL:
			print_trace ("Close GUI: SDL", true);
			closeSDL (guiFunc);
			break;
		case eGUI::SFML:
			print_trace ("Close GUI: SFML", true);
			closeSFML (guiFunc);
			break;
		case eGUI::Allegro:
			print_trace ("Close GUI: Allegro", true);
			closeAllegro (guiFunc);
			break;
		default:
			throw ShouldNeverOccurException (__FILE__, __LINE__);
	}

	guiFunc->libHandle = NULL;
	guiFunc->createGUI = NULL;
	guiFunc->destroyGUI = NULL;
}

