#include <nibbler.hpp>

static bool				launchNibbler (Board *board, nibblerParametersPointer nibblerParams,
									   guiFuncStruct *guiFunc, IGUI* &GUI)
{
	eGUIMainMenuEvent currentEvent;
	eGUI currentGUI, wantedGUI;

	print_trace ("launchNibbler BEGIN", true);

	currentGUI = GUI->getGUIName();

	GUI->loadMainMenu();

	while (true)
	{
		currentEvent = GUI->getMainMenuEvent();
		switch (currentEvent)
		{
			case eGUIMainMenuEvent::startSinglePlayerGame:
				board->setMultiPlayerMode (false);
				nibblerParams->boardMode = static_cast<eboardMode>
										   (nibblerParams->boardMode & ~eboardMode::Multiplayer);
				print_trace ("launchNibbler END (startSinglePlayerGame)", true);
				return true;

			case eGUIMainMenuEvent::startMultiPlayerGame:
				board->setMultiPlayerMode (true);
				nibblerParams->boardMode = static_cast<eboardMode>
										   (nibblerParams->boardMode | eboardMode::Multiplayer);
				print_trace ("launchNibbler END (startMultiPlayerGame)", true);
				return true;

			case eGUIMainMenuEvent::changeGUI:
				print_trace ("==> Switch GUI <==", true);
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
				print_trace ("launchNibbler END (quit)", true);
				return false;

			case eGUIMainMenuEvent::nothingTODO:
				break;

			default:
				throw UnknownEventException (eGUIString (GUI->getGUIName()), eGUIMainMenuEventString (currentEvent));
		}
	}

	print_trace ("launchNibbler END (SNO)", true);

	return false;
}

static bool				selectMap (Board *board, guiFuncStruct *guiFunc, IGUI* &GUI,
								   eBoardMaps *selectedMap)
{
	eGUIMapSelectionEvent currentEvent;
	eGUI currentGUI, wantedGUI;

	print_trace ("selectMap BEGIN", true);

	currentGUI = GUI->getGUIName();

	GUI->loadMapSelection();

	while (true)
	{
		currentEvent = GUI->getMapSelectionEvent();
		switch (currentEvent)
		{
			case eGUIMapSelectionEvent::mapLT:
				*selectedMap = eBoardMaps::Classic;
				print_trace ("selectMap END (mapLeftTop)", true);
				return true;

			case eGUIMapSelectionEvent::mapLM:
				*selectedMap = eBoardMaps::Borderless;
				print_trace ("selectMap END (mapLeftMiddle)", true);
				return true;

			case eGUIMapSelectionEvent::mapLB:
				*selectedMap = eBoardMaps::Tribal;
				print_trace ("selectMap END (mapLeftBottom)", true);
				return true;

			case eGUIMapSelectionEvent::mapCT:
				*selectedMap = eBoardMaps::Lines;
				print_trace ("selectMap END (mapCenterTop)", true);
				return true;

			case eGUIMapSelectionEvent::mapCM:
				*selectedMap = eBoardMaps::LinesBorderless;
				print_trace ("selectMap END (mapCenterMiddle)", true);
				return true;

			case eGUIMapSelectionEvent::mapCB:
				*selectedMap = eBoardMaps::LinesTribal;
				print_trace ("selectMap END (mapCenterBottom)", true);
				return true;

			case eGUIMapSelectionEvent::mapRT:
				*selectedMap = eBoardMaps::Blocks;
				print_trace ("selectMap END (mapRightTop)", true);
				return true;

			case eGUIMapSelectionEvent::mapRM:
				*selectedMap = eBoardMaps::BlocksBorderless;
				print_trace ("selectMap END (mapRightMiddle)", true);
				return true;

			case eGUIMapSelectionEvent::mapRB:
				*selectedMap = eBoardMaps::BlocksTribal;
				print_trace ("selectMap END (mapRightBottom)", true);
				return true;

			case eGUIMapSelectionEvent::changeGUI:
				print_trace ("==> Switch GUI <==", true);
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
				print_trace ("launchNibbler END (quit)", true);
				return false;

			case eGUIMapSelectionEvent::nothingTODO:
				break;

			default:
				throw UnknownEventException (eGUIString (GUI->getGUIName()), eGUIMapSelectionEventString (currentEvent));
		}
	}

	print_trace ("selectMap END (SNO)", true);

	return false;
}

static eGameStatus		startGame (Board *board, Snake *snakeP1, Snake *snakeP2,
								   unsigned int soundTrack,
								   nibblerParametersPointer nibblerParams,
								   guiFuncStruct *guiFunc, IGUI* &GUI)
{
	eGUIGameEvent currentEvent;
	eGUI currentGUI, wantedGUI;

	print_trace ("startGame BEGIN", true);

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
				if (nibblerParams->boardMode & eboardMode::Multiplayer)
					snakeP2->goLeft();
				else
					throw UnknownEventException (eGUIString (GUI->getGUIName()), eGUIGameEventString (currentEvent));
				break;
			case eGUIGameEvent::p2GoRight:
				if (nibblerParams->boardMode & eboardMode::Multiplayer)
					snakeP2->goRight();
				else
					throw UnknownEventException (eGUIString (GUI->getGUIName()), eGUIGameEventString (currentEvent));
				break;
			case eGUIGameEvent::p2GoUp:
				if (nibblerParams->boardMode & eboardMode::Multiplayer)
					snakeP2->goUp();
				else
					throw UnknownEventException (eGUIString (GUI->getGUIName()), eGUIGameEventString (currentEvent));
				break;
			case eGUIGameEvent::p2GoDown:
				if (nibblerParams->boardMode & eboardMode::Multiplayer)
					snakeP2->goDown();
				else
					throw UnknownEventException (eGUIString (GUI->getGUIName()), eGUIGameEventString (currentEvent));
				break;
			case eGUIGameEvent::changeGUI:
				print_trace ("==> Switch GUI <==", true);
				wantedGUI = GUI->wantedGUI();

				GUI->stop();
				guiFunc->destroyGUI (GUI);
				closeGUILibrary (currentGUI, guiFunc);

				openGUILibrary (wantedGUI, guiFunc);
				GUI = guiFunc->createGUI (board);
				GUI->start();
				GUI->setPlayers (snakeP1, snakeP2);
				GUI->loadBoard (soundTrack);

				currentGUI = wantedGUI;
				break;
			case eGUIGameEvent::forfeitGame:
				print_trace ("startGame END (Forfeit)", true);
				board->forfeitBoard();
				return eGameStatus::finish;
			case eGUIGameEvent::nothingTODO:
				break;
			case eGUIGameEvent::quitGame:
				print_trace ("startGame END (Quit)", true);
				return eGameStatus::quit;
			default:
				throw UnknownEventException (eGUIString (GUI->getGUIName()), eGUIGameEventString (currentEvent));
		}

		board->runTurn();

		if (! board->snakesAreAlive())
		{
			print_trace ("startGame END (Finish Dead Snake)", true);
			return eGameStatus::finish;
		}

		if (board->boardIsCompleted())
		{
			print_trace ("startGame END (Finish Completed Board)", true);
			return eGameStatus::finish;
		}
	}

	print_trace ("startGame END (UnknownStatus)", true);

	return eGameStatus::UnknownStatus;
}

static eGameStatus		endGame (Board *board, Snake *snakeP1, Snake *snakeP2,
								 guiFuncStruct *guiFunc, IGUI* &GUI)
{
	eGUIEndMenuEvent currentEvent;
	eGUI currentGUI, wantedGUI;

	print_trace ("endGame BEGIN", true);

	currentGUI = GUI->getGUIName();

	GUI->loadEndMenu();

	while (true)
	{
		currentEvent = GUI->getEndMenuEvent();
		switch (currentEvent)
		{
			case eGUIEndMenuEvent::changeGUI:
				print_trace ("==> Switch GUI <==", true);
				wantedGUI = GUI->wantedGUI();

				GUI->stop();
				guiFunc->destroyGUI (GUI);
				closeGUILibrary (currentGUI, guiFunc);

				openGUILibrary (wantedGUI, guiFunc);
				GUI = guiFunc->createGUI (board);
				GUI->start();
				GUI->setPlayers (snakeP1, snakeP2);
				GUI->loadEndMenu();

				currentGUI = wantedGUI;
				break;

			case eGUIEndMenuEvent::restartLevel:
				print_trace ("endGame END (restart)", true);
				return eGameStatus::restart;

			case eGUIEndMenuEvent::nextLevel:
				print_trace ("endGame END (changeLevel)", true);
				return eGameStatus::changeLevel;

			case eGUIEndMenuEvent::backToLobby:
				print_trace ("endGame END (backToLobby)", true);
				return eGameStatus::backMainMenu;

			case eGUIEndMenuEvent::quitGame:
				print_trace ("endGame END (quit)", true);
				return eGameStatus::quit;

			case eGUIEndMenuEvent::nothingTODO:
				break;

			default:
				throw UnknownEventException (eGUIString (GUI->getGUIName()), eGUIEndMenuEventString (currentEvent));
		}
	}

	print_trace ("endGame END (SNO)", true);

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

	print_trace ("startNibbler BEGIN", true);

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

		if (nibblerParams->boardMode & eboardMode::Multiplayer)
			snakeP2 = save_snakeP2;
		else
			snakeP2 = NULL;

		if (! selectMap (board, &guiFunc, GUI, &currentMap))
			break;

		soundTrack = selectSoundTrack (currentMap);
		GUI->setPlayers (snakeP1, snakeP2);

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

	print_trace ("startNibbler END", true);
}

int main (int ac, char **av)
{
	std::string validParameters ("--help|-c|--commands|-e|--endless|--nff|--nofriendlyfire|--no-friendly-fire|-s|--specialfood|--special-food");
	nibblerParametersStruct nibblerParams;
	unsigned int param, i;

	/* default */
	nibblerParams.width = 40u;
	nibblerParams.height = 40u;
	nibblerParams.boardMode = eboardMode::Default;

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

				if ((validParameters.find (av[1]) == 7) ||
					(validParameters.find (av[1]) == 10))
				{
					std::cout << std::ifstream ("COMMANDS").rdbuf();
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

				if ((validParameters.find (av[2]) == 7) ||
					(validParameters.find (av[2]) == 10))
				{
					std::cout << std::ifstream ("COMMANDS").rdbuf();
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
							std::cout << std::ifstream ("COMMANDS").rdbuf();
							return 0;
						case 21:
						case 24:
							nibblerParams.boardMode = static_cast<eboardMode>
													  (nibblerParams.boardMode | eboardMode::Endless);
							break;
						case 34:
						case 40:
						case 57:
							nibblerParams.boardMode = static_cast<eboardMode>
													  (nibblerParams.boardMode | eboardMode::NoFriendlyFire);
							break;
						case 76:
						case 79:
						case 93:
							nibblerParams.boardMode = static_cast<eboardMode>
													  (nibblerParams.boardMode | eboardMode::SpecialFood);
							break;
						default:
		 					std::cerr << "nibbler: invalid option '" << av[i] << "'" << std::endl;
		 					std::cerr << "Try './nibbler --help' for more information." << std::endl;
							exit (0);
					}
				}

				startNibbler (&nibblerParams);
			}
			catch (std::invalid_argument &e)
			{
				std::cerr << "nibbler: invalid width or height value" << std::endl;
				std::cerr << "Try './nibbler --help' for more information." << std::endl;
				exit (0);
			}
			catch (std::exception &e)
			{
				std::cerr << "Error : " << e.what() << std::endl;
				exit (0);
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
