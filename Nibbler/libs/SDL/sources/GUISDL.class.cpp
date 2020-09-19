#include <GUISDL.class.hpp>

static unsigned int _mapWidth;
static unsigned int _mapHeight;

/*
 * Constructors
 */
GUISDL::GUISDL (Board *board)
	: _board (board), _snakeP1 (NULL), _snakeP2 (NULL), _wantedGUI (eGUI::SDL),
	  _window (NULL), _boardRenderer (NULL), _mainMenuImage (NULL), _mainMenuTexture (NULL),
	  _mapSelectionImage (NULL), _mapSelectionTexture (NULL), _endMenuImage (NULL), _endMenuTexture (NULL),
	  _textHeight (26), _mainTextPolice (NULL), _mainTextImage (NULL), _mainTextTexture (NULL),
	  _scoreTextPolice (NULL), _scoreP1TextImage (NULL), _scoreP1TextTexture (NULL),
	  _scoreP2TextImage (NULL), _scoreP2TextTexture (NULL),
	  _mainMenuMusic (NULL), _mapSelectionMusic (NULL), _boardMusic (NULL), _endMenuMusic (NULL),
	  _musicVolume (MIX_MAX_VOLUME / 2),
	  _started (false)
{
	char SDLenv[] = "SDL_VIDEO_CENTERED=1";

	if (! board)
	{
		throw InvalidArgumentException ("GUISDL::GUISDL (Board *board, Snake *snake): board == null");
	}

	putenv (SDLenv);
	if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		throw GUIException (eGUIString (this->_GUI), "SDL_Init", SDL_GetError());
	}

	if (! IMG_Init (IMG_INIT_PNG))
	{
		throw GUIException (eGUIString (this->_GUI), "IMG_Init", IMG_GetError());
	}

	if (TTF_Init () == -1)
	{
		throw GUIException (eGUIString (this->_GUI), "TTF_Init", TTF_GetError());
	}

	if (Mix_OpenAudio (44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		throw GUIException (eGUIString (this->_GUI), "Mix_OpenAudio", Mix_GetError());
	}

	this->_menuLeftButton.x = 50;
	this->_menuLeftButton.y = 550;
	this->_menuLeftButton.width = 400;
	this->_menuLeftButton.height = 100;

	this->_menuRightButton.x = 550;
	this->_menuRightButton.y = 550;
	this->_menuRightButton.width = 400;
	this->_menuRightButton.height = 100;

	this->_menuMiddleButton.x = 300;
	this->_menuMiddleButton.y = 700;
	this->_menuMiddleButton.width = 400;
	this->_menuMiddleButton.height = 100;

	this->_menuBottomButton.x = 300;
	this->_menuBottomButton.y = 850;
	this->_menuBottomButton.width = 400;
	this->_menuBottomButton.height = 100;

		/* Map Selection */

	this->_mapLTButton.x = 100;
	this->_mapLTButton.y = 200;
	this->_mapLTButton.width = 200;
	this->_mapLTButton.height = 200;

	this->_mapLMButton.x = 100;
	this->_mapLMButton.y = 450;
	this->_mapLMButton.width = 200;
	this->_mapLMButton.height = 200;

	this->_mapLBButton.x = 100;
	this->_mapLBButton.y = 700;
	this->_mapLBButton.width = 200;
	this->_mapLBButton.height = 200;

	this->_mapCTButton.x = 400;
	this->_mapCTButton.y = 200;
	this->_mapCTButton.width = 200;
	this->_mapCTButton.height = 200;

	this->_mapCMButton.x = 400;
	this->_mapCMButton.y = 450;
	this->_mapCMButton.width = 200;
	this->_mapCMButton.height = 200;

	this->_mapCBButton.x = 400;
	this->_mapCBButton.y = 700;
	this->_mapCBButton.width = 200;
	this->_mapCBButton.height = 200;

	this->_mapRTButton.x = 700;
	this->_mapRTButton.y = 200;
	this->_mapRTButton.width = 200;
	this->_mapRTButton.height = 200;

	this->_mapRMButton.x = 700;
	this->_mapRMButton.y = 450;
	this->_mapRMButton.width = 200;
	this->_mapRMButton.height = 200;

	this->_mapRBButton.x = 700;
	this->_mapRBButton.y = 700;
	this->_mapRBButton.width = 200;
	this->_mapRBButton.height = 200;
}

/*
 * Destructor
 */
GUISDL::~GUISDL (void)
{
	char SDLenv[] = "SDL_VIDEO_CENTERED=1";

	if (this->_scoreP2TextTexture != NULL)
		SDL_DestroyTexture (this->_scoreP2TextTexture);

	if (this->_scoreP2TextImage != NULL)
		SDL_FreeSurface (this->_scoreP2TextImage);

	if (this->_scoreP1TextTexture != NULL)
		SDL_DestroyTexture (this->_scoreP1TextTexture);

	if (this->_scoreP1TextImage != NULL)
		SDL_FreeSurface (this->_scoreP1TextImage);

	if (this->_mainTextTexture != NULL)
		SDL_DestroyTexture (this->_mainTextTexture);

	if (this->_mainTextImage != NULL)
		SDL_FreeSurface (this->_mainTextImage);

	if (this->_endMenuTexture != NULL)
		SDL_DestroyTexture (this->_endMenuTexture);

	if (this->_endMenuImage != NULL)
		SDL_FreeSurface (this->_endMenuImage);

	if (this->_mapSelectionTexture != NULL)
		SDL_DestroyTexture (this->_mapSelectionTexture);

	if (this->_mapSelectionImage != NULL)
		SDL_FreeSurface (this->_mapSelectionImage);

	if (this->_mainMenuTexture != NULL)
		SDL_DestroyTexture (this->_mainMenuTexture);

	if (this->_mainMenuImage != NULL)
		SDL_FreeSurface (this->_mainMenuImage);

	if (this->_boardRenderer != NULL)
		SDL_DestroyRenderer (this->_boardRenderer);

	if (this->_window != NULL)
		SDL_DestroyWindow (this->_window);

	Mix_Quit();

	TTF_Quit();

	IMG_Quit();

	SDL_Quit();

	unsetenv (SDLenv);
}

/*
 * Private
 */
void						GUISDL::ajustBounds (void)
{
	this->_menuLeftButton.scale (_mapWidth , _mapHeight, 1000);
	this->_menuRightButton.scale (_mapWidth , _mapHeight, 1000);
	this->_menuMiddleButton.scale (_mapWidth , _mapHeight, 1000);
	this->_menuBottomButton.scale (_mapWidth , _mapHeight, 1000);

	this->_mapLTButton.scale (_mapWidth , _mapHeight, 1000);
	this->_mapLMButton.scale (_mapWidth , _mapHeight, 1000);
	this->_mapLBButton.scale (_mapWidth , _mapHeight, 1000);
	this->_mapCTButton.scale (_mapWidth , _mapHeight, 1000);
	this->_mapCMButton.scale (_mapWidth , _mapHeight, 1000);
	this->_mapCBButton.scale (_mapWidth , _mapHeight, 1000);
	this->_mapRTButton.scale (_mapWidth , _mapHeight, 1000);
	this->_mapRMButton.scale (_mapWidth , _mapHeight, 1000);
	this->_mapRBButton.scale (_mapWidth , _mapHeight, 1000);
}

void						GUISDL::drawMainMenu (void)
{
	eboadMode boardCurrentMode;
	std::string mainString;
	SDL_Rect textDimension;
	SDL_Color textColor, textBGColor;

	if (this->_mainMenuImage != NULL)
		SDL_FreeSurface (this->_mainMenuImage);

	this->_mainMenuImage = IMG_Load ("ressources/images/main_menu.png");
	if (this->_mainMenuImage == NULL)
	{
		throw GUIException (eGUIString (this->_GUI), "IMG_Load GUISDL::drawMainMenu", IMG_GetError());
	}

	if (this->_mainMenuTexture != NULL)
		SDL_DestroyTexture (this->_mainMenuTexture);

	this->_mainMenuTexture = SDL_CreateTextureFromSurface (this->_boardRenderer, this->_mainMenuImage);
	if (this->_mainMenuTexture == NULL)
	{
		throw GUIException (eGUIString (this->_GUI), "SDL_CreateTextureFromSurface GUISDL::drawMainMenu", SDL_GetError());
	}

	if (SDL_RenderCopy (this->_boardRenderer, this->_mainMenuTexture, NULL, NULL))
	{
		throw GUIException (eGUIString (this->_GUI), "SDL_RenderCopy GUISDL::drawMainMenu", SDL_GetError());
	}

	/* Printing Nibbler Mode */

	boardCurrentMode = this->_board->getBoardMode();

	mainString = "Current Mode: ";
	if ((boardCurrentMode | eboadMode::Default) == eboadMode::Default)
		mainString += "Default";
	else
	{
		switch (static_cast <unsigned int> (boardCurrentMode))
		{
			case eboadMode::SpecialFood:
				mainString += "SpecialFood";
				break;
			case eboadMode::NoFriendlyFire:
				mainString += "NoFriendlyFire";
				break;
			case eboadMode::Endless:
				mainString += "Endless";
				break;
			case eboadMode::Multiplayer:
				mainString += "Multiplayer";
				break;
			case eboadMode::SpecialFood | eboadMode::NoFriendlyFire:
				mainString += "SpecialFood | NoFriendlyFire";
				break;
			case eboadMode::SpecialFood | eboadMode::Endless:
				mainString += "SpecialFood | Endless";
				break;
			case eboadMode::SpecialFood | eboadMode::Multiplayer:
				mainString += "SpecialFood | Multiplayer";
				break;
			case eboadMode::NoFriendlyFire | eboadMode::Endless:
				mainString += "NoFriendlyFire | Endless";
				break;
			case eboadMode::NoFriendlyFire | eboadMode::Multiplayer:
				mainString += "NoFriendlyFire | Multiplayer";
				break;
			case eboadMode::Endless | eboadMode::Multiplayer:
				mainString += "Endless | Multiplayer";
				break;
			case eboadMode::SpecialFood | eboadMode::NoFriendlyFire | eboadMode::Endless:
				mainString += "SpecialFood | NoFriendlyFire | Endless";
				break;
			case eboadMode::SpecialFood | eboadMode::NoFriendlyFire | eboadMode::Multiplayer:
				mainString += "SpecialFood | NoFriendlyFire | Multiplayer";
				break;
			case eboadMode::SpecialFood | eboadMode::Endless | eboadMode::Multiplayer:
				mainString += "SpecialFood | Endless | Multiplayer";
				break;
			case eboadMode::NoFriendlyFire | eboadMode::Endless | eboadMode::Multiplayer:
				mainString += "NoFriendlyFire | Endless | Multiplayer";
				break;
			case eboadMode::SpecialFood | eboadMode::NoFriendlyFire | eboadMode::Endless | eboadMode::Multiplayer:
				mainString += "SpecialFood | NoFriendlyFire | Endless | Multiplayer";
				break;
			default:
				mainString += "????";
				break;
		}
	}

	textColor.r = 0;
	textColor.g = 0;
	textColor.b = 0;
	textColor.a = 255;

	textBGColor.r = 255;
	textBGColor.g = 255;
	textBGColor.b = 255;
	textBGColor.a = 255;

	if (this->_mainTextImage != NULL)
		SDL_FreeSurface (this->_mainTextImage);

	this->_mainTextImage = TTF_RenderUTF8_Shaded (this->_mainTextPolice, mainString.c_str(), textColor, textBGColor);
	if (this->_mainTextImage == NULL)
	{
		throw GUIException (eGUIString (this->_GUI), "TTF_RenderUTF8_Shaded 0", TTF_GetError());
	}

	if (this->_mainTextTexture != NULL)
		SDL_DestroyTexture (this->_mainTextTexture);

	this->_mainTextTexture = SDL_CreateTextureFromSurface (this->_boardRenderer, this->_mainTextImage);
	if (this->_mainTextTexture == NULL)
	{
		throw GUIException (eGUIString (this->_GUI), "SDL_CreateTextureFromSurface 0 GUISDL::drawScore", SDL_GetError());
	}

	textDimension.x = 10;
	textDimension.y = 3;
	textDimension.w = this->_mainTextImage->w;
	textDimension.h = this->_mainTextImage->h;

	if (SDL_RenderCopy (this->_boardRenderer, this->_mainTextTexture, NULL, &textDimension))
	{
		throw GUIException (eGUIString (this->_GUI), "SDL_RenderCopy 0 GUISDL::drawScore", SDL_GetError());
	}
}

void						GUISDL::drawMapSelection (void)
{
	if (this->_mapSelectionImage != NULL)
		SDL_FreeSurface (this->_mapSelectionImage);

	this->_mapSelectionImage = IMG_Load ("ressources/images/map_selection.png");
	if (this->_mapSelectionImage == NULL)
	{
		throw GUIException (eGUIString (this->_GUI), "IMG_Load GUISDL::drawMapSelection", IMG_GetError());
	}

	if (this->_mapSelectionTexture != NULL)
		SDL_DestroyTexture (this->_mapSelectionTexture);

	this->_mapSelectionTexture = SDL_CreateTextureFromSurface (this->_boardRenderer, this->_mapSelectionImage);
	if (this->_mapSelectionTexture == NULL)
	{
		throw GUIException (eGUIString (this->_GUI), "SDL_CreateTextureFromSurface GUISDL::drawMapSelection", SDL_GetError());
	}

	if (SDL_RenderCopy (this->_boardRenderer, this->_mapSelectionTexture, NULL, NULL))
	{
		throw GUIException (eGUIString (this->_GUI), "SDL_RenderCopy GUISDL::drawMapSelection", SDL_GetError());
	}
}

void						GUISDL::drawBoard (void)
{
	unsigned int height, width, y, x;
	std::vector< std::vector<int> > *boardCells;
	SDL_Rect boardCellDraw;
	Uint8 r, g, b;

	if (SDL_SetRenderDrawColor (this->_boardRenderer, 255, 255, 255, 255))
	{
		throw GUIException (eGUIString (this->_GUI), "SDL_SetRenderDrawColor GUISDL::drawBoard", SDL_GetError());
	}
	if (SDL_RenderClear (this->_boardRenderer))		/* use the RenderDrawColor to clear the Renderer */
	{
		throw GUIException (eGUIString (this->_GUI), "SDL_RenderClear GUISDL::drawBoard", SDL_GetError());
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
					throw GUIException (eGUIString (this->_GUI), "SDL_SetRenderDrawColor GUISDL::drawBoard", SDL_GetError());
				}

				boardCellDraw.x = x * 10;
				boardCellDraw.y = this->_textHeight + y * 10;
				boardCellDraw.w = 10;
				boardCellDraw.h = 10;

				if (SDL_RenderFillRect (this->_boardRenderer, &boardCellDraw))
				{
					throw GUIException (eGUIString (this->_GUI), "SDL_RenderFillRect GUISDL::drawBoard", SDL_GetError());
				}
			}
		}
	}
}

void						GUISDL::drawSnakes (void)
{
	std::list<t_cell> snakeCells;
	std::list<t_cell>::iterator itSnakeCell;
	SDL_Rect headCellDraw, snakeCellDraw;
	bool head;

	snakeCells = this->_snakeP1->getSnakeCells();

	if (SDL_SetRenderDrawColor (this->_boardRenderer, 0, 255, 0, 255))
	{
		throw GUIException (eGUIString (this->_GUI), "SDL_SetRenderDrawColor GUISDL::drawSnake P1", SDL_GetError());
	}

	head = true;
	for (itSnakeCell = snakeCells.begin(); itSnakeCell != snakeCells.end(); ++itSnakeCell)
	{
		snakeCellDraw.x = itSnakeCell->positionX * 10;
		snakeCellDraw.y = this->_textHeight + itSnakeCell->positionY * 10;
		snakeCellDraw.w = 10;
		snakeCellDraw.h = 10;

		if (head)
		{
			headCellDraw = snakeCellDraw;
			head = false;
			continue;
		}

		if (SDL_RenderFillRect (this->_boardRenderer, &snakeCellDraw))
		{
			throw GUIException (eGUIString (this->_GUI), "SDL_RenderFillRect GUISDL::drawSnake P1", SDL_GetError());
		}
	}

	if (SDL_SetRenderDrawColor (this->_boardRenderer, 0, 128, 0, 255))
	{
		throw GUIException (eGUIString (this->_GUI), "SDL_SetRenderDrawColor GUISDL::drawSnake P1", SDL_GetError());
	}

	if (SDL_RenderFillRect (this->_boardRenderer, &headCellDraw))
	{
		throw GUIException (eGUIString (this->_GUI), "SDL_RenderFillRect HEAD GUISDL::drawSnake P1", SDL_GetError());
	}

	if (this->_snakeP2)
	{
		snakeCells = this->_snakeP2->getSnakeCells();

		if (SDL_SetRenderDrawColor (this->_boardRenderer, 0, 255, 255, 255))
		{
			throw GUIException (eGUIString (this->_GUI), "SDL_SetRenderDrawColor GUISDL::drawSnake P2", SDL_GetError());
		}

		head = true;
		for (itSnakeCell = snakeCells.begin(); itSnakeCell != snakeCells.end(); ++itSnakeCell)
		{
			snakeCellDraw.x = itSnakeCell->positionX * 10;
			snakeCellDraw.y = this->_textHeight + itSnakeCell->positionY * 10;
			snakeCellDraw.w = 10;
			snakeCellDraw.h = 10;

			if (head)
			{
				headCellDraw = snakeCellDraw;
				head = false;
				continue;
			}

			if (SDL_RenderFillRect (this->_boardRenderer, &snakeCellDraw))
			{
				throw GUIException (eGUIString (this->_GUI), "SDL_RenderFillRect GUISDL::drawSnake P2", SDL_GetError());
			}
		}

		if (SDL_SetRenderDrawColor (this->_boardRenderer, 0, 128, 128, 255))
		{
			throw GUIException (eGUIString (this->_GUI), "SDL_SetRenderDrawColor GUISDL::drawSnake P2", SDL_GetError());
		}

		if (SDL_RenderFillRect (this->_boardRenderer, &headCellDraw))
		{
			throw GUIException (eGUIString (this->_GUI), "SDL_RenderFillRect HEAD GUISDL::drawSnake P1", SDL_GetError());
		}
	}
}

void						GUISDL::drawScore (void)
{
	SDL_Color textColor, textBGColor;
	unsigned int snakeScore;
	std::string scoreString;
	int boardCompletedScore;
	SDL_Rect textDimension;

	/* Clearing Score zone */

	textColor.r = 255;
	textColor.g = 255;
	textColor.b = 255;
	textColor.a = 255;

	textBGColor.r = 0x33;
	textBGColor.g = 0x33;
	textBGColor.b = 0x33;
	textBGColor.a = 255;

	if (SDL_SetRenderDrawColor (this->_boardRenderer, textBGColor.r, textBGColor.g, textBGColor.b, textBGColor.a))
	{
		throw GUIException (eGUIString (this->_GUI), "SDL_SetRenderDrawColor GUISDL::drawBoard", SDL_GetError());
	}

	textDimension.x = 0;
	textDimension.y = 0;
	textDimension.w = _mapWidth;
	textDimension.h = this->_textHeight;

	if (SDL_RenderFillRect (this->_boardRenderer, &textDimension))
	{
		throw GUIException (eGUIString (this->_GUI), "SDL_RenderFillRect GUISDL::drawBoard", SDL_GetError());
	}

	/* Setting Score Text */

	snakeScore = this->_snakeP1->getScore();

	scoreString = "Player1: ";
	if (snakeScore >= SNAKE_SCORE_MAX)
		scoreString += "MAX";
	else
		scoreString += std::to_string (snakeScore);
	scoreString += "/";
	boardCompletedScore = this->_board->getBoardCompletedScore();
	if (boardCompletedScore != -1)
		scoreString += std::to_string (boardCompletedScore);
	else
		scoreString += "∞";

	if (this->_scoreP1TextImage != NULL)
		SDL_FreeSurface (this->_scoreP1TextImage);

	this->_scoreP1TextImage = TTF_RenderUTF8_Shaded (this->_scoreTextPolice, scoreString.c_str(), textColor, textBGColor);
	if (this->_scoreP1TextImage == NULL)
	{
		throw GUIException (eGUIString (this->_GUI), "TTF_RenderUTF8_Shaded 1", TTF_GetError());
	}

	if (this->_snakeP2)
	{
		snakeScore = this->_snakeP2->getScore();

		scoreString = "Player2: ";
		if (snakeScore >= SNAKE_SCORE_MAX)
			scoreString += "MAX";
		else
			scoreString += std::to_string (snakeScore);
		scoreString += "/";
		boardCompletedScore = this->_board->getBoardCompletedScore();
		if (boardCompletedScore != -1)
			scoreString += std::to_string (boardCompletedScore);
		else
			scoreString += "∞";

		if (this->_scoreP2TextImage != NULL)
			SDL_FreeSurface (this->_scoreP2TextImage);

		this->_scoreP2TextImage = TTF_RenderUTF8_Shaded (this->_scoreTextPolice, scoreString.c_str(), textColor, textBGColor);
		if (this->_scoreP2TextImage == NULL)
		{
			throw GUIException (eGUIString (this->_GUI), "TTF_RenderUTF8_Shaded 2", TTF_GetError());
		}
	}

	/* Printing Score Text */

	if (this->_scoreP1TextTexture != NULL)
		SDL_DestroyTexture (this->_scoreP1TextTexture);

	this->_scoreP1TextTexture = SDL_CreateTextureFromSurface (this->_boardRenderer, this->_scoreP1TextImage);
	if (this->_scoreP1TextTexture == NULL)
	{
		throw GUIException (eGUIString (this->_GUI), "SDL_CreateTextureFromSurface 1 GUISDL::drawScore", SDL_GetError());
	}

	textDimension.x = 10;
	textDimension.y = 3;
	textDimension.w = this->_scoreP1TextImage->w;
	textDimension.h = this->_textHeight - 6;
	if (SDL_RenderCopy (this->_boardRenderer, this->_scoreP1TextTexture, NULL, &textDimension))
	{
		throw GUIException (eGUIString (this->_GUI), "SDL_RenderCopy 1 GUISDL::drawScore", SDL_GetError());
	}

	if (this->_snakeP2)
	{
		if (this->_scoreP2TextTexture != NULL)
			SDL_DestroyTexture (this->_scoreP2TextTexture);

		this->_scoreP2TextTexture = SDL_CreateTextureFromSurface (this->_boardRenderer, this->_scoreP2TextImage);
		if (this->_scoreP2TextTexture == NULL)
		{
			throw GUIException (eGUIString (this->_GUI), "SDL_CreateTextureFromSurface 2 GUISDL::drawScore", SDL_GetError());
		}

		textDimension.x = (_mapWidth - 10) - this->_scoreP2TextImage->w;
		textDimension.y = 3;
		textDimension.w = this->_scoreP2TextImage->w;
		textDimension.h = this->_textHeight - 6;
		if (SDL_RenderCopy (this->_boardRenderer, this->_scoreP2TextTexture, NULL, &textDimension))
		{
			throw GUIException (eGUIString (this->_GUI), "SDL_RenderCopy 2 GUISDL::drawScore", SDL_GetError());
		}
	}
}

void						GUISDL::drawEndMenu (void)
{
	eBoardStatus boardStatus;
	std::string endMenuFilename;

	if (this->_endMenuImage != NULL)
		SDL_FreeSurface (this->_endMenuImage);

	boardStatus = this->_board->getBoardStatus();
	switch (boardStatus)
	{
		case eBoardStatus::Player1Win:
			if (! this->_snakeP2)
				endMenuFilename = "ressources/images/singleplayer_win.png";
			else
				endMenuFilename = "ressources/images/multiplayer_player1_win.png";
			break;
		case eBoardStatus::Player1Lose:
			if (! this->_snakeP2)
				endMenuFilename = "ressources/images/singleplayer_lose.png";
			else
				endMenuFilename = "ressources/images/multiplayer_player2_win.png";
			break;
		case eBoardStatus::Player2Win:
			endMenuFilename = "ressources/images/multiplayer_player2_win.png";
			break;
		case eBoardStatus::Player2Lose:
			endMenuFilename = "ressources/images/multiplayer_player1_win.png";
			break;
		case eBoardStatus::Draw:
			endMenuFilename = "ressources/images/multiplayer_draw.png";
			break;
		case eBoardStatus::Forfeit:
			endMenuFilename = "ressources/images/end_menu_forfeit.png";
			break;
		default:
			throw ShouldNeverOccurException (__FILE__, __LINE__);
	}

	this->_endMenuImage = IMG_Load (endMenuFilename.c_str());
	if (this->_endMenuImage == NULL)
	{
		throw GUIException (eGUIString (this->_GUI), "IMG_Load GUISDL::drawEndMenu", IMG_GetError());
	}

	if (this->_endMenuTexture != NULL)
		SDL_DestroyTexture (this->_endMenuTexture);

	this->_endMenuTexture = SDL_CreateTextureFromSurface (this->_boardRenderer, this->_endMenuImage);
	if (this->_endMenuTexture == NULL)
	{
		throw GUIException (eGUIString (this->_GUI), "SDL_CreateTextureFromSurface GUISDL::drawEndMenu", SDL_GetError());
	}

	if (SDL_RenderCopy (this->_boardRenderer, this->_endMenuTexture, NULL, NULL))
	{
		throw GUIException (eGUIString (this->_GUI), "SDL_RenderCopy GUISDL::drawEndMenu", SDL_GetError());
	}
}

/*
 * Public
 */
eGUI						GUISDL::getGUIName (void) const
{
	return this->_GUI;
}

void						GUISDL::start (void)
{
	unsigned int scalingFactor, mainFontSize;

	print_trace ("GUISDL::start", true);

	_mapWidth = this->_board->getWidth() * 10;
	_mapHeight = this->_textHeight + this->_board->getHeight() * 10;


	this->_window = SDL_CreateWindow ("Nibbler (SDL GUI)",
									  SDL_WINDOWPOS_CENTERED,
									  SDL_WINDOWPOS_CENTERED,
									  _mapWidth, _mapHeight, SDL_WINDOW_SHOWN);
	if (this->_window == NULL)
	{
		throw GUIException (eGUIString (this->_GUI), "SDL_CreateWindow"), SDL_GetError();
	}

	this->_boardRenderer = SDL_CreateRenderer (this->_window, -1, SDL_RENDERER_ACCELERATED);
	if (this->_boardRenderer == NULL)
	{
		throw GUIException (eGUIString (this->_GUI), "SDL_CreateRenderer", SDL_GetError());
	}

	this->ajustBounds ();

	scalingFactor = (this->_board->getWidth() + this->_board->getHeight()) * 100 / (30 + 30 /* minimum possible board size*/);
	mainFontSize = 10 * scalingFactor / 100;

	print_trace ("Scaling Factor = ", false);
	print_trace (scalingFactor, false);
	print_trace (" | mainFontSize = ", false);
	print_trace (mainFontSize, true);

	this->_mainTextPolice = TTF_OpenFont ("ressources/fonts/FreeMono.ttf", mainFontSize);
	if (! this->_mainTextPolice)
	{
		throw GUIException (eGUIString (this->_GUI), "TTF_OpenFont 1", TTF_GetError());
	}

	this->_scoreTextPolice = TTF_OpenFont ("ressources/fonts/Ubuntu-MI.ttf", 18);
	if (! this->_scoreTextPolice)
	{
		throw GUIException (eGUIString (this->_GUI), "TTF_OpenFont 3", TTF_GetError());
	}

	this->_mainMenuMusic = Mix_LoadMUS ("ressources/sounds/ff_main_menu.wav");
	if (! this->_mainMenuMusic)
	{
		throw GUIException (eGUIString (this->_GUI), "Mix_LoadMUS 1", Mix_GetError());
	}

	this->_mapSelectionMusic = Mix_LoadMUS ("ressources/sounds/ff_main_theme.wav");
	if (! this->_mapSelectionMusic)
	{
		throw GUIException (eGUIString (this->_GUI), "Mix_LoadMUS _mapSelectionMusic", Mix_GetError());
	}

	Mix_VolumeMusic (this->_musicVolume);

	this->_started = true;
}

bool						GUISDL::alreadyStarted (void) const
{
	return this->_started;
}

eGUI						GUISDL::wantedGUI (void) const
{
	return this->_wantedGUI;
}

void						GUISDL::stop()
{
	print_trace ("GUISDL::stop", true);

	if (! this->_started)
	{
		throw GUIException (eGUIString (this->_GUI), "GUISDL::stop => GUISDL wasn't started");
	}

	if (this->_mainMenuMusic != NULL)
	{
		Mix_FreeMusic (this->_mainMenuMusic);
		this->_mainMenuMusic = NULL;
	}

	if (this->_mapSelectionMusic != NULL)
	{
		Mix_FreeMusic (this->_mapSelectionMusic);
		this->_mapSelectionMusic = NULL;
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

	if (this->_mainTextPolice != NULL)
	{
		TTF_CloseFont (this->_mainTextPolice);
		this->_mainTextPolice = NULL;
	}

	if (this->_scoreTextPolice != NULL)
	{
		TTF_CloseFont (this->_scoreTextPolice);
		this->_scoreTextPolice = NULL;
	}

	if (this->_window != NULL)
	{
		SDL_DestroyWindow (this->_window);
		this->_window = NULL;
	}

	this->_started = false;
}

/* Main Menu */

void						GUISDL::loadMainMenu (void)
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

eGUIMainMenuEvent			GUISDL::getMainMenuEvent (void)
{
	SDL_Event events;
	int x, y;

	while (SDL_PollEvent (&events))
	{
		switch (events.type)
		{
			case SDL_QUIT:
				return eGUIMainMenuEvent::quitGame;

			case SDL_WINDOWEVENT:
				switch (events.window.event)
				{
					case SDL_WINDOWEVENT_EXPOSED:
						SDL_RenderPresent (this->_boardRenderer);
						break;
					default:
						break;
				}
				break;

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
						this-> _wantedGUI = eGUI::Allegro;
						return eGUIMainMenuEvent::changeGUI;

					/* Audio */
					case SDLK_p:
						if (Mix_PausedMusic() == 1)
							Mix_ResumeMusic();
						else
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

					if (this->_menuRightButton.in (x, y))
						return eGUIMainMenuEvent::startMultiPlayerGame;

					if (this->_menuMiddleButton.in (x, y))
						return eGUIMainMenuEvent::quitGame;
				}
				break;

			default:
				break;
		}
	}

	return eGUIMainMenuEvent::nothingTODO;
}

/* Map Selection */

void						GUISDL::loadMapSelection (void)
{
	if (Mix_PausedMusic() == 1)
	{
		Mix_HaltMusic();
		Mix_PlayMusic (this->_mapSelectionMusic, -1);
		Mix_PauseMusic();
	}
	else
	{
		Mix_HaltMusic();
		Mix_PlayMusic (this->_mapSelectionMusic, -1);
	}

	this->drawMapSelection();

	SDL_RenderPresent (this->_boardRenderer);
}

eGUIMapSelectionEvent		GUISDL::getMapSelectionEvent (void)
{
	SDL_Event events;
	int x, y;

	while (SDL_PollEvent (&events))
	{
		switch (events.type)
		{
			case SDL_QUIT:
				return eGUIMapSelectionEvent::quitGame;

			case SDL_WINDOWEVENT:
				switch (events.window.event)
				{
					case SDL_WINDOWEVENT_EXPOSED:
						SDL_RenderPresent (this->_boardRenderer);
						break;
					default:
						break;
				}
				break;

			case SDL_KEYDOWN:
				switch (events.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						return eGUIMapSelectionEvent::quitGame;

					/* GUI Switchs */
					case SDLK_2:
					case SDLK_F2:
					case SDLK_KP_2:
						this-> _wantedGUI = eGUI::SFML;
						return eGUIMapSelectionEvent::changeGUI;

					case SDLK_3:
					case SDLK_F3:
					case SDLK_KP_3:
						this-> _wantedGUI = eGUI::Allegro;
						return eGUIMapSelectionEvent::changeGUI;

					/* Audio */
					case SDLK_p:
						if (Mix_PausedMusic() == 1)
							Mix_ResumeMusic();
						else
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

					if (this->_mapLTButton.in (x, y))
							return eGUIMapSelectionEvent::mapLT;

					if (this->_mapLMButton.in (x, y))
						return eGUIMapSelectionEvent::mapLM;

					if (this->_mapLBButton.in (x, y))
						return eGUIMapSelectionEvent::mapLB;

					if (this->_mapCTButton.in (x, y))
						return eGUIMapSelectionEvent::mapCT;

					if (this->_mapCMButton.in (x, y))
						return eGUIMapSelectionEvent::mapCM;

					if (this->_mapCBButton.in (x, y))
						return eGUIMapSelectionEvent::mapCB;

					if (this->_mapRTButton.in (x, y))
						return eGUIMapSelectionEvent::mapRT;

					if (this->_mapRMButton.in (x, y))
						return eGUIMapSelectionEvent::mapRM;

					if (this->_mapRBButton.in (x, y))
						return eGUIMapSelectionEvent::mapRB;
				}
				break;

			default:
				break;
		}
	}

	return eGUIMapSelectionEvent::nothingTODO;
}

/* Game */

void						GUISDL::setPlayers (Snake *snakeP1, Snake *snakeP2)
{
	if (! snakeP1)
	{
		throw InvalidArgumentException ("GUISDL::setPlayers: snakeP1 == null");
	}

	this->_snakeP1 = snakeP1;
	this->_snakeP2 = snakeP2;
}

void						GUISDL::loadBoard (unsigned int soundTrack)
{
	std::string boardMusicName;

	switch (soundTrack)
	{
		case 0:
			boardMusicName = "ressources/sounds/Twin Musicom - NES Theme.wav";
			break;

		case 1:
			boardMusicName = "ressources/sounds/Twin Musicom - NES Boss.wav";
			break;

		case 2:
			boardMusicName = "ressources/sounds/Twin Musicom - 8-bit March.wav";
			break;

		case 3:
		default:
			boardMusicName = "ressources/sounds/Twin Musicom - NES Theme.wav";
			break;
	}

	if (this->_boardMusic != NULL)
	{
		Mix_FreeMusic (this->_boardMusic);
		this->_boardMusic = NULL;
	}

	this->_boardMusic = Mix_LoadMUS (boardMusicName.c_str());
	if (! this->_boardMusic)
	{
		throw GUIException (eGUIString (this->_GUI), "Mix_LoadMUS", Mix_GetError());
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

void						GUISDL::updateGameGUI (void)
{
	int boardCompletedScore;
	unsigned int currentGlobalScore;
	unsigned int speed;

	this->drawBoard();
	this->drawSnakes();
	this->drawScore();

	SDL_RenderPresent (this->_boardRenderer);

	currentGlobalScore = this->_snakeP1->getScore();
	if (this->_snakeP2)
		currentGlobalScore = currentGlobalScore > this->_snakeP2->getScore() ?
							 currentGlobalScore :
							 this->_snakeP2->getScore();

	if (currentGlobalScore > 95)
		currentGlobalScore = 95;

	boardCompletedScore = this->_board->getBoardCompletedScore();
	if (boardCompletedScore <= -1)
		speed = 100 - currentGlobalScore;
	else
	{
		switch (boardCompletedScore)
		{
			case 20 ... 24:
				speed = 100 - (currentGlobalScore * 50 / (boardCompletedScore - 1));
				break;
			case 25 ... 29:
				speed = 100 - (currentGlobalScore * 52 / (boardCompletedScore - 1));
				break;
			case 30 ... 34:
				speed = 100 - (currentGlobalScore * 54 / (boardCompletedScore - 1));
				break;
			case 35 ... 39:
				speed = 100 - (currentGlobalScore * 58 / (boardCompletedScore - 1));
				break;
			case 40 ... 44:
				speed = 100 - (currentGlobalScore * 60 / (boardCompletedScore - 1));
				break;
			case 45 ... 49:
				speed = 100 - (currentGlobalScore * 62 / (boardCompletedScore - 1));
				break;
			case 50 ... 54:
				speed = 100 - (currentGlobalScore * 66 / (boardCompletedScore - 1));
				break;
			case 55 ... 59:
				speed = 100 - (currentGlobalScore * 68 / (boardCompletedScore - 1));
				break;
			case 60 ... 64:
				speed = 100 - (currentGlobalScore * 70 / (boardCompletedScore - 1));
				break;
			default:
				speed = 100 - (currentGlobalScore * 80 / (boardCompletedScore - 1));
				break;
		}
	}

	if (! (boardCompletedScore <= -1 && currentGlobalScore >= 100))
		SDL_Delay (speed);
}

eGUIGameEvent				GUISDL::getGameEvent (void)
{
	SDL_Event events;
	eSnakeDirection snakeP1CurrentDirection, snakeP2CurrentDirection;

	snakeP1CurrentDirection = this->_snakeP1->getCurrentDirection();
	if (this->_snakeP2)
		snakeP2CurrentDirection = this->_snakeP2->getCurrentDirection();

	while (SDL_PollEvent (&events))
	{
		switch (events.type)
		{
			case SDL_QUIT:
				return eGUIGameEvent::quitGame;

			case SDL_WINDOWEVENT:
				switch (events.window.event)
				{
					case SDL_WINDOWEVENT_EXPOSED:
						SDL_RenderPresent (this->_boardRenderer);
						break;
					default:
						break;
				}
				break;

			case SDL_KEYDOWN:

				switch (events.key.keysym.sym)
				{
#ifdef DEBUG_MODE
					case SDLK_e:
						this->_snakeP1->eat (1);
						break;

					case SDLK_r:
						if (this->_snakeP2)
							this->_snakeP2->eat (1);
						break;
#endif
					case SDLK_f:
						return eGUIGameEvent::forfeitGame;

					case SDLK_ESCAPE:
						return eGUIGameEvent::quitGame;

					/* Player 1 commands */
					case SDLK_LEFT:
						if ((snakeP1CurrentDirection != eSnakeDirection::West) &&
							(snakeP1CurrentDirection != eSnakeDirection::East))
							return eGUIGameEvent::p1GoLeft;
						break;

					case SDLK_RIGHT:
						if ((snakeP1CurrentDirection != eSnakeDirection::West) &&
							(snakeP1CurrentDirection != eSnakeDirection::East))
							return eGUIGameEvent::p1GoRight;
						break;

					case SDLK_UP:
						if ((snakeP1CurrentDirection != eSnakeDirection::North) &&
							(snakeP1CurrentDirection != eSnakeDirection::South))
							return eGUIGameEvent::p1GoUp;
						break;

					case SDLK_DOWN:
						if ((snakeP1CurrentDirection != eSnakeDirection::North) &&
							(snakeP1CurrentDirection != eSnakeDirection::South))
							return eGUIGameEvent::p1GoDown;
						break;

					/* Player 2 commands */
					case SDLK_q:
						if (this->_snakeP2)
							if ((snakeP2CurrentDirection != eSnakeDirection::West) &&
								(snakeP2CurrentDirection != eSnakeDirection::East))
								return eGUIGameEvent::p2GoLeft;
						break;

					case SDLK_d:
						if (this->_snakeP2)
							if ((snakeP2CurrentDirection != eSnakeDirection::West) &&
								(snakeP2CurrentDirection != eSnakeDirection::East))
								return eGUIGameEvent::p2GoRight;
						break;

					case SDLK_z:
						if (this->_snakeP2)
							if ((snakeP2CurrentDirection != eSnakeDirection::North) &&
								(snakeP2CurrentDirection != eSnakeDirection::South))
								return eGUIGameEvent::p2GoUp;
						break;

					case SDLK_s:
						if (this->_snakeP2)
							if ((snakeP2CurrentDirection != eSnakeDirection::North) &&
								(snakeP2CurrentDirection != eSnakeDirection::South))
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
						this-> _wantedGUI = eGUI::Allegro;
						return eGUIGameEvent::changeGUI;

					/* Audio */
					case SDLK_p:
						if (Mix_PausedMusic() == 1)
							Mix_ResumeMusic();
						else
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

void						GUISDL::loadEndMenu (void)
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
		case eBoardStatus::Forfeit:
			endMenuMusicName = "ressources/sounds/end_menu_forfeit.wav";
			break;
		default:
			throw ShouldNeverOccurException (__FILE__, __LINE__);
	}

	this->_endMenuMusic = Mix_LoadMUS (endMenuMusicName.c_str());
	if (! this->_endMenuMusic)
	{
		throw GUIException (eGUIString (this->_GUI), std::string ("Mix_LoadMUS \"") + endMenuMusicName.c_str() + "\"", Mix_GetError());
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

eGUIEndMenuEvent			GUISDL::getEndMenuEvent (void)
{
	SDL_Event events;
	int x, y;

	while (SDL_PollEvent (&events))
	{
		switch (events.type)
		{
			case SDL_QUIT:
				return eGUIEndMenuEvent::quitGame;

			case SDL_WINDOWEVENT:
				switch (events.window.event)
				{
					case SDL_WINDOWEVENT_EXPOSED:
						SDL_RenderPresent (this->_boardRenderer);
						break;
					default:
						break;
				}
				break;

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
						this-> _wantedGUI = eGUI::Allegro;
						return eGUIEndMenuEvent::changeGUI;

					/* Audio */
					case SDLK_p:
						if (Mix_PausedMusic() == 1)
							Mix_ResumeMusic();
						else
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

					if (this->_menuRightButton.in (x, y))
						return eGUIEndMenuEvent::nextLevel;

					if (this->_menuMiddleButton.in (x, y))
						return eGUIEndMenuEvent::backToLobby;

					if (this->_menuBottomButton.in (x, y))
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
GUISDL						*createGUI (Board *board)
{
	return new GUISDL (board);
}

void						destroyGUI (GUISDL *GUI)
{
	delete GUI;
}
