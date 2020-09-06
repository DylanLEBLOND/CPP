#include <nibbler.hpp>

/*
 * OpenGUIs
 */
static void		openSDL (guiFuncStruct *guiFunc)
{
	guiFunc->libHandle = dlopen ("./libguisdl.so", RTLD_LAZY);
	if (guiFunc->libHandle == NULL)
	{
		throw DynamicLoadGUIException (eGUI::SDL, "dlopen", dlerror());
	}

	guiFunc->createGUI = (IGUI *(*)(Board *)) dlsym (guiFunc->libHandle, "createGUI");
	if (guiFunc->createGUI == NULL)
	{
		throw DynamicLoadGUIException (eGUI::SDL, "dlsym createGUI", dlerror());
	}

	guiFunc->setPlayers = (void (*)(IGUI *, Snake *, Snake *)) dlsym (guiFunc->libHandle, "setPlayers");
	if (guiFunc->setPlayers == NULL)
	{
		throw DynamicLoadGUIException (eGUI::SDL, "dlsym setPlayers", dlerror());
	}

	guiFunc->destroyGUI = (void (*)(IGUI *)) dlsym (guiFunc->libHandle, "destroyGUI");
	if (guiFunc->destroyGUI == NULL)
	{
		throw DynamicLoadGUIException (eGUI::SDL, "dlsym destroyGUI", dlerror());
	}
}

static void		openOpenGL (guiFuncStruct *guiFunc)
{
	guiFunc->libHandle = dlopen ("./libguiopengl.so", RTLD_LAZY);
	if (guiFunc->libHandle == NULL)
	{
		throw DynamicLoadGUIException (eGUI::openGL, "dlopen", dlerror());
	}

	guiFunc->createGUI = (IGUI *(*)(Board *)) dlsym (guiFunc->libHandle, "createGUI");
	if (guiFunc->createGUI == NULL)
	{
		throw DynamicLoadGUIException (eGUI::openGL, "dlsym createGUI", dlerror());
	}

	guiFunc->setPlayers = (void (*)(IGUI *, Snake *, Snake *)) dlsym (guiFunc->libHandle, "setPlayers");
	if (guiFunc->setPlayers == NULL)
	{
		throw DynamicLoadGUIException (eGUI::openGL, "dlsym setPlayers", dlerror());
	}

	guiFunc->destroyGUI = (void (*)(IGUI *)) dlsym (guiFunc->libHandle, "destroyGUI");
	if (guiFunc->destroyGUI == NULL)
	{
		throw DynamicLoadGUIException (eGUI::openGL, "dlsym destroyGUI", dlerror());
	}
}

static void		openSFML (guiFuncStruct *guiFunc)
{
	guiFunc->libHandle = dlopen ("./libguisfml.so", RTLD_LAZY);
	if (guiFunc->libHandle == NULL)
	{
		throw DynamicLoadGUIException (eGUI::openGL, "dlopen", dlerror());
	}

	guiFunc->createGUI = (IGUI *(*)(Board *)) dlsym (guiFunc->libHandle, "createGUI");
	if (guiFunc->createGUI == NULL)
	{
		throw DynamicLoadGUIException (eGUI::openGL, "dlsym createGUI", dlerror());
	}

	guiFunc->setPlayers = (void (*)(IGUI *, Snake *, Snake *)) dlsym (guiFunc->libHandle, "setPlayers");
	if (guiFunc->setPlayers == NULL)
	{
		throw DynamicLoadGUIException (eGUI::openGL, "dlsym setPlayers", dlerror());
	}

	guiFunc->destroyGUI = (void (*)(IGUI *)) dlsym (guiFunc->libHandle, "destroyGUI");
	if (guiFunc->destroyGUI == NULL)
	{
		throw DynamicLoadGUIException (eGUI::openGL, "dlsym destroyGUI", dlerror());
	}
}

void			openGUILibrary (eGUI wantedGUI, guiFuncStruct *guiFunc)
{
	switch (wantedGUI)
	{
		case eGUI::SDL:
			std::cout << "Open GUI: SDL" << std::endl;
			openSDL (guiFunc);
			break;
		case eGUI::openGL:
			std::cout << "Open GUI: OpenGL" << std::endl;
			openOpenGL (guiFunc);
			break;
		case eGUI::SFML:
			std::cout << "Open GUI: SFML" << std::endl;
			openSFML (guiFunc);
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
		throw DynamicLoadGUIException (eGUI::SDL, "dlclose", dlerror());
	}
}

static void		closeOpenGL (guiFuncStruct *guiFunc)
{
	if (dlclose (guiFunc->libHandle))
	{
		throw DynamicLoadGUIException (eGUI::openGL, "dlclose", dlerror());
	}
}

static void		closeSFML (guiFuncStruct *guiFunc)
{
	if (dlclose (guiFunc->libHandle))
	{
		throw DynamicLoadGUIException (eGUI::SFML, "dlclose", dlerror());
	}
}

void			closeGUILibrary (eGUI currentGUI, guiFuncStruct *guiFunc)
{
	switch (currentGUI)
	{
		case eGUI::SDL:
			std::cout << "Close GUI: SDL" << std::endl;
			closeSDL (guiFunc);
			break;
		case eGUI::openGL:
			std::cout << "Close GUI: OpenGL" << std::endl;
			closeOpenGL (guiFunc);
			break;
		case eGUI::SFML:
			std::cout << "Close GUI: SFML" << std::endl;
			closeSFML (guiFunc);
			break;
		default:
			throw ShouldNeverOccurException (__FILE__, __LINE__);
	}

	guiFunc->libHandle = NULL;
	guiFunc->createGUI = NULL;
	guiFunc->setPlayers = NULL;
	guiFunc->destroyGUI = NULL;
}

