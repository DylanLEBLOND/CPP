#include <nibbler.hpp>

static eGameStatus		startGame (Board *board, Snake *snakeP1, Snake *snakeP2,
								   nibblerParametersPointer nibblerParams,
								   guiFuncStruct *guiFunc, IGUI *GUI)
{
	eGUIEvent currentEvent;
	eGUI currentGUI, wantedGUI;

	std::cout << "startGame BEGIN" << std::endl;

	currentGUI = GUI->getGUIName();
	while (true)
	{
		GUI->updateGUI();

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
				guiFunc->destroyGUI (GUI);
				closeGUILibrary (currentGUI, guiFunc);

				openGUILibrary (wantedGUI, guiFunc);
				GUI = guiFunc->createGUI (board, snakeP1, snakeP2);
				GUI->start();

				currentGUI = wantedGUI;
				break;
			case eGUIEvent::nothingTODO:
				break;
			case eGUIEvent::quitGame:
				std::cout << "startGame END (Quit)" << std::endl;
				return eGameStatus::quit;
			default:
				throw UnknownEventException (GUI->getGUIName(), currentEvent);
		}

		board->runTurn();

		if (! board->snakesAreAlive())
		{
			std::cout << "startGame END (Finish)" << std::endl;
			return eGameStatus::finish;
		}
	}

	std::cout << "startGame END (UnknownStatus)" << std::endl;

	return eGameStatus::UnknownStatus;
}

static eGameStatus		endGame (Board *board, Snake *snakeP1, Snake *snakeP2,
								 guiFuncStruct *guiFunc, IGUI *GUI)
{
	eGUIMenuEvent currentEvent;
	eGUI currentGUI, wantedGUI;

	std::cout << "endGame BEGIN" << std::endl;

	currentGUI = GUI->getGUIName();

	GUI->loadMenu();

	while (true)
	{
		currentEvent = GUI->getMenuEvent();
		switch (currentEvent)
		{
			case eGUIMenuEvent::changeGUI:
				std::cout << "==> Switch GUI <==";
				wantedGUI = GUI->wantedGUI();

				GUI->stop();
				guiFunc->destroyGUI (GUI);
				closeGUILibrary (currentGUI, guiFunc);

				openGUILibrary (wantedGUI, guiFunc);
				GUI = guiFunc->createGUI (board, snakeP1, snakeP2);
				GUI->start();

				currentGUI = wantedGUI;
				break;

			case eGUIMenuEvent::restartLevel:
				std::cout << "endGame END (restart)" << std::endl;
				return eGameStatus::restart;

			case eGUIMenuEvent::nextLevel:
				std::cout << "endGame END (changeLevel)" << std::endl;
				return eGameStatus::changeLevel;

			case eGUIMenuEvent::quitGame:
				std::cout << "endGame END (quit)" << std::endl;
				return eGameStatus::quit;

			default:
				throw UnknownEventException (GUI->getGUIName(), currentEvent);
		}
	}

	std::cout << "endGame END (Quit)" << std::endl;

	return eGameStatus::quit;
}

static eBoardMaps		loadNextLevel (eBoardMaps currentLevel)
{
	switch (currentLevel)
	{
		case eBoardMaps::Square:
			return eBoardMaps::Open;
		case eBoardMaps::Open:
			return eBoardMaps::Square;
		default:
			throw ShouldNeverOccurException (__FILE__, __LINE__);
	}
}

static void				startNibbler (nibblerParametersPointer nibblerParams)
{
	Board *board;
	Snake *snakeP1, *snakeP2;
	guiFuncStruct guiFunc;
	IGUI *GUI;
	unsigned int p1InitPosX, p1IinitPosY, p2InitPosX, p2IinitPosY;
	eGUI currentGUI;
	eBoardMaps currentMap;
	eGameStatus gameStatus;
	bool running;

	std::cout << "startNibbler BEGIN" << std::endl;

	board = new Board();
	if (! board)
		throw ShouldNeverOccurException (__FILE__, __LINE__);

	snakeP1 = new Snake ();
	if (! snakeP1)
		throw ShouldNeverOccurException (__FILE__, __LINE__);

	if (nibblerParams->multiplayer)
	{
		snakeP2 = new Snake ();
		if (! snakeP1)
			throw ShouldNeverOccurException (__FILE__, __LINE__);
	}
	else
		snakeP2 = NULL;

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

	currentMap = nibblerParams->selectedMap;

	openGUILibrary (eGUI::SDL, &guiFunc);
	GUI = guiFunc.createGUI (board, snakeP1, snakeP2);

	running = true;
	while (running)
	{
		board->initBoard (nibblerParams->width, nibblerParams->height, nibblerParams->multiplayer, nibblerParams->friendlyFire);

		snakeP1->initSnake (p1InitPosX, p1IinitPosY, 4u, eSnakeDirection::East, true /* canPassThroughWall */);
		if (nibblerParams->multiplayer)
			snakeP2->initSnake (p2InitPosX, p2IinitPosY, 4u, eSnakeDirection::West, true /* canPassThroughWall */);

		board->initPlayers (snakeP1, snakeP2);
		board->loadMap (currentMap);

		if (! GUI->alreadyStarted())
			GUI->start();

		gameStatus = startGame (board, snakeP1, snakeP2, nibblerParams, &guiFunc, GUI);
		switch (gameStatus)
		{
			case eGameStatus::quit:
				running = false;
				break;

			case eGameStatus::finish:
				gameStatus = endGame (board, snakeP1, snakeP2, &guiFunc, GUI);
				switch (gameStatus)
				{
					case eGameStatus::restart:
						/* nothing to do */
						break;

					case eGameStatus::changeLevel:
						currentMap = loadNextLevel (currentMap);
						break;

					case eGameStatus::quit:
						running = false;
						break;

					default:
						throw ShouldNeverOccurException (__FILE__, __LINE__);
				}
				break;

					default:
				throw ShouldNeverOccurException (__FILE__, __LINE__);
		}

		board->clearBoard();
	}

	currentGUI = GUI->getGUIName();

	GUI->stop();
	guiFunc.destroyGUI (GUI);
	closeGUILibrary (currentGUI, &guiFunc);

	delete snakeP2;
	delete snakeP1;
	delete board;

	std::cout << "startNibbler END" << std::endl;
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
