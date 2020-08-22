#include <GUISDL.class.hpp>

static int _size;

/*
 * Constructors
 */
GUISDL::GUISDL (Board *board, Snake *snake)
	: _board (board), _snake (snake), _window (NULL), _boardRenderer (NULL), _GUISwitch (eGUISwitch::SDL)
{
	SDL_Init (SDL_INIT_VIDEO);
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

	SDL_SetRenderDrawColor (this->_boardRenderer, 0, 0, 255, 255);

	for (itSnakeCell = snakeCells.begin(); itSnakeCell != snakeCells.end(); ++itSnakeCell)
	{
		snakeCellDraw.x = itSnakeCell->positionX * 10;
		snakeCellDraw.y = itSnakeCell->positionY * 10;
		snakeCellDraw.w = 10;
		snakeCellDraw.h = 10;

		SDL_RenderFillRect (this->_boardRenderer, &snakeCellDraw);
	}
}

void			GUISDL::drawTriangle (void)
{
	SDL_SetRenderDrawColor (this->_boardRenderer, 255, 255, 255, 255);
	SDL_RenderClear (this->_boardRenderer);		/* use the RenderDrawColor to clear the Renderer */

	SDL_SetRenderDrawColor (this->_boardRenderer, 0, 0, 255, 255);

	this->drawSnake();

	SDL_RenderPresent (this->_boardRenderer);
}


/*
 * Public
 */
void			GUISDL::start (void)
{
	_size = this->_board->getSize() * 10;

	std::cout << "GUISDL::start" << std::endl;


	this->_window = SDL_CreateWindow ("Nibbler (SDL GUI)", 100, 100, _size, _size, SDL_WINDOW_SHOWN);
	if (this->_window == NULL)
	{
		//THROW EXCEPTION ICI
		std::cerr << "start GUISDL Failed" << std::endl;
		exit (0);
	}

	this->_boardRenderer = SDL_CreateRenderer (this->_window, -1, SDL_RENDERER_ACCELERATED);
	if (this->_boardRenderer == NULL)
	{
		//THROW EXCEPTION ICI
		std::cerr << "start GUISDL Failed" << std::endl;
		exit (0);
	}
}

void			GUISDL::stop()
{
	if (this->_window == NULL)
	{
		//THROW EXCEPTION ICI
		std::cerr << "stop GUISDL Failed" << std::endl;
		exit (0);
	}

	SDL_DestroyWindow (this->_window);
}

bool			GUISDL::run (void)
{
	SDL_Event events;
	int x, y;

	while (SDL_PollEvent (&events))
	{
		if (events.type == SDL_QUIT)
				return false;
		else if (events.type == SDL_KEYDOWN)
		{
			switch (events.key.keysym.sym)
			{
				case SDLK_e:
					this->_snake->eat (1);
					break;
				case SDLK_LEFT:
					this->_snake->goLeft();
					break;
				case SDLK_RIGHT:
					this->_snake->goRight();
					break;
				case SDLK_UP:
					this->_snake->goUp();
					break;
				case SDLK_DOWN:
					this->_snake->goDown();
					break;
				case SDLK_KP_2:
				case SDLK_2:
					this-> _GUISwitch = eGUISwitch::MinilibX;
					return false;
				case SDLK_KP_3:
				case SDLK_3:
					this-> _GUISwitch = eGUISwitch::openGL;
					return false;
				case SDLK_KP_1:
				case SDLK_1:
				default:
					break;
			}
		}
	}

//	SDL_WaitEvent (&events);
//
//	if (events.window.event == SDL_WINDOWEVENT_CLOSE)
//			return false;
//
//	switch (events.key.keysym.sym)
//	{
//		case SDLK_LEFT:
//			this->_snake->moveLeft();
//			break;
//		case SDLK_RIGHT:
//			this->_snake->moveRight();
//			break;
//		case SDLK_UP:
//			this->_snake->moveUp();
//			break;
//		case SDLK_DOWN:
//			this->_snake->moveDown();
//			break;
//		case SDLK_KP_2:
//		case SDLK_2:
//			this-> _GUISwitch = eGUISwitch::MinilibX;
//			return false;
//		case SDLK_KP_3:
//		case SDLK_3:
//			this-> _GUISwitch = eGUISwitch::openGL;
//			return false;
//		case SDLK_KP_1:
//		case SDLK_1:
//		default:
//			this->_snake->moveStraight();
//			break;
//	}

	this->_snake->moveStraight();
	this->drawTriangle();

	SDL_Delay (100 /* 16 */);		/* ~ 60 FPS */

	return true;
}

eGUISwitch		GUISDL::getGUISwitch (void) const
{
	return this->_GUISwitch;
}

/*
 * Extern
 */
GUISDL		*createGUI (Board *board, Snake *snake, int *ac, char **av)
{
	 (void)ac;
	 (void)av;
	return new GUISDL (board, snake);
}

void			destroyGUI (GUISDL *GUI)
{
	delete GUI;
}
