#include <GUISDL.class.hpp>

static int _size;

/*
 * Constructors
 */
GUISDL::GUISDL (Board *board, Snake *snake)
	: _board (board), _snake (snake), _window (NULL), _boardRenderer (NULL), _wantedGUI (eGUI::SDL)
{
	if (SDL_Init (SDL_INIT_VIDEO))
	{
		throw GUIException (this->_GUIName, "SDL_Init");
	}
	this->_snake->setMapSize (this->_board->getSize());
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
void			GUISDL::drawSnake (void)
{
	std::list<t_cell> snakeCells;
	std::list<t_cell>::iterator itSnakeCell;
	SDL_Rect snakeCellDraw;

	snakeCells = this->_snake->getSnakeCells();

	if (SDL_SetRenderDrawColor (this->_boardRenderer, 0, 0, 255, 255))
	{
		throw GUIException (this->_GUIName, "SDL_SetRenderDrawColor");
	}

	for (itSnakeCell = snakeCells.begin(); itSnakeCell != snakeCells.end(); ++itSnakeCell)
	{
		snakeCellDraw.x = itSnakeCell->positionX * 10;
		snakeCellDraw.y = itSnakeCell->positionY * 10;
		snakeCellDraw.w = 10;
		snakeCellDraw.h = 10;

		if (SDL_RenderFillRect (this->_boardRenderer, &snakeCellDraw))
		{
			throw GUIException (this->_GUIName, "SDL_RenderFillRect");
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
	_size = this->_board->getSize() * 10;

	std::cout << "GUISDL::start" << std::endl;


	this->_window = SDL_CreateWindow ("Nibbler (SDL GUI)", 100, 100, _size, _size, SDL_WINDOW_SHOWN);
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
					this->_snake->eat (1);
					break;

				case SDLK_LEFT:
					return eGUIEvent::goLeft;

				case SDLK_RIGHT:
					return eGUIEvent::goRight;

				case SDLK_UP:
					return eGUIEvent::goUp;

				case SDLK_DOWN:
					return eGUIEvent::goDown;

				case SDLK_KP_2:
				case SDLK_2:
					this-> _wantedGUI = eGUI::MinilibX;
					return eGUIEvent::changeGUI;

				case SDLK_KP_3:
				case SDLK_3:
					this-> _wantedGUI = eGUI::openGL;
					return eGUIEvent::changeGUI;

				case SDLK_KP_1:
				case SDLK_1:
				default:
					return eGUIEvent::nothingTODO;
			}
		}
	}

	return eGUIEvent::nothingTODO;
}

void			GUISDL::updateGUI (void)
{
	if (SDL_SetRenderDrawColor (this->_boardRenderer, 255, 255, 255, 255))
	{
		throw GUIException (this->_GUIName, "SDL_CreateRenderer");
	}
	if (SDL_RenderClear (this->_boardRenderer))		/* use the RenderDrawColor to clear the Renderer */
	{
		throw GUIException (this->_GUIName, "SDL_CreateRenderer");
	}

	if (SDL_SetRenderDrawColor (this->_boardRenderer, 0, 0, 255, 255))
	{
		throw GUIException (this->_GUIName, "SDL_CreateRenderer");
	}

	this->drawSnake();

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
GUISDL			*createGUI (Board *board, Snake *snake, int *ac, char **av)
{
	 (void)ac;
	 (void)av;
	return new GUISDL (board, snake);
}

void			destroyGUI (GUISDL *GUI)
{
	delete GUI;
}
