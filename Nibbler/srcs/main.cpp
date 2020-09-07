#include <nibbler.hpp>

static bool				launchNibbler (Board *board, nibblerParametersPointer nibblerParams,
									   guiFuncStruct *guiFunc, IGUI* &GUI)
{
	eGUIMainMenuEvent currentEvent;
	eGUI currentGUI, wantedGUI;

	(void)nibblerParams;

	std::cout << "launchNibbler BEGIN" << std::endl;

	currentGUI = GUI->getGUIName();

	GUI->start();
	GUI->loadMainMenu();

	while (true)
	{
		currentEvent = GUI->getMainMenuEvent();
		switch (currentEvent)
		{
			case eGUIMainMenuEvent::startSinglePlayerGame:
				nibblerParams->multiplayer = false;
				std::cout << "launchNibbler END (startSinglePlayerGame)" << std::endl;
				return true;

			case eGUIMainMenuEvent::startMultiPlayerGame:
				nibblerParams->multiplayer = true;
				std::cout << "launchNibbler END (startMultiPlayerGame)" << std::endl;
				return true;

			case eGUIMainMenuEvent::changeGUI:
				std::cout << "==> Switch GUI <==" << std::endl;
				wantedGUI = GUI->wantedGUI();

				GUI->stop();
				guiFunc->destroyGUI (GUI);
				closeGUILibrary (currentGUI, guiFunc);

				openGUILibrary (wantedGUI, guiFunc);
				GUI = guiFunc->createGUI (board);
				GUI->start();
				GUI->loadMainMenu();

				currentGUI = wantedGUI;
				break;

			case eGUIMainMenuEvent::quitGame:
				std::cout << "launchNibbler END (quit)" << std::endl;
				return false;

			case eGUIMainMenuEvent::nothingTODO:
				break;

			default:
				throw UnknownEventException (GUI->getGUIName(), currentEvent);
		}
	}

	std::cout << "launchNibbler END (SNO)" << std::endl;

	return false;
}

static eGameStatus		startGame (Board *board, Snake *snakeP1, Snake *snakeP2,
								   nibblerParametersPointer nibblerParams,
								   guiFuncStruct *guiFunc, IGUI* &GUI)
{
	eGUIGameEvent currentEvent;
	eGUI currentGUI, wantedGUI;

	std::cout << "startGame BEGIN" << std::endl;

	currentGUI = GUI->getGUIName();
	while (true)
	{
		GUI->updateGameGUI();

		currentEvent = GUI->getGameEvent();
		switch (currentEvent)
		{
			case eGUIGameEvent::p1GoLeft:
				snakeP1->goLeft();
				break;
			case eGUIGameEvent::p1GoRight:
				snakeP1->goRight();
				break;
			case eGUIGameEvent::p1GoUp:
				snakeP1->goUp();
				break;
			case eGUIGameEvent::p1GoDown:
				snakeP1->goDown();
				break;
			case eGUIGameEvent::p2GoLeft:
				if (nibblerParams->multiplayer)
					snakeP2->goLeft();
				else
					throw UnknownEventException (currentGUI, currentEvent);
				break;
			case eGUIGameEvent::p2GoRight:
				if (nibblerParams->multiplayer)
					snakeP2->goRight();
				else
					throw UnknownEventException (currentGUI, currentEvent);
				break;
			case eGUIGameEvent::p2GoUp:
				if (nibblerParams->multiplayer)
					snakeP2->goUp();
				else
					throw UnknownEventException (currentGUI, currentEvent);
				break;
			case eGUIGameEvent::p2GoDown:
				if (nibblerParams->multiplayer)
					snakeP2->goDown();
				else
					throw UnknownEventException (currentGUI, currentEvent);
				break;
			case eGUIGameEvent::changeGUI:
				std::cout << "==> Switch GUI <==" << std::endl;
				wantedGUI = GUI->wantedGUI();

				GUI->stop();
				guiFunc->destroyGUI (GUI);
				closeGUILibrary (currentGUI, guiFunc);

				openGUILibrary (wantedGUI, guiFunc);
				GUI = guiFunc->createGUI (board);
				guiFunc->setPlayers (GUI, snakeP1, snakeP2);
				GUI->start();

				currentGUI = wantedGUI;
				break;
			case eGUIGameEvent::nothingTODO:
				break;
			case eGUIGameEvent::quitGame:
				std::cout << "startGame END (Quit)" << std::endl;
				return eGameStatus::quit;
			default:
				throw UnknownEventException (GUI->getGUIName(), currentEvent);
		}

		board->runTurn();

		if (! board->snakesAreAlive())
		{
			std::cout << "startGame END (Finish Dead Snake)" << std::endl;
			return eGameStatus::finish;
		}

		if (board->boardIsCompleted())
		{
			std::cout << "startGame END (Finish Completed Board)" << std::endl;
			return eGameStatus::finish;
		}
	}

	std::cout << "startGame END (UnknownStatus)" << std::endl;

	return eGameStatus::UnknownStatus;
}

static eGameStatus		endGame (Board *board, Snake *snakeP1, Snake *snakeP2,
								 guiFuncStruct *guiFunc, IGUI* &GUI)
{
	eGUIEndMenuEvent currentEvent;
	eGUI currentGUI, wantedGUI;

	std::cout << "endGame BEGIN" << std::endl;

	currentGUI = GUI->getGUIName();

	GUI->loadEndMenu();

	while (true)
	{
		currentEvent = GUI->getEndMenuEvent();
		switch (currentEvent)
		{
			case eGUIEndMenuEvent::changeGUI:
				std::cout << "==> Switch GUI <=="  << std::endl;
				wantedGUI = GUI->wantedGUI();

				GUI->stop();
				guiFunc->destroyGUI (GUI);
				closeGUILibrary (currentGUI, guiFunc);

				openGUILibrary (wantedGUI, guiFunc);
				GUI = guiFunc->createGUI (board);
				guiFunc->setPlayers (GUI, snakeP1, snakeP2);
				GUI->start();

				currentGUI = wantedGUI;
				break;

			case eGUIEndMenuEvent::restartLevel:
				std::cout << "endGame END (restart)" << std::endl;
				return eGameStatus::restart;

			case eGUIEndMenuEvent::nextLevel:
				std::cout << "endGame END (changeLevel)" << std::endl;
				return eGameStatus::changeLevel;

			case eGUIEndMenuEvent::quitGame:
				std::cout << "endGame END (quit)" << std::endl;
				return eGameStatus::quit;

			case eGUIEndMenuEvent::nothingTODO:
				break;

			default:
				throw UnknownEventException (GUI->getGUIName(), currentEvent);
		}
	}

	std::cout << "endGame END (SNO)" << std::endl;

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

	currentMap = nibblerParams->selectedMap;

	openGUILibrary (eGUI::SDL, &guiFunc);
	GUI = guiFunc.createGUI (board);

	board->initBoard (nibblerParams->width, nibblerParams->height);

	running = launchNibbler (board, nibblerParams, &guiFunc, GUI);

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

	guiFunc.setPlayers (GUI, snakeP1, snakeP2);

	while (running)
	{
		snakeP1->initSnake (p1InitPosX, p1IinitPosY, 4u, eSnakeDirection::East, true /* canPassThroughWall */);
		if (nibblerParams->multiplayer)
			snakeP2->initSnake (p2InitPosX, p2IinitPosY, 4u, eSnakeDirection::West, true /* canPassThroughWall */);

		board->initPlayers (snakeP1, snakeP2, nibblerParams->multiplayer, nibblerParams->friendlyFire);
		board->loadMap (currentMap);

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
		board->initBoard (nibblerParams->width, nibblerParams->height);
	}

	currentGUI = GUI->getGUIName();
	GUI->stop();
	guiFunc.destroyGUI (GUI);
	closeGUILibrary (currentGUI, &guiFunc);

	if (snakeP2 != NULL)
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

				if (strcmp ("friendlyfire:on", av[3]) && strcmp ("friendlyfire:off", av[3]))
				{
					std::cerr << "Invalid friendlyFire parameters. friendlyFire:on || friendlyFire:off (" << av[3] << ")." << std::endl;
					exit (0);
				}

				nibblerParams.friendlyFire = ! strcmp ("friendlyfire:on", av[3]) ? true : false;

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
