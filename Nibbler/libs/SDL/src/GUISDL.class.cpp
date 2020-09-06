#include <GUISDL.class.hpp>

static unsigned int _mapWidth;
static unsigned int _mapHeight;

/*
 * Constructors
 */
GUISDL::GUISDL (Board *board)
	: _board (board), _snakeP1 (NULL), _snakeP2 (NULL), _wantedGUI (eGUI::SDL),
	  _window (NULL), _boardRenderer (NULL), _mainMenuImage (NULL), _mainMenuTexture (NULL),
	  _started (false)
{
	if (! board)
	{
		throw InvalidArgumentException ("GUISDL::GUISDL (Board *board, Snake *snake): board == null");
	}

	if (SDL_Init (SDL_INIT_VIDEO))
	{
		throw GUIException (this->_GUIName, "SDL_Init");
	}

	if (! IMG_Init (IMG_INIT_PNG))
	{
		throw GUIException (this->_GUIName, "IMG_Init");
	}

	this->_mainMenuSinglePlayer.x = 50;
	this->_mainMenuSinglePlayer.y = 600;
	this->_mainMenuSinglePlayer.width = 400;
	this->_mainMenuSinglePlayer.height = 100;

	this->_mainMenuMultiplayer.x = 550;
	this->_mainMenuMultiplayer.y = 600;
	this->_mainMenuMultiplayer.width = 400;
	this->_mainMenuMultiplayer.height = 100;

	this->_mainMenuQuitGame.x = 300;
	this->_mainMenuQuitGame.y = 750;
	this->_mainMenuQuitGame.width = 400;
	this->_mainMenuQuitGame.height = 100;
}

/*
 * Destructor
 */
GUISDL::~GUISDL (void)
{
	if (this->_mainMenuTexture != NULL)
		SDL_DestroyTexture (this->_mainMenuTexture);

	if (this->_mainMenuImage != NULL)
		SDL_FreeSurface (this->_mainMenuImage);

	if (this->_boardRenderer != NULL)
		SDL_DestroyRenderer (this->_boardRenderer);

	if (this->_window != NULL)
		SDL_DestroyWindow (this->_window);

	IMG_Quit();

	SDL_Quit();
}

/*
 * Private
 */
void					GUISDL::ajustBounds (void)
{
	this->_mainMenuSinglePlayer.x = this->_mainMenuSinglePlayer.x * _mapWidth / 1000;
	this->_mainMenuSinglePlayer.y = this->_mainMenuSinglePlayer.y * _mapHeight / 1000;
	this->_mainMenuSinglePlayer.width = this->_mainMenuSinglePlayer.width * _mapWidth / 1000;
	this->_mainMenuSinglePlayer.height = this->_mainMenuSinglePlayer.height * _mapHeight / 1000;

	this->_mainMenuMultiplayer.x = this->_mainMenuMultiplayer.x * _mapWidth / 1000;
	this->_mainMenuMultiplayer.y = this->_mainMenuMultiplayer.y * _mapHeight / 1000;
	this->_mainMenuMultiplayer.width = this->_mainMenuMultiplayer.width * _mapWidth / 1000;
	this->_mainMenuMultiplayer.height = this->_mainMenuMultiplayer.height * _mapHeight / 1000;

	this->_mainMenuQuitGame.x = this->_mainMenuQuitGame.x * _mapWidth / 1000;
	this->_mainMenuQuitGame.y = this->_mainMenuQuitGame.y * _mapHeight / 1000;
	this->_mainMenuQuitGame.width = this->_mainMenuQuitGame.width * _mapWidth / 1000;
	this->_mainMenuQuitGame.height = this->_mainMenuQuitGame.height * _mapHeight / 1000;
}

void					GUISDL::drawMainMenu (void)
{
	this->_mainMenuImage = IMG_Load ("res/images/main_menu.png");
	if (this->_mainMenuImage == NULL)
	{
		throw GUIException (this->_GUIName, "IMG_Load GUISDL::drawMainMenu");
	}

	this->_mainMenuTexture = SDL_CreateTextureFromSurface (this->_boardRenderer, this->_mainMenuImage);
	if (this->_mainMenuTexture == NULL)
	{
		throw GUIException (this->_GUIName, "SDL_CreateTextureFromSurface GUISDL::drawMainMenu");
	}

	if (SDL_RenderCopy (this->_boardRenderer, this->_mainMenuTexture, NULL, NULL))
	{
		throw GUIException (this->_GUIName, "SDL_RenderCopy GUISDL::drawMainMenu");
	}
}

void					GUISDL::drawBoard (void)
{
	unsigned int height, width, y, x;
	std::vector< std::vector<int> > *boardCells;
	SDL_Rect boardCellDraw;
	Uint8 r, g, b;

	if (SDL_SetRenderDrawColor (this->_boardRenderer, 255, 255, 255, 255))
	{
		throw GUIException (this->_GUIName, "SDL_SetRenderDrawColor GUISDL::drawBoard");
	}
	if (SDL_RenderClear (this->_boardRenderer))		/* use the RenderDrawColor to clear the Renderer */
	{
		throw GUIException (this->_GUIName, "SDL_RenderClear GUISDL::drawBoard");
	}

	boardCells = this->_board->getBoardCells();
	height = this->_board->getHeight();
	width = this->_board->getWidth();

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			if (boardCells-> at (y).at (x) != 0)
			{
				switch (boardCells-> at (y).at (x))
				{
					case -1:
						r = 0x00;
						g = 0x00;
						b = 0x00;
						break;
					case (int)eBonusValue::CommonValue:
						r = 0xff;
						g = 0xa5;
						b = 0x00;
						break;
					case (int)eBonusValue::UncommonValue:
						r = 0xff;
						g = 0x00;
						b = 0x00;
						break;
					case (int)eBonusValue::RareValue:
						r = 0xff;
						g = 0x00;
						b = 0xff;
						break;
					case (int)eBonusValue::LegendaryValue:
						r = 0x00;
						g = 0x00;
						b = 0xff;
						break;
					case (int)eBonusValue::GodlikeValue:
						r = 0x33;
						g = 0x33;
						b = 0x33;
						break;
					default:
						throw ShouldNeverOccurException (__FILE__, __LINE__);
				}

				if (SDL_SetRenderDrawColor (this->_boardRenderer, r, g, b, 255))
				{
					throw GUIException (this->_GUIName, "SDL_SetRenderDrawColor GUISDL::drawBoard");
				}

				boardCellDraw.x = x * 10;
				boardCellDraw.y = y * 10;
				boardCellDraw.w = 10;
				boardCellDraw.h = 10;

				if (SDL_RenderFillRect (this->_boardRenderer, &boardCellDraw))
				{
					throw GUIException (this->_GUIName, "SDL_RenderFillRect GUISDL::drawBoard");
				}
			}
		}
	}
}

void					GUISDL::drawSnakes (void)
{
	std::list<t_cell> snakeCells;
	std::list<t_cell>::iterator itSnakeCell;
	SDL_Rect snakeCellDraw;

	snakeCells = this->_snakeP1->getSnakeCells();

	if (SDL_SetRenderDrawColor (this->_boardRenderer, 0, 255, 0, 255))
	{
		throw GUIException (this->_GUIName, "SDL_SetRenderDrawColor GUISDL::drawSnake P1");
	}

	for (itSnakeCell = snakeCells.begin(); itSnakeCell != snakeCells.end(); ++itSnakeCell)
	{
		snakeCellDraw.x = itSnakeCell->positionX * 10;
		snakeCellDraw.y = itSnakeCell->positionY * 10;
		snakeCellDraw.w = 10;
		snakeCellDraw.h = 10;

		if (SDL_RenderFillRect (this->_boardRenderer, &snakeCellDraw))
		{
			throw GUIException (this->_GUIName, "SDL_RenderFillRect GUISDL::drawSnake P1");
		}
	}

	if (this->_snakeP2)
	{
		snakeCells = this->_snakeP2->getSnakeCells();

		if (SDL_SetRenderDrawColor (this->_boardRenderer, 0, 255, 255, 255))
		{
			throw GUIException (this->_GUIName, "SDL_SetRenderDrawColor GUISDL::drawSnake P2");
		}

		for (itSnakeCell = snakeCells.begin(); itSnakeCell != snakeCells.end(); ++itSnakeCell)
		{
			snakeCellDraw.x = itSnakeCell->positionX * 10;
			snakeCellDraw.y = itSnakeCell->positionY * 10;
			snakeCellDraw.w = 10;
			snakeCellDraw.h = 10;

			if (SDL_RenderFillRect (this->_boardRenderer, &snakeCellDraw))
			{
				throw GUIException (this->_GUIName, "SDL_RenderFillRect GUISDL::drawSnake P2");
			}
		}
	}
}

void					GUISDL::drawEndMenu (void)
{
	if (SDL_SetRenderDrawColor (this->_boardRenderer, 255, 255, 255, 255))
	{
		throw GUIException (this->_GUIName, "SDL_SetRenderDrawColor GUISDL::drawEndMenu");
	}
	if (SDL_RenderClear (this->_boardRenderer))		/* use the RenderDrawColor to clear the Renderer */
	{
		throw GUIException (this->_GUIName, "SDL_RenderClear GUISDL::drawEndMenu");
	}
}

/*
 * Public
 */
eGUI					GUISDL::getGUIName (void) const
{
	return this->_GUIName;
}

void					GUISDL::start (void)
{
	_mapWidth = this->_board->getWidth() * 10;
	_mapHeight = this->_board->getHeight() * 10;

#ifdef PROJ_DEBUG
	std::cout << "GUISDL::start" << std::endl;
#endif

	this->_window = SDL_CreateWindow ("Nibbler (SDL GUI)", 100, 100, _mapWidth, _mapHeight, SDL_WINDOW_SHOWN);
	if (this->_window == NULL)
	{
		throw GUIException (this->_GUIName, "SDL_CreateWindow");
	}

	this->_boardRenderer = SDL_CreateRenderer (this->_window, -1, SDL_RENDERER_ACCELERATED);
	if (this->_boardRenderer == NULL)
	{
		throw GUIException (this->_GUIName, "SDL_CreateRenderer");
	}

	this->ajustBounds ();

	this->_started = true;
}

bool					GUISDL::alreadyStarted (void) const
{
	return this->_started;
}

eGUI					GUISDL::wantedGUI (void) const
{
	return this->_wantedGUI;
}

void					GUISDL::stop()
{
#ifdef PROJ_DEBUG
	std::cout << "GUISDL::stop" << std::endl;
#endif

	if (this->_window == NULL)
	{
		throw GUIException (this->_GUIName, "GUISDL::stop => GUISDL wasn't started");
	}

	SDL_DestroyWindow (this->_window);

	this->_started = false;
}

/* Main Menu */

void					GUISDL::loadMainMenu (void)
{
	this->drawMainMenu();

	SDL_RenderPresent (this->_boardRenderer);
}

eGUIMainMenuEvent		GUISDL::getMainMenuEvent (void)
{
	SDL_Event events;
	int x, y;

	while (SDL_PollEvent (&events))
	{
		if (events.type == SDL_QUIT)
				return eGUIMainMenuEvent::quitGame;
		else if (events.type == SDL_KEYDOWN)
		{
			switch (events.key.keysym.sym)
			{
				/* GUI Switchs */
				case SDLK_KP_2:
				case SDLK_2:
					this-> _wantedGUI = eGUI::MinilibX;
					return eGUIMainMenuEvent::changeGUI;

				case SDLK_KP_3:
				case SDLK_3:
					this-> _wantedGUI = eGUI::openGL;
					return eGUIMainMenuEvent::changeGUI;

				case SDLK_ESCAPE:
					return eGUIMainMenuEvent::quitGame;

				default:
					return eGUIMainMenuEvent::nothingTODO;
			}
		}
		else if (events.type == SDL_MOUSEBUTTONUP && SDL_BUTTON (SDL_BUTTON_LEFT))
		{
			SDL_GetMouseState (&x, &y);
			if (this->_mainMenuSinglePlayer.in (x, y))
				return eGUIMainMenuEvent::startSinglePlayerGame;
			else if (this->_mainMenuMultiplayer.in (x, y))
				return eGUIMainMenuEvent::startMultiPlayerGame;
			else if (this->_mainMenuQuitGame.in (x, y))
				return eGUIMainMenuEvent::quitGame;
		}
	}

	return eGUIMainMenuEvent::nothingTODO;
}

/* Game */

void					GUISDL::setPlayers (Snake *snakeP1, Snake *snakeP2)
{
	if (! snakeP1)
	{
		throw InvalidArgumentException ("GUISDL::setPlayers: snakeP1 == null");
	}

	this->_snakeP1 = snakeP1;
	this->_snakeP2 = snakeP2;
}

void					GUISDL::updateGameGUI (void)
{
	unsigned int currentGlobalScore;

//	if (! this->_snakeP1->getIsAlive())
//		return;
//	if (this->_snakeP2 && ! this->_snakeP2->getIsAlive())
//		return;

	this->drawBoard();
	this->drawSnakes();

	SDL_RenderPresent (this->_boardRenderer);

	currentGlobalScore = this->_snakeP1->getScore();
	if (this->_snakeP2)
		currentGlobalScore = currentGlobalScore > this->_snakeP2->getScore() ? currentGlobalScore : this->_snakeP2->getScore();

	if (currentGlobalScore > 95)
		currentGlobalScore = 95;

	SDL_Delay (100 - currentGlobalScore);
}

eGUIGameEvent			GUISDL::getGameEvent (void)
{
	SDL_Event events;

	while (SDL_PollEvent (&events))
	{
		if (events.type == SDL_QUIT)
				return eGUIGameEvent::quitGame;
		else if (events.type == SDL_KEYDOWN)
		{
			switch (events.key.keysym.sym)
			{
				case SDLK_e:
					this->_snakeP1->eat (1);
					break;

				/* Player 1 commands */
				case SDLK_LEFT:
					return eGUIGameEvent::p1GoLeft;

				case SDLK_RIGHT:
					return eGUIGameEvent::p1GoRight;

				case SDLK_UP:
					return eGUIGameEvent::p1GoUp;

				case SDLK_DOWN:
					return eGUIGameEvent::p1GoDown;

				/* Player 2 commands */
				case SDLK_q:
					if (this->_snakeP2)
						return eGUIGameEvent::p2GoLeft;
					return eGUIGameEvent::nothingTODO;

				case SDLK_d:
					if (this->_snakeP2)
						return eGUIGameEvent::p2GoRight;
					return eGUIGameEvent::nothingTODO;

				case SDLK_z:
					if (this->_snakeP2)
						return eGUIGameEvent::p2GoUp;
					return eGUIGameEvent::nothingTODO;

				case SDLK_s:
					if (this->_snakeP2)
						return eGUIGameEvent::p2GoDown;
					return eGUIGameEvent::nothingTODO;

				/* GUI Switchs */
				case SDLK_KP_2:
				case SDLK_2:
					this-> _wantedGUI = eGUI::MinilibX;
					return eGUIGameEvent::changeGUI;

				case SDLK_KP_3:
				case SDLK_3:
					this-> _wantedGUI = eGUI::openGL;
					return eGUIGameEvent::changeGUI;

				case SDLK_ESCAPE:
					return eGUIGameEvent::quitGame;

				default:
					return eGUIGameEvent::nothingTODO;
			}
		}
	}

	return eGUIGameEvent::nothingTODO;
}

/* End Menu */

void					GUISDL::loadEndMenu (void)
{
	this->drawEndMenu();

	SDL_RenderPresent (this->_boardRenderer);
}

eGUIEndMenuEvent		GUISDL::getEndMenuEvent (void)
{
	return eGUIEndMenuEvent::nextLevel;
}

/*
 * Extern
 */
GUISDL					*createGUI (Board *board)
{
	return new GUISDL (board);
}

void					setPlayers (GUISDL *GUI, Snake *snakeP1, Snake *snakeP2)
{
	GUI->setPlayers (snakeP1, snakeP2);
}

void					destroyGUI (GUISDL *GUI)
{
	delete GUI;
}
