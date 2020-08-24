#include <nibbler.hpp>

static void startNibbler (nibblerParametersPointer nibblerParams)
{
	Board *board;
	Snake *snakeP1, *snakeP2;
	guiFuncStruct guiFunc;
	IGUI *GUI;
	eGUIEvent currentEvent;
	eGUI currentGUI, wantedGUI;
	bool running;
	unsigned int p1InitPosX, p1IinitPosY, p2InitPosX, p2IinitPosY;

	board = new Board();
	if (! board)
	{
		throw ShouldNeverOccurException (__FILE__, __LINE__);
	}
	board->initBoard (nibblerParams->width, nibblerParams->height, nibblerParams->multiplayer, nibblerParams->friendlyFire);

	if (! nibblerParams->multiplayer)
	{
		p1InitPosX = nibblerParams->width / 2;
		p1IinitPosY = nibblerParams->height / 2;
	}
	else
	{
		p1InitPosX = 10u;
		p1IinitPosY = 10u;
		p2InitPosX = nibblerParams->width - 10;
		p2IinitPosY = nibblerParams->height - 10;
	}

	snakeP1 = new Snake (p1InitPosX, p1IinitPosY, 4u, eSnakeDirection::East, true /* canPassThroughWall */);
	if (! snakeP1)
	{
		throw ShouldNeverOccurException (__FILE__, __LINE__);
	}

	if (nibblerParams->multiplayer)
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
	board->loadMap (eBoardMaps::Square);

	openGUILibrary (eGUI::SDL, &guiFunc);
	GUI = guiFunc.createGUI (board, snakeP1, snakeP2);
	GUI->start();

	currentGUI = eGUI::SDL;
	running = true;
	while (running)
	{
		currentEvent = GUI->getEvent();
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
				if (nibblerParams->multiplayer)
					snakeP2->goLeft();
				else
					throw UnknownEventException (currentGUI, currentEvent);
				break;
			case eGUIEvent::p2GoRight:
				if (nibblerParams->multiplayer)
					snakeP2->goRight();
				else
					throw UnknownEventException (currentGUI, currentEvent);
				break;
			case eGUIEvent::p2GoUp:
				if (nibblerParams->multiplayer)
					snakeP2->goUp();
				else
					throw UnknownEventException (currentGUI, currentEvent);
				break;
			case eGUIEvent::p2GoDown:
				if (nibblerParams->multiplayer)
					snakeP2->goDown();
				else
					throw UnknownEventException (currentGUI, currentEvent);
				break;
			case eGUIEvent::changeGUI:
				std::cout << "==> Switch GUI <==";
				wantedGUI = GUI->wantedGUI();

				GUI->stop();
				guiFunc.destroyGUI (GUI);
				closeGUILibrary (currentGUI, &guiFunc);

				openGUILibrary (wantedGUI, &guiFunc);
				GUI = guiFunc.createGUI (board, snakeP1, snakeP2);
				GUI->start();

				currentGUI = wantedGUI;
				break;
			case eGUIEvent::nothingTODO:
				break;
			case eGUIEvent::quitGame:
				running = false;
				break;
			default:
				throw UnknownEventException (GUI->getGUIName(), currentEvent);
		}

		board->runTurn();
		GUI->updateGUI();

		if (! board->snakesAreAlive())
			running = false;
	}
	GUI->stop();
	guiFunc.destroyGUI (GUI);
	closeGUILibrary (currentGUI, &guiFunc);

	board->clearBoard();

	delete snakeP2;
	delete snakeP1;
	delete board;
}

int main (int ac, char **av)
{
	nibblerParametersStruct nibblerParams;

	/* default */
	nibblerParams.width = 40u;
	nibblerParams.height = 40u;
	nibblerParams.multiplayer = false;
	nibblerParams.friendlyFire = true;
	nibblerParams.selectedMap = eBoardMaps::Square;

	switch (ac)
	{
		case 3:
			try
			{
				nibblerParams.width = std::stoi (av[1]);
				if (nibblerParams.width < 30 || 100 < nibblerParams.width)
				{
					std::cerr << "Invalid boardWdith. boardWdith < 30 || boardWdith > 100 (" << nibblerParams.width << ")." << std::endl;
					exit (0);
				}

				nibblerParams.height = std::stoi (av[2]);
				if (nibblerParams.height < 30 || 100 < nibblerParams.height)
				{
					std::cerr << "Invalid boardWdith. boardWdith < 30 || boardWdith > 100 (" << nibblerParams.height << ")." << std::endl;
					exit (0);
				}

				startNibbler (&nibblerParams);
			}
			catch (std::exception &e)
			{
				std::cerr << "Error : " << e.what() << std::endl;
			}
			break;
		case 4:
			try
			{
				nibblerParams.width = std::stoi (av[1]);
				if (nibblerParams.width < 30 || 100 < nibblerParams.width)
				{
					std::cerr << "Invalid boardWdith. boardWdith < 30 || boardWdith > 100 (" << nibblerParams.width << ")." << std::endl;
					exit (0);
				}

				nibblerParams.height = std::stoi (av[2]);
				if (nibblerParams.height < 30 || 100 < nibblerParams.height)
				{
					std::cerr << "Invalid boardWdith. boardWdith < 30 || boardWdith > 100 (" << nibblerParams.height << ")." << std::endl;
					exit (0);
				}

				if (strcmp ("multiplayer:on", av[3]) && strcmp ("multiplayer:off", av[3]))
				{
					std::cerr << "Invalid multiplayer parameters. multiplayer:on || multiplayer:off (" << av[3] << ")." << std::endl;
					exit (0);
				}

				nibblerParams.multiplayer = ! strcmp ("multiplayer:on", av[3]) ? true : false;

				startNibbler (&nibblerParams);
			}
			catch (std::exception &e)
			{
				std::cerr << "Error : " << e.what() << std::endl;
			}
			break;
		case 5:
			try
			{
				nibblerParams.width = std::stoi (av[1]);
				if (nibblerParams.width < 30 || 100 < nibblerParams.width)
				{
					std::cerr << "Invalid boardWdith. boardWdith < 30 || boardWdith > 100 (" << nibblerParams.width << ")." << std::endl;
					exit (0);
				}

				nibblerParams.height = std::stoi (av[2]);
				if (nibblerParams.height < 30 || 100 < nibblerParams.height)
				{
					std::cerr << "Invalid boardWdith. boardWdith < 30 || boardWdith > 100 (" << nibblerParams.height << ")." << std::endl;
					exit (0);
				}

				if (strcmp ("multiplayer:on", av[3]) && strcmp ("multiplayer:off", av[3]))
				{
					std::cerr << "Invalid multiplayer parameters. multiplayer:on || multiplayer:off (" << av[3] << ")." << std::endl;
					exit (0);
				}

				if (strcmp ("friendlyfire:on", av[4]) && strcmp ("friendlyfire:off", av[4]))
				{
					std::cerr << "Invalid friendlyFire parameters. friendlyFire:on || friendlyFire:off (" << av[4] << ")." << std::endl;
					exit (0);
				}

				nibblerParams.multiplayer = ! strcmp ("multiplayer:on", av[3]) ? true : false;
				nibblerParams.friendlyFire = ! strcmp ("friendlyfire:on", av[4]) ? true : false;

				startNibbler (&nibblerParams);
			}
			catch (std::exception &e)
			{
				std::cerr << "Error : " << e.what() << std::endl;
			}
			break;
		default:
			std::cerr << "Invalid parameters.See README" << std::endl;
			exit (0);
			break;
	}

	return 0;
}
