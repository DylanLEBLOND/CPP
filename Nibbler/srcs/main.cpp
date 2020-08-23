#include <nibbler.hpp>

void openSDL (guiFuncStruct *guiFunc)
{
	guiFunc->libHandle = dlopen ("./libguisdl.so", RTLD_LAZY);
	if (guiFunc->libHandle == NULL)
	{
		throw DynamicLoadGUIException (eGUI::SDL, "dlopen", dlerror());
	}

	guiFunc->createGUI = (IGUI *(*)(Board *, Snake *, Snake *)) dlsym (guiFunc->libHandle, "createGUI");
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

void startNibbler (unsigned int boardWidth, unsigned int boardHeight, bool multiPlayer)
{
	Board *board;
	Snake *snakeP1, *snakeP2;
	guiFuncStruct guiFunc;
	IGUI *currentGUI;
	eGUIEvent currentEvent;
	eGUI wantedGUI;
	bool running;
	unsigned int p1InitPosX, p1IinitPosY, p2InitPosX, p2IinitPosY;

	board = new Board();
	if (! board)
	{
		throw ShouldNeverOccurException (__FILE__, __LINE__);
	}
	board->initBoard (boardWidth, boardHeight, multiPlayer);

	if (! multiPlayer)
	{
		p1InitPosX = boardWidth / 2;
		p1IinitPosY = boardHeight / 2;
	}
	else
	{
		p1InitPosX = 10u;
		p1IinitPosY = 10u;
		p2InitPosX = boardWidth - 10;
		p2IinitPosY = boardHeight - 10;
	}

	snakeP1 = new Snake (p1InitPosX, p1IinitPosY, 4u, eSnakeDirection::East, true /* canPassThroughWall */);
	if (! snakeP1)
	{
		throw ShouldNeverOccurException (__FILE__, __LINE__);
	}

	if (multiPlayer)
	{
		snakeP2 = new Snake (p2InitPosX, p2IinitPosY, 4u, eSnakeDirection::West, true /* canPassThroughWall */);
		if (! snakeP1)
		{
			throw ShouldNeverOccurException (__FILE__, __LINE__);
		}
	}
	else
		snakeP2 = NULL;

	board->initPlayers (snakeP1, snakeP2);

	openSDL (&guiFunc);
	currentGUI = guiFunc.createGUI (board, snakeP1, snakeP2);
	currentGUI->start();

	running = true;
	while (running)
	{
		currentEvent = currentGUI->getEvent();
		switch (currentEvent)
		{
			case eGUIEvent::p1GoLeft:
				snakeP1->goLeft();
				break;
			case eGUIEvent::p1GoRight:
				snakeP1->goRight();
				break;
			case eGUIEvent::p1GoUp:
				snakeP1->goUp();
				break;
			case eGUIEvent::p1GoDown:
				snakeP1->goDown();
				break;
			case eGUIEvent::p2GoLeft:
				if (multiPlayer)
					snakeP2->goLeft();
				else
					throw UnknownEventException (currentGUI->getGUIName(), currentEvent);
				break;
			case eGUIEvent::p2GoRight:
				if (multiPlayer)
					snakeP2->goRight();
				else
					throw UnknownEventException (currentGUI->getGUIName(), currentEvent);
				break;
			case eGUIEvent::p2GoUp:
				if (multiPlayer)
					snakeP2->goUp();
				else
					throw UnknownEventException (currentGUI->getGUIName(), currentEvent);
				break;
			case eGUIEvent::p2GoDown:
				if (multiPlayer)
					snakeP2->goDown();
				else
					throw UnknownEventException (currentGUI->getGUIName(), currentEvent);
				break;
			case eGUIEvent::changeGUI:
				wantedGUI = currentGUI->wantedGUI();
				//change GUI her e

				std::cout << "Switch GUI: ";
				switch (wantedGUI)
				{
					case eGUI::SDL:
						std::cout << "SDL" << std::endl;
						break;
					case eGUI::openGL:
						std::cout << "OpenGL" << std::endl;
						break;
					case eGUI::MinilibX:
						std::cout << "MinilibX" << std::endl;
						break;
					default:
						throw ShouldNeverOccurException (__FILE__, __LINE__);
				}
				break;
			case eGUIEvent::nothingTODO:
				break;
			case eGUIEvent::quitGame:
				running = false;
				break;
			default:
				throw UnknownEventException (currentGUI->getGUIName(), currentEvent);
		}

		board->runTurn();
		currentGUI->updateGUI();

		if (! board->snakesAreAlive())
			running = false;
	}
	currentGUI->stop();

	closeSDL (&guiFunc);

	delete snakeP2;
	delete snakeP1;
	delete board;
}

int main (int ac, char **av)
{
	unsigned int boardWidth, boardHeight;

	switch (ac)
	{
		case 3:
			try
			{
				boardWidth = std::stoi (av[1]);
				if (boardWidth < 30 || 100 < boardWidth)
				{
					std::cerr << "Invalid boardWdith. boardWdith < 30 || boardWdith > 100 (" << boardWidth << ")." << std::endl;
					exit (0);
				}

				boardHeight = std::stoi (av[2]);
				if (boardHeight < 30 || 100 < boardHeight)
				{
					std::cerr << "Invalid boardWdith. boardWdith < 30 || boardWdith > 100 (" << boardHeight << ")." << std::endl;
					exit (0);
				}

				startNibbler (boardWidth, boardHeight, false /* multiPlayer */);
			}
			catch (std::exception &e)
			{
				std::cerr << "Error : " << e.what() << std::endl;
			}
			break;
		case 4:
			try
			{
				boardWidth = std::stoi (av[1]);
				if (boardWidth < 30 || 100 < boardWidth)
				{
					std::cerr << "Invalid boardWdith. boardWdith < 30 || boardWdith > 100 (" << boardWidth << ")." << std::endl;
					exit (0);
				}

				boardHeight = std::stoi (av[2]);
				if (boardHeight < 30 || 100 < boardHeight)
				{
					std::cerr << "Invalid boardWdith. boardWdith < 30 || boardWdith > 100 (" << boardHeight << ")." << std::endl;
					exit (0);
				}

				if (strcmp ("multiplayer:on", av[3]) && strcmp ("multiplayer:off", av[3]))
				{
					std::cerr << "Invalid multiplayer parameters. multiplayer:on || multiplayer:off (" << av[3] << ")." << std::endl;
					exit (0);
				}

				if (! strcmp ("multiplayer:on", av[3]))
					startNibbler (boardWidth, boardHeight, true /* multiPlayer */);
				else
					startNibbler (boardWidth, boardHeight, false /* multiPlayer */);
			}
			catch (std::exception &e)
			{
				std::cerr << "Error : " << e.what() << std::endl;
			}
			break;
		default:
			std::cerr << "Invalid parameters. ./nibbler boardWidth boardHeight" << std::endl;
			exit (0);
			break;
	}

	return 0;
}
