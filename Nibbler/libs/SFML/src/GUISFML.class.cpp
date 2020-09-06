#include <GUISFML.class.hpp>

static unsigned int _mapWidth;
static unsigned int _mapHeight;

/*
 * Constructors
 */
GUISFML::GUISFML (Board *board)
	: _board (board), _snakeP1 (NULL), _snakeP2 (NULL), _wantedGUI (eGUI::SFML),
	  _window (NULL),
//	  _boardRenderer (NULL), _mainMenuImage (NULL), _mainMenuTexture (NULL),
//	  _endMenuImage (NULL), _endMenuTexture (NULL),
	  _started (false)
{
	if (! board)
	{
		throw InvalidArgumentException ("GUISFML::GUISFML (Board *board, Snake *snake): board == null");
	}
//
//	if (SFML_Init (SFML_INIT_VIDEO))
//	{
//		throw GUIException (this->_GUIName, "SFML_Init");
//	}
//
//	if (! IMG_Init (IMG_INIT_PNG))
//	{
//		throw GUIException (this->_GUIName, "IMG_Init");
//	}

	this->_menuLeftButton.x = 50;
	this->_menuLeftButton.y = 600;
	this->_menuLeftButton.width = 400;
	this->_menuLeftButton.height = 100;

	this->_menuRightButton.x = 550;
	this->_menuRightButton.y = 600;
	this->_menuRightButton.width = 400;
	this->_menuRightButton.height = 100;

	this->_menuQuitButton.x = 300;
	this->_menuQuitButton.y = 750;
	this->_menuQuitButton.width = 400;
	this->_menuQuitButton.height = 100;
}

/*
 * Destructor
 */
GUISFML::~GUISFML (void)
{
//	if (this->_endMenuTexture != NULL)
//		SFML_DestroyTexture (this->_endMenuTexture);
//
//	if (this->_endMenuImage != NULL)
//		SFML_FreeSurface (this->_endMenuImage);
//
//	if (this->_mainMenuTexture != NULL)
//		SFML_DestroyTexture (this->_mainMenuTexture);
//
//	if (this->_mainMenuImage != NULL)
//		SFML_FreeSurface (this->_mainMenuImage);
//
//	if (this->_boardRenderer != NULL)
//		SFML_DestroyRenderer (this->_boardRenderer);

	if (this->_window != NULL)
		delete this->_window;

//	IMG_Quit();
//
//	SFML_Quit();
}

/*
 * Private
 */
void					GUISFML::ajustBounds (void)
{
	this->_menuLeftButton.x = this->_menuLeftButton.x * _mapWidth / 1000;
	this->_menuLeftButton.y = this->_menuLeftButton.y * _mapHeight / 1000;
	this->_menuLeftButton.width = this->_menuLeftButton.width * _mapWidth / 1000;
	this->_menuLeftButton.height = this->_menuLeftButton.height * _mapHeight / 1000;

	this->_menuRightButton.x = this->_menuRightButton.x * _mapWidth / 1000;
	this->_menuRightButton.y = this->_menuRightButton.y * _mapHeight / 1000;
	this->_menuRightButton.width = this->_menuRightButton.width * _mapWidth / 1000;
	this->_menuRightButton.height = this->_menuRightButton.height * _mapHeight / 1000;

	this->_menuQuitButton.x = this->_menuQuitButton.x * _mapWidth / 1000;
	this->_menuQuitButton.y = this->_menuQuitButton.y * _mapHeight / 1000;
	this->_menuQuitButton.width = this->_menuQuitButton.width * _mapWidth / 1000;
	this->_menuQuitButton.height = this->_menuQuitButton.height * _mapHeight / 1000;
}

void					GUISFML::drawMainMenu (void)
{
//	if (this->_mainMenuImage == NULL)
//	{
//		this->_mainMenuImage = IMG_Load ("res/images/main_menu.png");
//		if (this->_mainMenuImage == NULL)
//		{
//			throw GUIException (this->_GUIName, "IMG_Load GUISFML::drawMainMenu");
//		}
//	}
//
//	if (this->_mainMenuTexture == NULL)
//	{
//		this->_mainMenuTexture = SFML_CreateTextureFromSurface (this->_boardRenderer, this->_mainMenuImage);
//		if (this->_mainMenuTexture == NULL)
//		{
//			throw GUIException (this->_GUIName, "SFML_CreateTextureFromSurface GUISFML::drawMainMenu");
//		}
//	}
//
//	if (SFML_RenderCopy (this->_boardRenderer, this->_mainMenuTexture, NULL, NULL))
//	{
//		throw GUIException (this->_GUIName, "SFML_RenderCopy GUISFML::drawMainMenu");
//	}
}

void					GUISFML::drawBoard (void)
{
//	unsigned int height, width, y, x;
//	std::vector< std::vector<int> > *boardCells;
//	SFML_Rect boardCellDraw;
//	Uint8 r, g, b;
//
//	if (SFML_SetRenderDrawColor (this->_boardRenderer, 255, 255, 255, 255))
//	{
//		throw GUIException (this->_GUIName, "SFML_SetRenderDrawColor GUISFML::drawBoard");
//	}
//	if (SFML_RenderClear (this->_boardRenderer))		/* use the RenderDrawColor to clear the Renderer */
//	{
//		throw GUIException (this->_GUIName, "SFML_RenderClear GUISFML::drawBoard");
//	}
//
//	boardCells = this->_board->getBoardCells();
//	height = this->_board->getHeight();
//	width = this->_board->getWidth();
//
//	for (y = 0; y < height; y++)
//	{
//		for (x = 0; x < width; x++)
//		{
//			if (boardCells-> at (y).at (x) != 0)
//			{
//				switch (boardCells-> at (y).at (x))
//				{
//					case -1:
//						r = 0x00;
//						g = 0x00;
//						b = 0x00;
//						break;
//					case (int)eBonusValue::CommonValue:
//						r = 0xff;
//						g = 0xa5;
//						b = 0x00;
//						break;
//					case (int)eBonusValue::UncommonValue:
//						r = 0xff;
//						g = 0x00;
//						b = 0x00;
//						break;
//					case (int)eBonusValue::RareValue:
//						r = 0xff;
//						g = 0x00;
//						b = 0xff;
//						break;
//					case (int)eBonusValue::LegendaryValue:
//						r = 0x00;
//						g = 0x00;
//						b = 0xff;
//						break;
//					case (int)eBonusValue::GodlikeValue:
//						r = 0x33;
//						g = 0x33;
//						b = 0x33;
//						break;
//					default:
//						throw ShouldNeverOccurException (__FILE__, __LINE__);
//				}
//
//				if (SFML_SetRenderDrawColor (this->_boardRenderer, r, g, b, 255))
//				{
//					throw GUIException (this->_GUIName, "SFML_SetRenderDrawColor GUISFML::drawBoard");
//				}
//
//				boardCellDraw.x = x * 10;
//				boardCellDraw.y = y * 10;
//				boardCellDraw.w = 10;
//				boardCellDraw.h = 10;
//
//				if (SFML_RenderFillRect (this->_boardRenderer, &boardCellDraw))
//				{
//					throw GUIException (this->_GUIName, "SFML_RenderFillRect GUISFML::drawBoard");
//				}
//			}
//		}
//	}
}

void					GUISFML::drawSnakes (void)
{
//	std::list<t_cell> snakeCells;
//	std::list<t_cell>::iterator itSnakeCell;
//	SFML_Rect snakeCellDraw;
//
//	snakeCells = this->_snakeP1->getSnakeCells();
//
//	if (SFML_SetRenderDrawColor (this->_boardRenderer, 0, 255, 0, 255))
//	{
//		throw GUIException (this->_GUIName, "SFML_SetRenderDrawColor GUISFML::drawSnake P1");
//	}
//
//	for (itSnakeCell = snakeCells.begin(); itSnakeCell != snakeCells.end(); ++itSnakeCell)
//	{
//		snakeCellDraw.x = itSnakeCell->positionX * 10;
//		snakeCellDraw.y = itSnakeCell->positionY * 10;
//		snakeCellDraw.w = 10;
//		snakeCellDraw.h = 10;
//
//		if (SFML_RenderFillRect (this->_boardRenderer, &snakeCellDraw))
//		{
//			throw GUIException (this->_GUIName, "SFML_RenderFillRect GUISFML::drawSnake P1");
//		}
//	}
//
//	if (this->_snakeP2)
//	{
//		snakeCells = this->_snakeP2->getSnakeCells();
//
//		if (SFML_SetRenderDrawColor (this->_boardRenderer, 0, 255, 255, 255))
//		{
//			throw GUIException (this->_GUIName, "SFML_SetRenderDrawColor GUISFML::drawSnake P2");
//		}
//
//		for (itSnakeCell = snakeCells.begin(); itSnakeCell != snakeCells.end(); ++itSnakeCell)
//		{
//			snakeCellDraw.x = itSnakeCell->positionX * 10;
//			snakeCellDraw.y = itSnakeCell->positionY * 10;
//			snakeCellDraw.w = 10;
//			snakeCellDraw.h = 10;
//
//			if (SFML_RenderFillRect (this->_boardRenderer, &snakeCellDraw))
//			{
//				throw GUIException (this->_GUIName, "SFML_RenderFillRect GUISFML::drawSnake P2");
//			}
//		}
//	}
}

void					GUISFML::drawEndMenu (void)
{
//	if (this->_endMenuImage != NULL)
//		SFML_FreeSurface (this->_endMenuImage);
//
//	if (this->_snakeP1->isAlive())
//	{
//		if (this->_snakeP2)
//		{
//			if (this->_snakeP2->isAlive())
//				this->_endMenuImage = IMG_Load ("res/images/multiplayer_draw.png");
//			else
//				this->_endMenuImage = IMG_Load ("res/images/multiplayer_player1_win.png");
//		}
//		else
//			this->_endMenuImage = IMG_Load ("res/images/singleplayer_win.png");
//	}
//	else
//	{
//		if (this->_snakeP2)
//		{
//			if (this->_snakeP2->isAlive())
//				this->_endMenuImage = IMG_Load ("res/images/multiplayer_player2_win.png");
//			else
//				this->_endMenuImage = IMG_Load ("res/images/multiplayer_draw.png");
//		}
//		else
//			this->_endMenuImage = IMG_Load ("res/images/singleplayer_lose.png");
//	}
//
//	if (this->_endMenuImage == NULL)
//	{
//		throw GUIException (this->_GUIName, "IMG_Load GUISFML::drawEndMenu");
//	}
//
//	if (this->_endMenuTexture != NULL)
//		SFML_DestroyTexture (this->_endMenuTexture);
//
//	this->_endMenuTexture = SFML_CreateTextureFromSurface (this->_boardRenderer, this->_endMenuImage);
//	if (this->_endMenuTexture == NULL)
//	{
//		throw GUIException (this->_GUIName, "SFML_CreateTextureFromSurface GUISFML::drawEndMenu");
//	}
//
//	if (SFML_RenderCopy (this->_boardRenderer, this->_endMenuTexture, NULL, NULL))
//	{
//		throw GUIException (this->_GUIName, "SFML_RenderCopy GUISFML::drawEndMenu");
//	}
}

/*
 * Public
 */
eGUI					GUISFML::getGUIName (void) const
{
	return this->_GUIName;
}

void					GUISFML::start (void)
{
	_mapWidth = this->_board->getWidth() * 10;
	_mapHeight = this->_board->getHeight() * 10;

#ifdef PROJ_DEBUG
	std::cout << "GUISFML::start" << std::endl;
#endif

	this->_window = new sf::RenderWindow (sf::VideoMode (_mapWidth, _mapHeight), "Nibbler (SFML GUI)");
	if (this->_window == NULL)
	{
		throw GUIException (this->_GUIName, "sf::RenderWindow");
	}

//	this->_boardRenderer = SFML_CreateRenderer (this->_window, -1, SFML_RENDERER_ACCELERATED);
//	if (this->_boardRenderer == NULL)
//	{
//		throw GUIException (this->_GUIName, "SFML_CreateRenderer");
//	}

	this->ajustBounds ();

	this->_started = true;
}

bool					GUISFML::alreadyStarted (void) const
{
	return this->_started;
}

eGUI					GUISFML::wantedGUI (void) const
{
	return this->_wantedGUI;
}

void					GUISFML::stop()
{
#ifdef PROJ_DEBUG
	std::cout << "GUISFML::stop" << std::endl;
#endif

	if (this->_window == NULL)
	{
		throw GUIException (this->_GUIName, "GUISFML::stop => GUISFML wasn't started");
	}

	this->_window->close();
	delete this->_window;
	this->_window = NULL;		/* required */

	this->_started = false;
}

/* Main Menu */

void					GUISFML::loadMainMenu (void)
{
	this->drawMainMenu();

	this->_window->display();
}

eGUIMainMenuEvent		GUISFML::getMainMenuEvent (void)
{
	sf::Event events;
//	int x, y;

	while (this->_window->pollEvent (events))
	{
		if (events.type == sf::Event::Closed)
				return eGUIMainMenuEvent::quitGame;
//		else if (events.type == SFML_KEYDOWN)
//		{
//			switch (events.key.keysym.sym)
//			{
//				/* GUI Switchs */
//				case SFMLK_KP_2:
//				case SFMLK_2:
//					this-> _wantedGUI = eGUI::Ncurses;
//					return eGUIMainMenuEvent::changeGUI;
//
//				case SFMLK_KP_3:
//				case SFMLK_3:
//					this-> _wantedGUI = eGUI::openGL;
//					return eGUIMainMenuEvent::changeGUI;
//
//				case SFMLK_ESCAPE:
//					return eGUIMainMenuEvent::quitGame;
//
//				default:
//					return eGUIMainMenuEvent::nothingTODO;
//			}
//		}
//		else if (events.type == SFML_MOUSEBUTTONUP && SFML_BUTTON (SFML_BUTTON_LEFT))
//		{
//			SFML_GetMouseState (&x, &y);
//			if (this->_menuLeftButton.in (x, y))
//				return eGUIMainMenuEvent::startSinglePlayerGame;
//			else if (this->_menuRightButton.in (x, y))
//				return eGUIMainMenuEvent::startMultiPlayerGame;
//			else if (this->_menuQuitButton.in (x, y))
//				return eGUIMainMenuEvent::quitGame;
//		}
	}

	return eGUIMainMenuEvent::nothingTODO;
}

/* Game */

void					GUISFML::setPlayers (Snake *snakeP1, Snake *snakeP2)
{
	if (! snakeP1)
	{
		throw InvalidArgumentException ("GUISFML::setPlayers: snakeP1 == null");
	}

	this->_snakeP1 = snakeP1;
	this->_snakeP2 = snakeP2;
}

void					GUISFML::updateGameGUI (void)
{
	unsigned int currentGlobalScore;

//	if (! this->_snakeP1->getIsAlive())
//		return;
//	if (this->_snakeP2 && ! this->_snakeP2->getIsAlive())
//		return;

	this->drawBoard();
	this->drawSnakes();

	this->_window->display();

	currentGlobalScore = this->_snakeP1->getScore();
	if (this->_snakeP2)
		currentGlobalScore = currentGlobalScore > this->_snakeP2->getScore() ? currentGlobalScore : this->_snakeP2->getScore();

	if (currentGlobalScore > 95)
		currentGlobalScore = 95;

//	SFML_Delay (100 - currentGlobalScore);
}

eGUIGameEvent			GUISFML::getGameEvent (void)
{
	sf::Event events;

	while (this->_window->pollEvent (events))
	{
		if (events.type == sf::Event::Closed)
				return eGUIGameEvent::quitGame;
//		else if (events.type == SFML_KEYDOWN)
//		{
//			switch (events.key.keysym.sym)
//			{
//				case SFMLK_e:
//					this->_snakeP1->eat (1);
//					break;
//
//				/* Player 1 commands */
//				case SFMLK_LEFT:
//					return eGUIGameEvent::p1GoLeft;
//
//				case SFMLK_RIGHT:
//					return eGUIGameEvent::p1GoRight;
//
//				case SFMLK_UP:
//					return eGUIGameEvent::p1GoUp;
//
//				case SFMLK_DOWN:
//					return eGUIGameEvent::p1GoDown;
//
//				/* Player 2 commands */
//				case SFMLK_q:
//					if (this->_snakeP2)
//						return eGUIGameEvent::p2GoLeft;
//					return eGUIGameEvent::nothingTODO;
//
//				case SFMLK_d:
//					if (this->_snakeP2)
//						return eGUIGameEvent::p2GoRight;
//					return eGUIGameEvent::nothingTODO;
//
//				case SFMLK_z:
//					if (this->_snakeP2)
//						return eGUIGameEvent::p2GoUp;
//					return eGUIGameEvent::nothingTODO;
//
//				case SFMLK_s:
//					if (this->_snakeP2)
//						return eGUIGameEvent::p2GoDown;
//					return eGUIGameEvent::nothingTODO;
//
//				/* GUI Switchs */
//				case SFMLK_KP_2:
//				case SFMLK_2:
//					this-> _wantedGUI = eGUI::Ncurses;
//					return eGUIGameEvent::changeGUI;
//
//				case SFMLK_KP_3:
//				case SFMLK_3:
//					this-> _wantedGUI = eGUI::openGL;
//					return eGUIGameEvent::changeGUI;
//
//				case SFMLK_ESCAPE:
//					return eGUIGameEvent::quitGame;
//
//				default:
//					return eGUIGameEvent::nothingTODO;
//			}
//		}
	}

	return eGUIGameEvent::nothingTODO;
}

/* End Menu */

void					GUISFML::loadEndMenu (void)
{
	this->drawEndMenu();

	this->_window->display();
}

eGUIEndMenuEvent		GUISFML::getEndMenuEvent (void)
{
	sf::Event events;
//	int x, y;

	while (this->_window->pollEvent (events))
	{
		if (events.type == sf::Event::Closed)
				return eGUIEndMenuEvent::quitGame;
//		else if (events.type == SFML_KEYDOWN)
//		{
//			switch (events.key.keysym.sym)
//			{
//				/* GUI Switchs */
//				case SFMLK_KP_2:
//				case SFMLK_2:
//					this-> _wantedGUI = eGUI::Ncurses;
//					return eGUIEndMenuEvent::changeGUI;
//
//				case SFMLK_KP_3:
//				case SFMLK_3:
//					this-> _wantedGUI = eGUI::openGL;
//					return eGUIEndMenuEvent::changeGUI;
//
//				case SFMLK_ESCAPE:
//					return eGUIEndMenuEvent::quitGame;
//
//				default:
//					return eGUIEndMenuEvent::nothingTODO;
//			}
//		}
//		else if (events.type == SFML_MOUSEBUTTONUP && SFML_BUTTON (SFML_BUTTON_LEFT))
//		{
//			SFML_GetMouseState (&x, &y);
//			if (this->_menuLeftButton.in (x, y))
//				return eGUIEndMenuEvent::restartLevel;
//			else if (this->_menuRightButton.in (x, y))
//				return eGUIEndMenuEvent::nextLevel;
//			else if (this->_menuQuitButton.in (x, y))
//				return eGUIEndMenuEvent::quitGame;
//		}
	}

	return eGUIEndMenuEvent::nothingTODO;
}

/*
 * Extern
 */
GUISFML					*createGUI (Board *board)
{
	return new GUISFML (board);
}

void					setPlayers (GUISFML *GUI, Snake *snakeP1, Snake *snakeP2)
{
	GUI->setPlayers (snakeP1, snakeP2);
}

void					destroyGUI (GUISFML *GUI)
{
	delete GUI;
}
