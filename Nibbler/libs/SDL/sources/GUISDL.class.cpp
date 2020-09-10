#include <GUISDL.class.hpp>

static unsigned int _mapWidth;
static unsigned int _mapHeight;

/*
 * Constructors
 */
GUISDL::GUISDL (Board *board)
	: _board (board), _snakeP1 (NULL), _snakeP2 (NULL), _wantedGUI (eGUI::SDL),
	  _window (NULL), _boardRenderer (NULL), _mainMenuImage (NULL), _mainMenuTexture (NULL),
	  _endMenuImage (NULL), _endMenuTexture (NULL),
	  _mainMenuMusic (NULL), _boardMusic (NULL), _endMenuMusic (NULL), _musicVolume (MIX_MAX_VOLUME / 2),
	  _started (false)
{
	if (! board)
	{
		throw InvalidArgumentException ("GUISDL::GUISDL (Board *board, Snake *snake): board == null");
	}

	if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		throw GUIException (this->_GUIName, "SDL_Init", SDL_GetError());
	}

	if (! IMG_Init (IMG_INIT_PNG))
	{
		throw GUIException (this->_GUIName, "IMG_Init", IMG_GetError());
	}

	if (Mix_OpenAudio (44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		throw GUIException (this->_GUIName, "Mix_OpenAudio", Mix_GetError());
	}

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
GUISDL::~GUISDL (void)
{
	if (this->_endMenuTexture != NULL)
		SDL_DestroyTexture (this->_endMenuTexture);

	if (this->_endMenuImage != NULL)
		SDL_FreeSurface (this->_endMenuImage);

	if (this->_mainMenuTexture != NULL)
		SDL_DestroyTexture (this->_mainMenuTexture);

	if (this->_mainMenuImage != NULL)
		SDL_FreeSurface (this->_mainMenuImage);

	if (this->_boardRenderer != NULL)
		SDL_DestroyRenderer (this->_boardRenderer);

	if (this->_window != NULL)
		SDL_DestroyWindow (this->_window);

	Mix_Quit();

	IMG_Quit();

	SDL_Quit();
}

/*
 * Private
 */
void					GUISDL::ajustBounds (void)
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

void					GUISDL::drawMainMenu (void)
{
	if (this->_mainMenuImage == NULL)
	{
		this->_mainMenuImage = IMG_Load ("ressources/images/main_menu.png");
		if (this->_mainMenuImage == NULL)
		{
			throw GUIException (this->_GUIName, "IMG_Load GUISDL::drawMainMenu", IMG_GetError());
		}
	}

	if (this->_mainMenuTexture == NULL)
	{
		this->_mainMenuTexture = SDL_CreateTextureFromSurface (this->_boardRenderer, this->_mainMenuImage);
		if (this->_mainMenuTexture == NULL)
		{
			throw GUIException (this->_GUIName, "SDL_CreateTextureFromSurface GUISDL::drawMainMenu", SDL_GetError());
		}
	}

	if (SDL_RenderCopy (this->_boardRenderer, this->_mainMenuTexture, NULL, NULL))
	{
		throw GUIException (this->_GUIName, "SDL_RenderCopy GUISDL::drawMainMenu", SDL_GetError());
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
		throw GUIException (this->_GUIName, "SDL_SetRenderDrawColor GUISDL::drawBoard", SDL_GetError());
	}
	if (SDL_RenderClear (this->_boardRenderer))		/* use the RenderDrawColor to clear the Renderer */
	{
		throw GUIException (this->_GUIName, "SDL_RenderClear GUISDL::drawBoard", SDL_GetError());
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
					throw GUIException (this->_GUIName, "SDL_SetRenderDrawColor GUISDL::drawBoard", SDL_GetError());
				}

				boardCellDraw.x = x * 10;
				boardCellDraw.y = y * 10;
				boardCellDraw.w = 10;
				boardCellDraw.h = 10;

				if (SDL_RenderFillRect (this->_boardRenderer, &boardCellDraw))
				{
					throw GUIException (this->_GUIName, "SDL_RenderFillRect GUISDL::drawBoard", SDL_GetError());
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
	bool head;

	snakeCells = this->_snakeP1->getSnakeCells();

	head = true;
	for (itSnakeCell = snakeCells.begin(); itSnakeCell != snakeCells.end(); ++itSnakeCell)
	{
		snakeCellDraw.x = itSnakeCell->positionX * 10;
		snakeCellDraw.y = itSnakeCell->positionY * 10;
		snakeCellDraw.w = 10;
		snakeCellDraw.h = 10;

		if (head)
		{
			if (SDL_SetRenderDrawColor (this->_boardRenderer, 0, 128, 0, 255))
			{
				throw GUIException (this->_GUIName, "SDL_SetRenderDrawColor GUISDL::drawSnake P1", SDL_GetError());
			}

			if (SDL_RenderFillRect (this->_boardRenderer, &snakeCellDraw))
			{
				throw GUIException (this->_GUIName, "SDL_RenderFillRect GUISDL::drawSnake P1", SDL_GetError());
			}

			if (SDL_SetRenderDrawColor (this->_boardRenderer, 0, 255, 0, 255))
			{
				throw GUIException (this->_GUIName, "SDL_SetRenderDrawColor GUISDL::drawSnake P1", SDL_GetError());
			}

			head = false;
		}
		else
		{
			if (SDL_RenderFillRect (this->_boardRenderer, &snakeCellDraw))
			{
				throw GUIException (this->_GUIName, "SDL_RenderFillRect GUISDL::drawSnake P1", SDL_GetError());
			}
		}
	}

	if (this->_snakeP2)
	{
		snakeCells = this->_snakeP2->getSnakeCells();

		head = true;
		for (itSnakeCell = snakeCells.begin(); itSnakeCell != snakeCells.end(); ++itSnakeCell)
		{
			snakeCellDraw.x = itSnakeCell->positionX * 10;
			snakeCellDraw.y = itSnakeCell->positionY * 10;
			snakeCellDraw.w = 10;
			snakeCellDraw.h = 10;

			if (head)
			{
				if (SDL_SetRenderDrawColor (this->_boardRenderer, 0, 128, 128, 255))
				{
					throw GUIException (this->_GUIName, "SDL_SetRenderDrawColor GUISDL::drawSnake P2", SDL_GetError());
				}

				if (SDL_RenderFillRect (this->_boardRenderer, &snakeCellDraw))
				{
					throw GUIException (this->_GUIName, "SDL_RenderFillRect GUISDL::drawSnake P2", SDL_GetError());
				}

				if (SDL_SetRenderDrawColor (this->_boardRenderer, 0, 255, 255, 255))
				{
					throw GUIException (this->_GUIName, "SDL_SetRenderDrawColor GUISDL::drawSnake P2", SDL_GetError());
				}

				head = false;
			}
			else
			{
				if (SDL_RenderFillRect (this->_boardRenderer, &snakeCellDraw))
				{
					throw GUIException (this->_GUIName, "SDL_RenderFillRect GUISDL::drawSnake P2", SDL_GetError());
				}
			}
		}
	}
}

void					GUISDL::drawEndMenu (void)
{
	eBoardStatus boardStatus;

	if (this->_endMenuImage != NULL)
		SDL_FreeSurface (this->_endMenuImage);

	boardStatus = this->_board->getBoardStatus();
	switch (boardStatus)
	{
		case eBoardStatus::Player1Win:
			if (! this->_snakeP2)
				this->_endMenuImage = IMG_Load ("ressources/images/singleplayer_win.png");
			else
				this->_endMenuImage = IMG_Load ("ressources/images/multiplayer_player1_win.png");
			break;
		case eBoardStatus::Player1Lose:
			if (! this->_snakeP2)
				this->_endMenuImage = IMG_Load ("ressources/images/singleplayer_lose.png");
			else
				this->_endMenuImage = IMG_Load ("ressources/images/multiplayer_player2_win.png");
			break;
		case eBoardStatus::Player2Win:
			this->_endMenuImage = IMG_Load ("ressources/images/multiplayer_player2_win.png");
			break;
		case eBoardStatus::Player2Lose:
			this->_endMenuImage = IMG_Load ("ressources/images/multiplayer_player1_win.png");
			break;
		case eBoardStatus::Draw:
			this->_endMenuImage = IMG_Load ("ressources/images/multiplayer_draw.png");
			break;
		default:
			throw ShouldNeverOccurException (__FILE__, __LINE__);
	}

	if (this->_endMenuImage == NULL)
	{
		throw GUIException (this->_GUIName, "IMG_Load GUISDL::drawEndMenu", IMG_GetError());
	}

	if (this->_endMenuTexture != NULL)
		SDL_DestroyTexture (this->_endMenuTexture);

	this->_endMenuTexture = SDL_CreateTextureFromSurface (this->_boardRenderer, this->_endMenuImage);
	if (this->_endMenuTexture == NULL)
	{
		throw GUIException (this->_GUIName, "SDL_CreateTextureFromSurface GUISDL::drawEndMenu", SDL_GetError());
	}

	if (SDL_RenderCopy (this->_boardRenderer, this->_endMenuTexture, NULL, NULL))
	{
		throw GUIException (this->_GUIName, "SDL_RenderCopy GUISDL::drawEndMenu", SDL_GetError());
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
		throw GUIException (this->_GUIName, "SDL_CreateWindow"), SDL_GetError();
	}

	this->_boardRenderer = SDL_CreateRenderer (this->_window, -1, SDL_RENDERER_ACCELERATED);
	if (this->_boardRenderer == NULL)
	{
		throw GUIException (this->_GUIName, "SDL_CreateRenderer", SDL_GetError());
	}

	this->ajustBounds ();

	this->_mainMenuMusic = Mix_LoadMUS ("ressources/sounds/ff_main_menu.wav");
	if (! this->_mainMenuMusic)
	{
		throw GUIException (this->_GUIName, "Mix_LoadMUS 1", Mix_GetError());
	}

	Mix_VolumeMusic (this->_musicVolume);

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

	if (this->_mainMenuMusic != NULL)
	{
		Mix_FreeMusic (this->_mainMenuMusic);
		this->_mainMenuMusic = NULL;
	}

	if (this->_boardMusic != NULL)
	{
		Mix_FreeMusic (this->_boardMusic);
		this->_boardMusic = NULL;
	}

	if (this->_endMenuMusic != NULL)
	{
		Mix_FreeMusic (this->_endMenuMusic);
		this->_endMenuMusic = NULL;
	}

	SDL_DestroyWindow (this->_window);

	this->_started = false;
}

/* Main Menu */

void					GUISDL::loadMainMenu (void)
{
	if (Mix_PausedMusic() == 1)
	{
		Mix_HaltMusic();
		Mix_PlayMusic (this->_mainMenuMusic, -1);
		Mix_PauseMusic();
	}
	else
	{
		Mix_HaltMusic();
		Mix_PlayMusic (this->_mainMenuMusic, -1);
	}

	this->drawMainMenu();

	SDL_RenderPresent (this->_boardRenderer);
}

eGUIMainMenuEvent		GUISDL::getMainMenuEvent (void)
{
	SDL_Event events;
	int x, y;

	while (SDL_PollEvent (&events))
	{
		switch (events.type)
		{
			case SDL_QUIT:
				return eGUIMainMenuEvent::quitGame;

			case SDL_KEYDOWN:
				switch (events.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						return eGUIMainMenuEvent::quitGame;

					/* GUI Switchs */
					case SDLK_2:
					case SDLK_F2:
					case SDLK_KP_2:
						this-> _wantedGUI = eGUI::SFML;
						return eGUIMainMenuEvent::changeGUI;

					case SDLK_3:
					case SDLK_F3:
					case SDLK_KP_3:
						this-> _wantedGUI = eGUI::openGL;
						return eGUIMainMenuEvent::changeGUI;

					/* Audio */
					case SDLK_p:
						if (Mix_PausedMusic() == 1)
							Mix_ResumeMusic();
						else
							Mix_PauseMusic();
						break;

					case SDLK_m:
						if (Mix_PlayingMusic())
							Mix_PauseMusic();
						break;

					case SDLK_PLUS:
					case SDLK_KP_PLUS:
						this->_musicVolume = this->_musicVolume + 8 <= 128 ?
											 this->_musicVolume + 8:
											 128;
						Mix_VolumeMusic (this->_musicVolume);
						break;

					case SDLK_MINUS:
					case SDLK_KP_MINUS:
						this->_musicVolume = this->_musicVolume >= 8 ?
											 this->_musicVolume - 8:
											 0;
						Mix_VolumeMusic (this->_musicVolume);
						break;

					default:
						break;
				}
				break;

			case SDL_MOUSEBUTTONUP:
				if (SDL_BUTTON (SDL_BUTTON_LEFT))
				{
					SDL_GetMouseState (&x, &y);
					if (this->_menuLeftButton.in (x, y))
						return eGUIMainMenuEvent::startSinglePlayerGame;
					else if (this->_menuRightButton.in (x, y))
						return eGUIMainMenuEvent::startMultiPlayerGame;
					else if (this->_menuQuitButton.in (x, y))
						return eGUIMainMenuEvent::quitGame;
				}
				break;

			default:
				break;
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

void					GUISDL::loadBoard (unsigned int soundTrack)
{
	if (this->_boardMusic != NULL)
	{
		Mix_FreeMusic (this->_boardMusic);
		this->_boardMusic = NULL;
	}

	switch (soundTrack)
	{
		case 0:
			this->_boardMusic = Mix_LoadMUS ("ressources/sounds/ff_main_theme.wav");
			if (! this->_boardMusic)
			{
				throw GUIException (this->_GUIName, "Mix_LoadMUS 3", Mix_GetError());
			}
			break;

		case 1:
			this->_boardMusic = Mix_LoadMUS ("ressources/sounds/Twin Musicom - 8-bit March.wav");
			if (! this->_boardMusic)
			{
				throw GUIException (this->_GUIName, "Mix_LoadMUS 3", Mix_GetError());
			}
			break;

		case 2:
			this->_boardMusic = Mix_LoadMUS ("ressources/sounds/Twin Musicom - NES Theme.wav");
			if (! this->_boardMusic)
			{
				throw GUIException (this->_GUIName, "Mix_LoadMUS 3", Mix_GetError());
			}
			break;

		case 3:
		default:
			this->_boardMusic = Mix_LoadMUS ("ressources/sounds/ff_main_theme.wav");
			if (! this->_boardMusic)
			{
				throw GUIException (this->_GUIName, "Mix_LoadMUS 3", Mix_GetError());
			}
			break;
	}

	if (Mix_PausedMusic() == 1)
	{
		Mix_HaltMusic();
		Mix_PlayMusic (this->_boardMusic, -1);
		Mix_PauseMusic();
	}
	else
	{
		Mix_HaltMusic();
		Mix_PlayMusic (this->_boardMusic, -1);
	}
}

void					GUISDL::updateGameGUI (void)
{
	unsigned int currentGlobalScore;

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
		switch (events.type)
		{
			case SDL_QUIT:
				return eGUIGameEvent::quitGame;

			case SDL_KEYDOWN:

				switch (events.key.keysym.sym)
				{
					case SDLK_e:
						this->_snakeP1->eat (1);
						break;

					case SDLK_ESCAPE:
						return eGUIGameEvent::quitGame;

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
						break;

					case SDLK_d:
						if (this->_snakeP2)
							return eGUIGameEvent::p2GoRight;
						break;

					case SDLK_z:
						if (this->_snakeP2)
							return eGUIGameEvent::p2GoUp;
						break;

					case SDLK_s:
						if (this->_snakeP2)
							return eGUIGameEvent::p2GoDown;
						break;

					/* GUI Switchs */
					case SDLK_2:
					case SDLK_F2:
					case SDLK_KP_2:
						this-> _wantedGUI = eGUI::SFML;
						return eGUIGameEvent::changeGUI;

					case SDLK_3:
					case SDLK_F3:
					case SDLK_KP_3:
						this-> _wantedGUI = eGUI::openGL;
						return eGUIGameEvent::changeGUI;

					/* Audio */
					case SDLK_p:
						if (Mix_PausedMusic() == 1)
							Mix_ResumeMusic();
						else
							Mix_PauseMusic();
						break;

					case SDLK_m:
						if (Mix_PlayingMusic())
							Mix_PauseMusic();
						break;

					case SDLK_PLUS:
					case SDLK_KP_PLUS:
						this->_musicVolume = this->_musicVolume + 8 <= 128 ?
											 this->_musicVolume + 8:
											 128;
						Mix_VolumeMusic (this->_musicVolume);
						break;

					case SDLK_MINUS:
					case SDLK_KP_MINUS:
						this->_musicVolume = this->_musicVolume >= 8 ?
											 this->_musicVolume - 8:
											 0;
						Mix_VolumeMusic (this->_musicVolume);
						break;

					default:
						break;
				}
				break;

			default:
				break;
		}
	}

	return eGUIGameEvent::nothingTODO;
}

/* End Menu */

void					GUISDL::loadEndMenu (void)
{
	eBoardStatus boardStatus;
	std::string endMenuMusicName;

	if (this->_endMenuMusic != NULL)
	{
		Mix_FreeMusic (this->_endMenuMusic);
		this->_endMenuMusic = NULL;
	}

	boardStatus = this->_board->getBoardStatus();
	switch (boardStatus)
	{
		case eBoardStatus::Player1Win:
		case eBoardStatus::Player2Win:
		case eBoardStatus::Player2Lose:
			endMenuMusicName = "ressources/sounds/end_menu_win.wav";
			break;
		case eBoardStatus::Player1Lose:
			if (! this->_snakeP2)
				endMenuMusicName = "ressources/sounds/end_menu_game_over.wav";
			else
				endMenuMusicName = "ressources/sounds/end_menu_win.wav";
			break;
		case eBoardStatus::Draw:
			endMenuMusicName = "ressources/sounds/end_menu_draw.wav";
			break;
		default:
			throw ShouldNeverOccurException (__FILE__, __LINE__);
	}

	this->_endMenuMusic = Mix_LoadMUS (endMenuMusicName.c_str());
	if (! this->_endMenuMusic)
	{
		throw GUIException (this->_GUIName, std::string ("Mix_LoadMUS \"") + endMenuMusicName.c_str() + "\"", Mix_GetError());
	}

	if (Mix_PausedMusic() == 1)
	{
		Mix_HaltMusic();
		Mix_PlayMusic (this->_endMenuMusic, 1);
		Mix_PauseMusic();
	}
	else
	{
		Mix_HaltMusic();
		Mix_PlayMusic (this->_endMenuMusic, 1);
	}

	this->drawEndMenu();

	SDL_RenderPresent (this->_boardRenderer);
}

eGUIEndMenuEvent		GUISDL::getEndMenuEvent (void)
{
	SDL_Event events;
	int x, y;

	while (SDL_PollEvent (&events))
	{
		switch (events.type)
		{
			case SDL_QUIT:
				return eGUIEndMenuEvent::quitGame;

			case SDL_KEYDOWN:
				switch (events.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						return eGUIEndMenuEvent::quitGame;

					/* GUI Switchs */
					case SDLK_2:
					case SDLK_F2:
					case SDLK_KP_2:
						this-> _wantedGUI = eGUI::SFML;
						return eGUIEndMenuEvent::changeGUI;

					case SDLK_3:
					case SDLK_F3:
					case SDLK_KP_3:
						this-> _wantedGUI = eGUI::openGL;
						return eGUIEndMenuEvent::changeGUI;

					/* Audio */
					case SDLK_p:
						if (Mix_PausedMusic() == 1)
							Mix_ResumeMusic();
						else
							Mix_PauseMusic();
						break;

					case SDLK_m:
						if (Mix_PlayingMusic())
							Mix_PauseMusic();
						break;

					case SDLK_PLUS:
					case SDLK_KP_PLUS:
						this->_musicVolume = this->_musicVolume + 8 <= 128 ?
											 this->_musicVolume + 8:
											 128;
						Mix_VolumeMusic (this->_musicVolume);
						break;

					case SDLK_MINUS:
					case SDLK_KP_MINUS:
						this->_musicVolume = this->_musicVolume >= 8 ?
											 this->_musicVolume - 8:
											 0;
						Mix_VolumeMusic (this->_musicVolume);
						break;

					default:
						break;
				}
				break;

			case SDL_MOUSEBUTTONUP:
				if (SDL_BUTTON (SDL_BUTTON_LEFT))
				{
					SDL_GetMouseState (&x, &y);
					if (this->_menuLeftButton.in (x, y))
						return eGUIEndMenuEvent::restartLevel;
					else if (this->_menuRightButton.in (x, y))
						return eGUIEndMenuEvent::nextLevel;
					else if (this->_menuQuitButton.in (x, y))
						return eGUIEndMenuEvent::quitGame;
				}
				break;

			default:
				break;
		}
	}

	return eGUIEndMenuEvent::nothingTODO;
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
