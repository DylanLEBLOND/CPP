#include <GUISDL.class.hpp>

static unsigned int _mapWidth;
static unsigned int _mapHeight;

/*
 * Constructors
 */
GUISDL::GUISDL (Board *board, Snake *snake)
	: _board (board), _snakeP1 (snake), _snakeP2 (NULL), _window (NULL), _boardRenderer (NULL), _wantedGUI (eGUI::SDL)
{
	if (! board)
	{
		throw InvalidArgumentException ("GUISDL::GUISDL (Board *board, Snake *snake): board == null");
	}

	if (! snake)
	{
		throw InvalidArgumentException ("GUISDL::GUISDL (Board *board, Snake *snake): snake == null");
	}

	if (SDL_Init (SDL_INIT_VIDEO))
	{
		throw GUIException (this->_GUIName, "SDL_Init");
	}
}

GUISDL::GUISDL (Board *board, Snake *snakeP1, Snake *snakeP2)
	: _board (board), _snakeP1 (snakeP1), _snakeP2 (snakeP2), _window (NULL), _boardRenderer (NULL), _wantedGUI (eGUI::SDL)
{
	if (! board)
	{
		throw InvalidArgumentException ("GUISDL::GUISDL (Board *board, Snake *snakeP1, Snake *snakeP2): board == null");
	}

	if (! snakeP1 || ! snakeP2)
	{
		throw InvalidArgumentException ("GUISDL::GUISDL (Board *board, Snake *snakeP1, Snake *snakeP2): snakeP1 and/or snakeP2 == null");
	}

	if (SDL_Init (SDL_INIT_VIDEO))
	{
		throw GUIException (this->_GUIName, "SDL_Init");
	}
}

/*
 * Destructor
 */
GUISDL::~GUISDL (void)
{
	if (this->_boardRenderer != NULL)
		SDL_DestroyRenderer (this->_boardRenderer);

	if (this->_window != NULL)
		SDL_DestroyWindow (this->_window);

	SDL_Quit();
}

/*
 * Private
 */
void			GUISDL::drawBoard (void)
{
	unsigned int height, width, y, x;
	std::vector< std::vector<int> > *boardCells;
	SDL_Rect boardCellDraw;

	if (SDL_SetRenderDrawColor (this->_boardRenderer, 255, 255, 255, 255))
	{
		throw GUIException (this->_GUIName, "SDL_SetRenderDrawColor GUISDL::drawBoard");
	}
	if (SDL_RenderClear (this->_boardRenderer))		/* use the RenderDrawColor to clear the Renderer */
	{
		throw GUIException (this->_GUIName, "SDL_RenderClear GUISDL::drawBoard");
	}

	if (SDL_SetRenderDrawColor (this->_boardRenderer, 0, 0, 0, 255))
	{
		throw GUIException (this->_GUIName, "SDL_SetRenderDrawColor GUISDL::drawBoard");
	}

	boardCells = this->_board->getBoardCells();
	height = this->_board->getHeight();
	width = this->_board->getWidth();

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			if (boardCells-> at (y).at (x) < 0)
			{
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

void			GUISDL::drawSnakes (void)
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

		if (SDL_SetRenderDrawColor (this->_boardRenderer, 0, 0, 255, 255))
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

/*
 * Public
 */
eGUI			GUISDL::getGUIName (void) const
{
	return this->_GUIName;
}

void			GUISDL::start (void)
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
}

void			GUISDL::stop()
{
#ifdef PROJ_DEBUG
	std::cout << "GUISDL::stop" << std::endl;
#endif

	if (this->_window == NULL)
	{
		throw GUIException (this->_GUIName, "GUISDL::stop => GUISDL wasn't started");
	}

	SDL_DestroyWindow (this->_window);
}

eGUIEvent		GUISDL::getEvent (void)
{
	SDL_Event events;
	int x, y;

	while (SDL_PollEvent (&events))
	{
		if (events.type == SDL_QUIT)
				return eGUIEvent::quitGame;
		else if (events.type == SDL_KEYDOWN)
		{
			switch (events.key.keysym.sym)
			{
				case SDLK_e:
					this->_snakeP1->eat (1);
					break;

				/* Player 1 commands */
				case SDLK_LEFT:
					return eGUIEvent::p1GoLeft;

				case SDLK_RIGHT:
					return eGUIEvent::p1GoRight;

				case SDLK_UP:
					return eGUIEvent::p1GoUp;

				case SDLK_DOWN:
					return eGUIEvent::p1GoDown;

				/* Player 2 commands */
				case SDLK_q:
					if (this->_snakeP2)
						return eGUIEvent::p2GoLeft;
					return eGUIEvent::nothingTODO;

				case SDLK_d:
					if (this->_snakeP2)
						return eGUIEvent::p2GoRight;
					return eGUIEvent::nothingTODO;

				case SDLK_z:
					if (this->_snakeP2)
						return eGUIEvent::p2GoUp;
					return eGUIEvent::nothingTODO;

				case SDLK_s:
					if (this->_snakeP2)
						return eGUIEvent::p2GoDown;
					return eGUIEvent::nothingTODO;

				/* GUI Switchs */
				case SDLK_KP_2:
				case SDLK_2:
					this-> _wantedGUI = eGUI::MinilibX;
					return eGUIEvent::changeGUI;

				case SDLK_KP_3:
				case SDLK_3:
					this-> _wantedGUI = eGUI::openGL;
					return eGUIEvent::changeGUI;

				case SDLK_ESCAPE:
					return eGUIEvent::quitGame;

				default:
					return eGUIEvent::nothingTODO;
			}
		}
	}

	return eGUIEvent::nothingTODO;
}

void			GUISDL::updateGUI (void)
{
	this->drawBoard();
	this->drawSnakes();

	SDL_RenderPresent (this->_boardRenderer);

	SDL_Delay (100 /* 16 */);		/* ~ 60 FPS */
}

eGUI			GUISDL::wantedGUI (void) const
{
	return this->_wantedGUI;
}

/*
 * Extern
 */
GUISDL			*createGUI (Board *board, Snake *snakeP1, Snake *snakeP2)
{
	if (! snakeP2)
		return new GUISDL (board, snakeP1);
	return new GUISDL (board, snakeP1, snakeP2);
}

void			destroyGUI (GUISDL *GUI)
{
	delete GUI;
}
