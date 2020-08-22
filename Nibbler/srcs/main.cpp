#include <nibbler.hpp>

void openSDL (guiFuncStruct *guiFunc)
{
	guiFunc->libHandle = dlopen ("./libs/SDL/lib/libguisdl.so", RTLD_LAZY);
	if (guiFunc->libHandle == NULL)
	{
		throw DynamicLoadGUIException (eGUI::SDL, "dlopen", dlerror());
	}

	guiFunc->createGUI = (IGUI *(*)(Board *, Snake *, int *, char **)) dlsym (guiFunc->libHandle, "createGUI");
	if (guiFunc->createGUI == NULL)
	{
		throw DynamicLoadGUIException (eGUI::SDL, "dlsym createGUI", dlerror());
	}

	guiFunc->destroyGUI = (void (*)(IGUI *)) dlsym (guiFunc->libHandle, "destroyGUI");
	if (guiFunc->destroyGUI == NULL)
	{
		throw DynamicLoadGUIException (eGUI::SDL, "dlsym destroyGUI", dlerror());
	}
}

void closeSDL (guiFuncStruct *guiFunc)
{
	if (dlclose (guiFunc->libHandle))
	{
		throw DynamicLoadGUIException (eGUI::SDL, "dlclose", dlerror());
	}

	guiFunc->libHandle = NULL;
	guiFunc->createGUI = NULL;
	guiFunc->destroyGUI = NULL;
}

int main (int ac, char **av)
{
	Board board (std::stoi (av[1]));
	Snake snake (10u, 10u, 3u, true);
	guiFuncStruct guiFunc;
	IGUI *currentGUI;
	eGUIEvent currentEvent;
	eGUI wantedGUI;
	bool running;

	try
	{
		openSDL (&guiFunc);
		currentGUI = guiFunc.createGUI (&board, &snake, &ac, av);
		currentGUI->start();

		running = true;
		while (running)
		{
			currentEvent = currentGUI->getEvent();
			switch (currentEvent)
			{
				case eGUIEvent::goLeft:
					snake.goLeft();
					break;
				case eGUIEvent::goRight:
					snake.goRight();
					break;
				case eGUIEvent::goUp:
					snake.goUp();
					break;
				case eGUIEvent::goDown:
					snake.goDown();
					break;
				case eGUIEvent::changeGUI:
					wantedGUI = currentGUI->wantedGUI();
					//change GUI here
					(void)wantedGUI;
					break;
				case eGUIEvent::nothingTODO:
					break;
				case eGUIEvent::quitGame:
					running = false;
					break;
				default:
					throw UnknownEventException (currentGUI->getGUIName(), currentEvent);
			}

			snake.moveStraight();
			currentGUI->updateGUI();
		}
		currentGUI->stop();

		closeSDL (&guiFunc);
	}
	catch (std::exception &e)
	{
		std::cerr << "Error : " << e.what() << std::endl;
	}

	switch (ac)
	{
		case 1:
			break;
		case 2:
			(void)av[1];
			break;
		default:
			break;
	}
	return 0;
}
