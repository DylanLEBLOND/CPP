#include <nibbler.hpp>

static bool				launchNibbler (Board *board, nibblerParametersPointer nibblerParams,
									   guiFuncStruct *guiFunc, IGUI* &GUI)
{
	eGUIMainMenuEvent currentEvent;
	eGUI currentGUI, wantedGUI;

	std::cout << "launchNibbler BEGIN" << std::endl;

	currentGUI = GUI->getGUIName();

	GUI->loadMainMenu();

	while (true)
	{
		currentEvent = GUI->getMainMenuEvent();
		switch (currentEvent)
		{
			case eGUIMainMenuEvent::startSinglePlayerGame:
				board->setMultiPlayerMode (false);
				nibblerParams->boardMode = static_cast<eboadMode>
										   (nibblerParams->boardMode & ~eboadMode::Multiplayer);
				std::cout << "launchNibbler END (startSinglePlayerGame)" << std::endl;
				return true;

			case eGUIMainMenuEvent::startMultiPlayerGame:
				board->setMultiPlayerMode (true);
				nibblerParams->boardMode = static_cast<eboadMode>
										   (nibblerParams->boardMode | eboadMode::Multiplayer);
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

static bool				selectMap (Board *board, guiFuncStruct *guiFunc, IGUI* &GUI,
								   eBoardMaps *selectedMap)
{
	eGUIMapSelectionEvent currentEvent;
	eGUI currentGUI, wantedGUI;

	std::cout << "selectMap BEGIN" << std::endl;

	currentGUI = GUI->getGUIName();

	GUI->loadMapSelection();

	while (true)
	{
		currentEvent = GUI->getMapSelectionEvent();
		switch (currentEvent)
		{
			case eGUIMapSelectionEvent::mapLT:
				*selectedMap = eBoardMaps::Classic;
				std::cout << "selectMap END (mapLeftTop)" << std::endl;
				return true;

			case eGUIMapSelectionEvent::mapLM:
				*selectedMap = eBoardMaps::Borderless;
				std::cout << "selectMap END (mapLeftMiddle)" << std::endl;
				return true;

			case eGUIMapSelectionEvent::mapLB:
				*selectedMap = eBoardMaps::Tribal;
				std::cout << "selectMap END (mapLeftBottom)" << std::endl;
				return true;

			case eGUIMapSelectionEvent::mapCT:
				*selectedMap = eBoardMaps::Lines;
				std::cout << "selectMap END (mapCenterTop)" << std::endl;
				return true;

			case eGUIMapSelectionEvent::mapCM:
				*selectedMap = eBoardMaps::LinesBorderless;
				std::cout << "selectMap END (mapCenterMiddle)" << std::endl;
				return true;

			case eGUIMapSelectionEvent::mapCB:
				*selectedMap = eBoardMaps::LinesTribal;
				std::cout << "selectMap END (mapCenterBottom)" << std::endl;
				return true;

			case eGUIMapSelectionEvent::mapRT:
				*selectedMap = eBoardMaps::Blocks;
				std::cout << "selectMap END (mapRightTop)" << std::endl;
				return true;

			case eGUIMapSelectionEvent::mapRM:
				*selectedMap = eBoardMaps::BlocksBorderless;
				std::cout << "selectMap END (mapRightMiddle)" << std::endl;
				return true;

			case eGUIMapSelectionEvent::mapRB:
				*selectedMap = eBoardMaps::BlocksTribal;
				std::cout << "selectMap END (mapRightBottom)" << std::endl;
				return true;

			case eGUIMapSelectionEvent::changeGUI:
				std::cout << "==> Switch GUI <==" << std::endl;
				wantedGUI = GUI->wantedGUI();

				GUI->stop();
				guiFunc->destroyGUI (GUI);
				closeGUILibrary (currentGUI, guiFunc);

				openGUILibrary (wantedGUI, guiFunc);
				GUI = guiFunc->createGUI (board);
				GUI->start();
				GUI->loadMapSelection();

				currentGUI = wantedGUI;
				break;

			case eGUIMapSelectionEvent::quitGame:
				std::cout << "launchNibbler END (quit)" << std::endl;
				return false;

			case eGUIMapSelectionEvent::nothingTODO:
				break;

			default:
				throw UnknownEventException (GUI->getGUIName(), currentEvent);
		}
	}

	std::cout << "selectMap END (SNO)" << std::endl;

	return false;
}

static eGameStatus		startGame (Board *board, Snake *snakeP1, Snake *snakeP2,
								   unsigned int soundTrack,
								   nibblerParametersPointer nibblerParams,
								   guiFuncStruct *guiFunc, IGUI* &GUI)
{
	eGUIGameEvent currentEvent;
	eGUI currentGUI, wantedGUI;

	std::cout << "startGame BEGIN" << std::endl;

	currentGUI = GUI->getGUIName();

	GUI->loadBoard (soundTrack);

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
				if (nibblerParams->boardMode & eboadMode::Multiplayer)
					snakeP2->goLeft();
				else
					throw UnknownEventException (currentGUI, currentEvent);
				break;
			case eGUIGameEvent::p2GoRight:
				if (nibblerParams->boardMode & eboadMode::Multiplayer)
					snakeP2->goRight();
				else
					throw UnknownEventException (currentGUI, currentEvent);
				break;
			case eGUIGameEvent::p2GoUp:
				if (nibblerParams->boardMode & eboadMode::Multiplayer)
					snakeP2->goUp();
				else
					throw UnknownEventException (currentGUI, currentEvent);
				break;
			case eGUIGameEvent::p2GoDown:
				if (nibblerParams->boardMode & eboadMode::Multiplayer)
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
				GUI->loadBoard (soundTrack);

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
				GUI->loadEndMenu();

				currentGUI = wantedGUI;
				break;

			case eGUIEndMenuEvent::restartLevel:
				std::cout << "endGame END (restart)" << std::endl;
				return eGameStatus::restart;

			case eGUIEndMenuEvent::nextLevel:
				std::cout << "endGame END (changeLevel)" << std::endl;
				return eGameStatus::changeLevel;

			case eGUIEndMenuEvent::backToLobby:
				std::cout << "endGame END (backToLobby)" << std::endl;
				return eGameStatus::backMainMenu;

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
		case eBoardMaps::Classic:
			return eBoardMaps::Lines;

		case eBoardMaps::Lines:
			return eBoardMaps::Blocks;

		case eBoardMaps::Blocks:
			return eBoardMaps::Borderless;

		case eBoardMaps::Borderless:
			return eBoardMaps::LinesBorderless;

		case eBoardMaps::LinesBorderless:
			return eBoardMaps::BlocksBorderless;

		case eBoardMaps::BlocksBorderless:
			return eBoardMaps::Tribal;

		case eBoardMaps::Tribal:
			return eBoardMaps::LinesTribal;

		case eBoardMaps::LinesTribal:
			return eBoardMaps::BlocksTribal;

		case eBoardMaps::BlocksTribal:
			return eBoardMaps::Classic;

		default:
			throw ShouldNeverOccurException (__FILE__, __LINE__);
	}
}

static unsigned int		selectSoundTrack (eBoardMaps currentLevel)
{
	switch (currentLevel)
	{
		case eBoardMaps::Classic:
		case eBoardMaps::Borderless:
		case eBoardMaps::Tribal:
			return 0;

		case eBoardMaps::Lines:
		case eBoardMaps::LinesBorderless:
		case eBoardMaps::LinesTribal:
			return 1;

		case eBoardMaps::Blocks:
		case eBoardMaps::BlocksBorderless:
		case eBoardMaps::BlocksTribal:
			return 2;

		default:
			throw ShouldNeverOccurException (__FILE__, __LINE__);
	}
}

static void				startNibbler (nibblerParametersPointer nibblerParams)
{
	Board *board;
	Snake *snakeP1, *snakeP2, *save_snakeP2;
	guiFuncStruct guiFunc;
	IGUI *GUI;
	eGUI currentGUI;
	eBoardMaps currentMap;
	unsigned int soundTrack;
	eGameStatus gameStatus;
	bool running, playing;

	std::cout << "startNibbler BEGIN" << std::endl;

	board = new Board();
	if (! board)
		throw ShouldNeverOccurException (__FILE__, __LINE__);

	snakeP1 = new Snake ();
	if (! snakeP1)
		throw ShouldNeverOccurException (__FILE__, __LINE__);

	save_snakeP2 = new Snake ();
	if (! save_snakeP2)
		throw ShouldNeverOccurException (__FILE__, __LINE__);

	openGUILibrary (eGUI::SDL, &guiFunc);
	GUI = guiFunc.createGUI (board);

	board->initBoard (nibblerParams->width, nibblerParams->height, nibblerParams->boardMode);

	GUI->start();

	running = true;
	while (running)
	{
		if (! launchNibbler (board, nibblerParams, &guiFunc, GUI))
			break;

		if (nibblerParams->boardMode & eboadMode::Multiplayer)
		{
			snakeP2 = save_snakeP2;
		}
		else
			snakeP2 = NULL;

		if (! selectMap (board, &guiFunc, GUI, &currentMap))
			break;

		soundTrack = selectSoundTrack (currentMap);
		guiFunc.setPlayers (GUI, snakeP1, snakeP2);

		playing = true;
		while (playing)
		{
			board->loadMap (currentMap);
			board->initPlayers (snakeP1, snakeP2);

			gameStatus = startGame (board, snakeP1, snakeP2, soundTrack, nibblerParams, &guiFunc, GUI);
			switch (gameStatus)
			{
				case eGameStatus::quit:
					playing = false;
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
							soundTrack = selectSoundTrack (currentMap);
							break;

						case eGameStatus::backMainMenu:
							playing = false;
							break;

						case eGameStatus::quit:
							playing = false;
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

			board->initBoard (nibblerParams->width, nibblerParams->height, nibblerParams->boardMode);
		}
	}

	currentGUI = GUI->getGUIName();
	GUI->stop();
	guiFunc.destroyGUI (GUI);
	closeGUILibrary (currentGUI, &guiFunc);

	delete save_snakeP2;
	delete snakeP1;
	delete board;

	std::cout << "startNibbler END" << std::endl;
}

int main (int ac, char **av)
{
	std::string validParameters ("--help|-e|--endless|--nff|--nofriendlyfire|--no-friendly-fire|-s|--specialfood|--special-food");
	nibblerParametersStruct nibblerParams;
	unsigned int param, i;

	/* default */
	nibblerParams.width = 40u;
	nibblerParams.height = 40u;
	nibblerParams.boardMode = eboadMode::Default;

	switch (ac)
	{
		case 1:
			std::cerr << "nibbler: too few parameters" << std::endl;
			std::cerr << "Try './nibbler --help' for more information." << std::endl;
			exit (0);
			break;
		case 2 ... 10:
			try
			{
				if (validParameters.find (av[1]) == 0)
				{
					std::cout << std::ifstream ("README").rdbuf();
					return 0;
				}

				nibblerParams.width = std::stoi (av[1]);
				if (nibblerParams.width < 30 || 100 < nibblerParams.width)
				{
 					std::cerr << "nibbler: invalid width value '" << nibblerParams.width << "'" << std::endl;
 					std::cerr << "Try './nibbler --help' for more information." << std::endl;
					exit (0);
				}

				if (ac == 2)
				{
 					std::cerr << "nibbler: too few parameters" << std::endl;
 					std::cerr << "Try './nibbler --help' for more information." << std::endl;
					exit (0);
				}

				if (validParameters.find (av[2]) == 0)
				{
					std::cout << std::ifstream ("README").rdbuf();
					return 0;
				}

				nibblerParams.height = std::stoi (av[2]);
				if (nibblerParams.height < 30 || 100 < nibblerParams.height)
				{
 					std::cerr << "nibbler: invalid height value '" << nibblerParams.height << "'" << std::endl;
 					std::cerr << "Try './nibbler --help' for more information." << std::endl;
					exit (0);
				}

				for (i = 3; i < (unsigned int)ac; i++)
				{
					param = validParameters.find (av[i]);
					switch (param)
					{
						case 0:
							std::cout << std::ifstream ("README").rdbuf();
							return 0;
						case 7:
						case 10:
							nibblerParams.boardMode = static_cast<eboadMode>
													  (nibblerParams.boardMode | eboadMode::Endless);
							break;
						case 20:
						case 26:
						case 43:
							nibblerParams.boardMode = static_cast<eboadMode>
													  (nibblerParams.boardMode | eboadMode::NoFriendlyFire);
							break;
						case 62:
						case 65:
						case 79:
							nibblerParams.boardMode = static_cast<eboadMode>
													  (nibblerParams.boardMode | eboadMode::SpecialFood);
							break;
						default:
		 					std::cerr << "nibbler: invalid option '" << av[i] << "'" << std::endl;
		 					std::cerr << "Try './nibbler --help' for more information." << std::endl;
							exit (0);
					}
				}

				startNibbler (&nibblerParams);
			}
			catch (std::exception &e)
			{
				std::cerr << "Error : " << e.what() << std::endl;
			}
			break;
		default:
			std::cerr << "nibbler: too much parameters" << std::endl;
			std::cerr << "Try './nibbler --help' for more information." << std::endl;
			exit (0);
			break;
	}

	return 0;
}
