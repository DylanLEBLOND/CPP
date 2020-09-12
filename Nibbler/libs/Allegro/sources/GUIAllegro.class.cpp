#include <GUIAllegro.class.hpp>

static unsigned int _mapWidth;
static unsigned int _mapHeight;

/*
 * Constructors
 */
GUIAllegro::GUIAllegro (Board *board)
	: _board (board), _snakeP1 (NULL), _snakeP2 (NULL), _wantedGUI (eGUI::Allegro),
	  _eventQueue (NULL), _window (NULL), _boardBitmap (NULL), _mainMenuImage (NULL),
	  _mapSelectionImage (NULL), _endMenuImage (NULL),
	  _textHeight (26), _mainTextPolice (NULL), _scoreTextPolice (NULL),
	  _mainMenuSample (NULL), _mapSelectionSample (NULL), _boardSample (NULL), _endMenuSample (NULL),
	  _mainMenuMusic (NULL), _mapSelectionMusic (NULL), _boardMusic (NULL),
	  _musicVolume (1.0f), _muted (false),
	  _started (false)
{
	if (! board)
	{
		throw InvalidArgumentException ("GUIAllegro::GUIAllegro (Board *board, Snake *snake): board == null");
	}

	if (! al_init())
	{
		throw GUIException (this->_GUIName, "al_init");
	}

	if (! al_init_primitives_addon())
	{
		throw GUIException (this->_GUIName, "al_init_primitives_addon");
	}

	if (! al_install_keyboard())
	{
		throw GUIException (this->_GUIName, "al_install_keyboard");
	}

	if (! al_install_mouse())
	{
		throw GUIException (this->_GUIName, "al_install_mouse");
	}

	if (! al_init_image_addon())
	{
		throw GUIException (this->_GUIName, "al_init_image_addon");
	}

	if (! al_init_font_addon())
	{
		throw GUIException (this->_GUIName, "al_init_font_addon");
	}

	if (! al_init_ttf_addon())
	{
		throw GUIException (this->_GUIName, "al_init_ttf_addon");
	}

	if (! al_install_audio())
	{
		throw GUIException (this->_GUIName, "al_install_audio");
	}

	if (! al_init_acodec_addon())
	{
		throw GUIException (this->_GUIName, "al_init_acodec_addon");
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
GUIAllegro::~GUIAllegro (void)
{
	if (this->_endMenuSample != NULL)
		al_destroy_sample (this->_endMenuSample);

	if (this->_boardMusic != NULL)
		al_destroy_sample_instance (this->_boardMusic);

	if (this->_boardSample != NULL)
		al_destroy_sample (this->_boardSample);

	if (this->_mapSelectionMusic != NULL)
		al_destroy_sample_instance (this->_mapSelectionMusic);

	if (this->_mapSelectionSample != NULL)
		al_destroy_sample (this->_mapSelectionSample);

	if (this->_mainMenuMusic != NULL)
		al_destroy_sample_instance (this->_mainMenuMusic);

	if (this->_mainMenuSample != NULL)
		al_destroy_sample (this->_mainMenuSample);

	if (this->_endMenuImage != NULL)
		al_destroy_bitmap (this->_endMenuImage);

	if (this->_mapSelectionImage != NULL)
		al_destroy_bitmap (this->_mapSelectionImage);

	if (this->_mainMenuImage != NULL)
		al_destroy_bitmap (this->_mainMenuImage);

	if (this->_scoreTextPolice != NULL)
		al_destroy_font (this->_scoreTextPolice);

	if (this->_mainTextPolice != NULL)
		al_destroy_font (this->_mainTextPolice);

	if (this->_eventQueue != NULL)
		al_destroy_event_queue (this->_eventQueue);

	if (this->_boardBitmap != NULL)
		al_destroy_bitmap (this->_boardBitmap);

	if (this->_window != NULL)
		al_destroy_display (this->_window);

	al_uninstall_audio();

	al_uninstall_mouse();

	al_uninstall_keyboard();
}

/*
 * Private
 */
void						GUIAllegro::ajustBounds (void)
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

void						GUIAllegro::drawMainMenu (void)
{
	eboadMode boardCurrentMode;
	std::string mainString;

	if (this->_mainMenuImage == NULL)
	{
		this->_mainMenuImage = al_load_bitmap ("ressources/images/main_menu.png");
		if (this->_mainMenuImage == NULL)
		{
			throw GUIException (this->_GUIName, "al_load_bitmap GUIAllegro::drawMainMenu");
		}
	}

	al_draw_scaled_bitmap (this->_mainMenuImage, 0, 0, 1000, 1000, 0, 0, _mapWidth, _mapHeight, 0);

	/* Printing Nibbler Mode */

	boardCurrentMode = this->_board->getBoardMode();

	mainString = "Current Mode: ";
	if ((boardCurrentMode | eboadMode::Default) == eboadMode::Default)
		mainString += "Default";
	else
	{
		switch (boardCurrentMode)
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
			case eboadMode::SpecialFood | eboadMode::NoFriendlyFire |
				 eboadMode::Endless | eboadMode::Multiplayer:
				mainString += "SpecialFood | NoFriendlyFire | Endless | Multiplayer";
				break;
			default:
				mainString += "????";
				break;
		}
	}

	al_draw_text (this->_mainTextPolice, al_map_rgb (0x00, 0x00, 0x00), 10, 3,
				  ALLEGRO_ALIGN_LEFT, mainString.c_str());
}

void						GUIAllegro::drawMapSelection (void)
{
	if (this->_mapSelectionImage == NULL)
	{
		this->_mapSelectionImage = al_load_bitmap ("ressources/images/map_selection.png");
		if (this->_mapSelectionImage == NULL)
		{
			throw GUIException (this->_GUIName, "al_load_bitmap GUIAllegro::drawMapSelection");
		}
	}

	al_draw_scaled_bitmap (this->_mapSelectionImage, 0, 0, 1000, 1000, 0, 0,
						   _mapWidth, _mapHeight, 0);
}

void						GUIAllegro::drawBoard (void)
{
	unsigned int height, width, y, x;
	std::vector< std::vector<int> > *boardCells;
	ALLEGRO_COLOR cellColor;

	al_clear_to_color (al_map_rgb (255, 255, 255));

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
						cellColor = al_map_rgb (0x00, 0x00, 0x00);
						break;
					case (int)eBonusValue::CommonValue:
						cellColor = al_map_rgb (0xff, 0xa5, 0x00);
						break;
					case (int)eBonusValue::UncommonValue:
						cellColor = al_map_rgb (0xff, 0x00, 0x00);
						break;
					case (int)eBonusValue::RareValue:
						cellColor = al_map_rgb (0xff, 0x00, 0xff);
						break;
					case (int)eBonusValue::LegendaryValue:
						cellColor = al_map_rgb (0x00, 0x00, 0xff);
						break;
					case (int)eBonusValue::GodlikeValue:
						cellColor = al_map_rgb (0x33, 0x33, 0x33);
						break;
					default:
						throw ShouldNeverOccurException (__FILE__, __LINE__);
				}

				al_draw_filled_rectangle (x * 10, y * 10, x * 10 + 10, y * 10 + 10, cellColor);
			}
		}
	}
}

void						GUIAllegro::drawSnakes (void)
{
	std::list<t_cell> snakeCells;
	std::list<t_cell>::iterator itSnakeCell;
	ALLEGRO_COLOR snakeCellColor;
	eSnakeDirection snakeCurrentDirection;
	bool head;

	snakeCells = this->_snakeP1->getSnakeCells();
	snakeCurrentDirection = this->_snakeP1->getCurrentDirection();

	head = true;
	snakeCellColor = al_map_rgb (0x00, 0x7f, 0x00);
	for (itSnakeCell = snakeCells.begin(); itSnakeCell != snakeCells.end(); ++itSnakeCell)
	{
		if (head)
		{
			switch (snakeCurrentDirection)
			{
				case eSnakeDirection::East:
					al_draw_filled_triangle (itSnakeCell->positionX * 10,
											 itSnakeCell->positionY * 10,
											 itSnakeCell->positionX * 10,
											 itSnakeCell->positionY * 10 + 10,
											 itSnakeCell->positionX * 10 + 10,
											 itSnakeCell->positionY * 10 + 5,
											 snakeCellColor);
					break;
				case eSnakeDirection::West:
					al_draw_filled_triangle (itSnakeCell->positionX * 10 + 10,
											 itSnakeCell->positionY * 10,
											 itSnakeCell->positionX * 10 + 10,
											 itSnakeCell->positionY * 10 + 10,
											 itSnakeCell->positionX * 10,
											 itSnakeCell->positionY * 10 + 5,
											 snakeCellColor);
					break;
				case eSnakeDirection::North:
					al_draw_filled_triangle (itSnakeCell->positionX * 10 + 5,
											 itSnakeCell->positionY * 10,
											 itSnakeCell->positionX * 10,
											 itSnakeCell->positionY * 10 + 10,
											 itSnakeCell->positionX * 10 + 10,
											 itSnakeCell->positionY * 10 + 10,
											 snakeCellColor);
					break;
				case eSnakeDirection::South:
					al_draw_filled_triangle (itSnakeCell->positionX * 10,
											 itSnakeCell->positionY * 10,
											 itSnakeCell->positionX * 10 + 10,
											 itSnakeCell->positionY * 10,
											 itSnakeCell->positionX * 10 + 5,
											 itSnakeCell->positionY * 10 + 10,
											 snakeCellColor);
					break;
				default:
					/* Safety: Should never occur */
					al_draw_filled_circle (itSnakeCell->positionX * 10 + 5,
										   itSnakeCell->positionY * 10 + 5,
										   5, snakeCellColor);
					break;
			}

			snakeCellColor = al_map_rgb (0x00, 0xff, 0x00);
			head = false;
			continue;
		}

		al_draw_filled_rectangle (itSnakeCell->positionX * 10,
								  itSnakeCell->positionY * 10,
								  itSnakeCell->positionX * 10 + 10,
								  itSnakeCell->positionY * 10 + 10,
								  snakeCellColor);
	}

	if (this->_snakeP2)
	{
		snakeCells = this->_snakeP2->getSnakeCells();
		snakeCurrentDirection = this->_snakeP2->getCurrentDirection();

		head = true;
		snakeCellColor = al_map_rgb (0x00, 0x7f, 0x7f);
		for (itSnakeCell = snakeCells.begin(); itSnakeCell != snakeCells.end(); ++itSnakeCell)
		{
			if (head)
			{
				switch (snakeCurrentDirection)
				{
					case eSnakeDirection::East:
						al_draw_filled_triangle (itSnakeCell->positionX * 10,
												 itSnakeCell->positionY * 10,
												 itSnakeCell->positionX * 10,
												 itSnakeCell->positionY * 10 + 10,
												 itSnakeCell->positionX * 10 + 10,
												 itSnakeCell->positionY * 10 + 5,
												 snakeCellColor);
						break;
					case eSnakeDirection::West:
						al_draw_filled_triangle (itSnakeCell->positionX * 10 + 10,
												 itSnakeCell->positionY * 10,
												 itSnakeCell->positionX * 10 + 10,
												 itSnakeCell->positionY * 10 + 10,
												 itSnakeCell->positionX * 10,
												 itSnakeCell->positionY * 10 + 5,
												 snakeCellColor);
						break;
					case eSnakeDirection::North:
						al_draw_filled_triangle (itSnakeCell->positionX * 10 + 5,
												 itSnakeCell->positionY * 10,
												 itSnakeCell->positionX * 10,
												 itSnakeCell->positionY * 10 + 10,
												 itSnakeCell->positionX * 10 + 10,
												 itSnakeCell->positionY * 10 + 10,
												 snakeCellColor);
						break;
					case eSnakeDirection::South:
						al_draw_filled_triangle (itSnakeCell->positionX * 10,
												 itSnakeCell->positionY * 10,
												 itSnakeCell->positionX * 10 + 10,
												 itSnakeCell->positionY * 10,
												 itSnakeCell->positionX * 10 + 5,
												 itSnakeCell->positionY * 10 + 10,
												 snakeCellColor);
						break;
					default:
						/* Safety: Should never occur */
						al_draw_filled_circle (itSnakeCell->positionX * 10 + 5,
											   itSnakeCell->positionY * 10 + 5,
											   5, snakeCellColor);
						break;
				}

				snakeCellColor = al_map_rgb (0x00, 0xff, 0xff);
				head = false;
				continue;
			}

			al_draw_filled_rectangle (itSnakeCell->positionX * 10,
									  itSnakeCell->positionY * 10,
									  itSnakeCell->positionX * 10 + 10,
									  itSnakeCell->positionY * 10 + 10,
									  snakeCellColor);
		}
	}
}

void						GUIAllegro::drawScore (void)
{
	std::string scoreString;
	int boardCompletedScore;

	/* Clearing Score zone */

	al_draw_filled_rectangle (0, 0, _mapWidth, this->_textHeight, al_map_rgb (0x33, 0x33, 0x33));

	/* Setting Score Text */

	scoreString = "Player1: ";
	scoreString += std::to_string (this->_snakeP1->getScore());
	scoreString += "/";
	boardCompletedScore = this->_board->getBoardCompletedScore();
	if (boardCompletedScore != -1)
		scoreString += std::to_string (boardCompletedScore);
	else
		scoreString += "∞";

	al_draw_text (this->_scoreTextPolice, al_map_rgb (0xFF, 0xFF, 0xFF), 10, 3,
				  ALLEGRO_ALIGN_LEFT, scoreString.c_str());

	if (this->_snakeP2)
	{
		scoreString = "Player2: ";
		scoreString += std::to_string (this->_snakeP2->getScore());
		scoreString += "/";
		boardCompletedScore = this->_board->getBoardCompletedScore();
		if (boardCompletedScore != -1)
			scoreString += std::to_string (boardCompletedScore);
		else
			scoreString += "∞";

		al_draw_text (this->_scoreTextPolice, al_map_rgb (0xFF, 0xFF, 0xFF),
					  _mapWidth - 10, 3, ALLEGRO_ALIGN_RIGHT, scoreString.c_str());
	}
}

void						GUIAllegro::drawEndMenu (void)
{
	eBoardStatus boardStatus;

	if (this->_endMenuImage != NULL)
		al_destroy_bitmap (this->_endMenuImage);

	boardStatus = this->_board->getBoardStatus();
	switch (boardStatus)
	{
		case eBoardStatus::Player1Win:
			if (! this->_snakeP2)
				this->_endMenuImage = al_load_bitmap ("ressources/images/singleplayer_win.png");
			else
				this->_endMenuImage = al_load_bitmap ("ressources/images/multiplayer_player1_win.png");
			break;
		case eBoardStatus::Player1Lose:
			if (! this->_snakeP2)
				this->_endMenuImage = al_load_bitmap ("ressources/images/singleplayer_lose.png");
			else
				this->_endMenuImage = al_load_bitmap ("ressources/images/multiplayer_player2_win.png");
			break;
		case eBoardStatus::Player2Win:
			this->_endMenuImage = al_load_bitmap ("ressources/images/multiplayer_player2_win.png");
			break;
		case eBoardStatus::Player2Lose:
			this->_endMenuImage = al_load_bitmap ("ressources/images/multiplayer_player1_win.png");
			break;
		case eBoardStatus::Draw:
			this->_endMenuImage = al_load_bitmap ("ressources/images/multiplayer_draw.png");
			break;
		default:
			throw ShouldNeverOccurException (__FILE__, __LINE__);
	}

	if (this->_endMenuImage == NULL)
	{
		throw GUIException (this->_GUIName, "al_load_bitmap GUIAllegro::drawEndMenu");
	}

	al_draw_scaled_bitmap (this->_endMenuImage, 0, 0, 1000, 1000, 0, 0, _mapWidth, _mapHeight, 0);
}

/*
 * Public
 */
eGUI						GUIAllegro::getGUIName (void) const
{
	return this->_GUIName;
}

void						GUIAllegro::start (void)
{
	unsigned int scalingFactor, mainFontSize;

	_mapWidth = this->_board->getWidth() * 10;
	_mapHeight = this->_textHeight + this->_board->getHeight() * 10;

#ifdef PROJ_DEBUG
	std::cout << "GUIAllegro::start" << std::endl;
#endif

	this->_window = al_create_display (_mapWidth, _mapHeight);
	if (this->_window == NULL)
	{
		throw GUIException (this->_GUIName, "al_create_display");
	}
	al_set_window_title (this->_window, "Nibbler (Allegro GUI)");

	al_set_new_bitmap_flags (ALLEGRO_MEMORY_BITMAP);
	this->_boardBitmap = al_create_bitmap (_mapWidth, _mapHeight - this->_textHeight);
	if (! this->_boardBitmap)
	{
		throw GUIException (this->_GUIName, "al_create_bitmap");
	}

	this->ajustBounds();

	this->_eventQueue = al_create_event_queue();
	if (! this->_eventQueue)
	{
		throw GUIException (this->_GUIName, "al_create_event_queue");
	}
	al_register_event_source (this->_eventQueue, al_get_display_event_source (this->_window));
	al_register_event_source (this->_eventQueue, al_get_keyboard_event_source());
	al_register_event_source (this->_eventQueue, al_get_mouse_event_source());

	scalingFactor = (this->_board->getWidth() + this->_board->getHeight()) * 100 / (100 + 100 /* maximum possible board size*/);
	mainFontSize =  30 * scalingFactor / 100;

	this->_mainTextPolice = al_load_ttf_font_stretch ("ressources/fonts/FreeMono.ttf", mainFontSize, mainFontSize, 0);
	if (! this->_mainTextPolice)
	{
		throw GUIException (this->_GUIName, "al_load_ttf_font 1");
	}

	this->_scoreTextPolice = al_load_ttf_font_stretch ("ressources/fonts/Ubuntu-MI.ttf", this->_textHeight - 10, this->_textHeight - 10, 0);
	if (! this->_scoreTextPolice)
	{
		throw GUIException (this->_GUIName, "al_load_ttf_font 3");
	}

	if (! al_reserve_samples (4))
	{
		throw GUIException (this->_GUIName, "al_reserve_samples");
	}

	this->_mainMenuSample = al_load_sample ("ressources/sounds/ff_main_menu.wav");
	if (! this->_mainMenuSample)
	{
		throw GUIException (this->_GUIName, "al_load_sample this->_mainMenuSample");
	}

	this->_mainMenuMusic = al_create_sample_instance (this->_mainMenuSample);
	if (! this->_mainMenuMusic)
	{
		throw GUIException (this->_GUIName, "al_create_sample_instance this->_mainMenuMusic");
	}

	if (! al_set_sample_instance_playmode (this->_mainMenuMusic, ALLEGRO_PLAYMODE_LOOP))
	{
		throw GUIException (this->_GUIName, "al_set_sample_instance_playmode this->_mainMenuMusic");
	}

	this->_mapSelectionSample = al_load_sample ("ressources/sounds/ff_main_theme.wav");
	if (! this->_mapSelectionSample)
	{
		throw GUIException (this->_GUIName, "al_load_sample this->_mapSelectionSample");
	}

	this->_mapSelectionMusic = al_create_sample_instance (this->_mapSelectionSample);
	if (! this->_mapSelectionMusic)
	{
		throw GUIException (this->_GUIName, "al_create_sample_instance this->_mapSelectionMusic");
	}

	if (! al_set_sample_instance_playmode (this->_mapSelectionMusic, ALLEGRO_PLAYMODE_LOOP))
	{
		throw GUIException (this->_GUIName, "al_set_sample_instance_playmode this->_mapSelectionMusic");
	}

	this->_started = true;
}

bool						GUIAllegro::alreadyStarted (void) const
{
	return this->_started;
}

eGUI						GUIAllegro::wantedGUI (void) const
{
	return this->_wantedGUI;
}

void						GUIAllegro::stop()
{
#ifdef PROJ_DEBUG
	std::cout << "GUIAllegro::stop" << std::endl;
#endif

	if (! this->_started)
	{
		throw GUIException (this->_GUIName, "GUIAllegro::stop => GUIAllegro wasn't started");
	}

	if (this->_endMenuSample != NULL)
	{
		al_destroy_sample (this->_endMenuSample);
		this->_endMenuSample = NULL;
	}

	if (this->_boardMusic != NULL)
	{
		al_destroy_sample_instance (this->_boardMusic);
		this->_boardMusic = NULL;
	}

	if (this->_boardSample != NULL)
	{
		al_destroy_sample (this->_boardSample);
		this->_boardSample = NULL;
	}

	if (this->_mapSelectionMusic != NULL)
	{
		al_destroy_sample_instance (this->_mapSelectionMusic);
		this->_mapSelectionMusic = NULL;
	}

	if (this->_mapSelectionSample != NULL)
	{
		al_destroy_sample (this->_mapSelectionSample);
		this->_mapSelectionSample = NULL;
	}

	if (this->_mainMenuMusic != NULL)
	{
		al_destroy_sample_instance (this->_mainMenuMusic);
		this->_mainMenuMusic = NULL;
	}

	if (this->_mainMenuSample != NULL)
	{
		al_destroy_sample (this->_mainMenuSample);
		this->_mainMenuSample = NULL;
	}

	if (this->_scoreTextPolice != NULL)
	{
		al_destroy_font (this->_scoreTextPolice);
		this->_scoreTextPolice = NULL;
	}

	if (this->_mainTextPolice != NULL)
	{
		al_destroy_font (this->_mainTextPolice);
		this->_mainTextPolice = NULL;
	}

	if (this->_eventQueue != NULL)
	{
		al_destroy_event_queue (this->_eventQueue);
		this->_eventQueue = NULL;
	}

	if (this->_boardBitmap != NULL)
	{
		al_destroy_bitmap (this->_boardBitmap);
		this->_boardBitmap = NULL;
	}

	if (this->_window != NULL)
	{
		al_destroy_display (this->_window);
		this->_window = NULL;
	}

	this->_started = false;
}

/* Main Menu */

void						GUIAllegro::loadMainMenu (void)
{
	if (this->_mapSelectionMusic != NULL)
		al_detach_sample_instance (this->_mapSelectionMusic);
	if (this->_boardMusic != NULL)
		al_detach_sample_instance (this->_boardMusic);
	al_stop_samples();

	if (! al_attach_sample_instance_to_mixer (this->_mainMenuMusic, al_get_default_mixer()))
	{
		throw GUIException (this->_GUIName, "al_attach_sample_instance_to_mixer this->_mainMenuMusic");
	}

	al_set_sample_instance_position (this->_mainMenuMusic, 0.0f);
	al_play_sample_instance (this->_mainMenuMusic);
	if (! this->_muted)
		al_set_mixer_playing (al_get_default_mixer(), ! this->_muted);

	this->drawMainMenu();

	al_flip_display();
}

eGUIMainMenuEvent			GUIAllegro::getMainMenuEvent (void)
{
	ALLEGRO_EVENT events;

	while (al_get_next_event (this->_eventQueue, &events))
	{
		switch (events.type)
		{
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				return eGUIMainMenuEvent::quitGame;

			case ALLEGRO_EVENT_KEY_DOWN:
				switch (events.keyboard.keycode)
				{
					case ALLEGRO_KEY_ESCAPE:
						return eGUIMainMenuEvent::quitGame;

					/* GUI Switchs */
					case ALLEGRO_KEY_1:
					case ALLEGRO_KEY_F1:
					case ALLEGRO_KEY_PAD_1:
						this-> _wantedGUI = eGUI::SDL;
						return eGUIMainMenuEvent::changeGUI;

					case ALLEGRO_KEY_2:
					case ALLEGRO_KEY_F2:
					case ALLEGRO_KEY_PAD_2:
						this-> _wantedGUI = eGUI::SFML;
						return eGUIMainMenuEvent::changeGUI;

					/* Audio */
					case ALLEGRO_KEY_P:
						if (! al_get_mixer_playing (al_get_default_mixer()))
							this->_muted = false;
						else
							this->_muted = true;

						al_set_mixer_playing (al_get_default_mixer(), ! this->_muted);
						break;

					case ALLEGRO_KEY_PAD_PLUS:
						this->_musicVolume = this->_musicVolume + 0.1f <= 10.0f ?
											 this->_musicVolume + 0.1f:
											 10.0f;
						al_set_mixer_gain (al_get_default_mixer(), this->_musicVolume);
						break;

					case ALLEGRO_KEY_MINUS:
					case ALLEGRO_KEY_PAD_MINUS:
						this->_musicVolume = this->_musicVolume >= 0.1f ?
											 this->_musicVolume - 0.1f:
											 0.0f;
						al_set_mixer_gain (al_get_default_mixer(), this->_musicVolume);
						break;

					default:
						break;
				}
				break;

			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				if (events.mouse.button & 1)
				{
					if (this->_menuLeftButton.in (events.mouse.x, events.mouse.y))
						return eGUIMainMenuEvent::startSinglePlayerGame;

					if (this->_menuRightButton.in (events.mouse.x, events.mouse.y))
						return eGUIMainMenuEvent::startMultiPlayerGame;

					if (this->_menuMiddleButton.in (events.mouse.x, events.mouse.y))
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

void						GUIAllegro::loadMapSelection (void)
{
	if (this->_mainMenuMusic != NULL)
		al_detach_sample_instance (this->_mainMenuMusic);
	if (this->_boardMusic != NULL)
		al_detach_sample_instance (this->_boardMusic);
	al_stop_samples();

	if (! al_attach_sample_instance_to_mixer (this->_mapSelectionMusic, al_get_default_mixer()))
	{
		throw GUIException (this->_GUIName, "al_attach_sample_instance_to_mixer this->_mapSelectionMusic");
	}

	al_set_sample_instance_position (this->_mapSelectionMusic, 0.0f);
	al_play_sample_instance (this->_mapSelectionMusic);
	if (! this->_muted)
		al_set_mixer_playing (al_get_default_mixer(), ! this->_muted);

	this->drawMapSelection();

	al_flip_display();
}

eGUIMapSelectionEvent		GUIAllegro::getMapSelectionEvent (void)
{
	ALLEGRO_EVENT events;

	while (al_get_next_event (this->_eventQueue, &events))
	{
		switch (events.type)
		{
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				return eGUIMapSelectionEvent::quitGame;

			case ALLEGRO_EVENT_KEY_DOWN:
				switch (events.keyboard.keycode)
				{
					case ALLEGRO_KEY_ESCAPE:
						return eGUIMapSelectionEvent::quitGame;

					/* GUI Switchs */
					case ALLEGRO_KEY_1:
					case ALLEGRO_KEY_F1:
					case ALLEGRO_KEY_PAD_1:
						this-> _wantedGUI = eGUI::SDL;
						return eGUIMapSelectionEvent::changeGUI;

					case ALLEGRO_KEY_2:
					case ALLEGRO_KEY_F2:
					case ALLEGRO_KEY_PAD_2:
						this-> _wantedGUI = eGUI::SFML;
						return eGUIMapSelectionEvent::changeGUI;

					/* Audio */
					case ALLEGRO_KEY_P:
						if (! al_get_mixer_playing (al_get_default_mixer()))
							this->_muted = false;
						else
							this->_muted = true;

						al_set_mixer_playing (al_get_default_mixer(), ! this->_muted);
						break;

					case ALLEGRO_KEY_PAD_PLUS:
						this->_musicVolume = this->_musicVolume + 0.1f <= 10.0f ?
											 this->_musicVolume + 0.1f:
											 10.0f;
						al_set_mixer_gain (al_get_default_mixer(), this->_musicVolume);
						break;

					case ALLEGRO_KEY_MINUS:
					case ALLEGRO_KEY_PAD_MINUS:
						this->_musicVolume = this->_musicVolume >= 0.1f ?
											 this->_musicVolume - 0.1f:
											 0.0f;
						al_set_mixer_gain (al_get_default_mixer(), this->_musicVolume);
						break;

					default:
						break;
				}
				break;

			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				if (events.mouse.button & 1)
				{
					if (this->_mapLTButton.in (events.mouse.x, events.mouse.y))
							return eGUIMapSelectionEvent::mapLT;

					if (this->_mapLMButton.in (events.mouse.x, events.mouse.y))
						return eGUIMapSelectionEvent::mapLM;

					if (this->_mapLBButton.in (events.mouse.x, events.mouse.y))
						return eGUIMapSelectionEvent::mapLB;

					if (this->_mapCTButton.in (events.mouse.x, events.mouse.y))
						return eGUIMapSelectionEvent::mapCT;

					if (this->_mapCMButton.in (events.mouse.x, events.mouse.y))
						return eGUIMapSelectionEvent::mapCM;

					if (this->_mapCBButton.in (events.mouse.x, events.mouse.y))
						return eGUIMapSelectionEvent::mapCB;

					if (this->_mapRTButton.in (events.mouse.x, events.mouse.y))
						return eGUIMapSelectionEvent::mapRT;

					if (this->_mapRMButton.in (events.mouse.x, events.mouse.y))
						return eGUIMapSelectionEvent::mapRM;

					if (this->_mapRBButton.in (events.mouse.x, events.mouse.y))
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

void						GUIAllegro::setPlayers (Snake *snakeP1, Snake *snakeP2)
{
	if (! snakeP1)
	{
		throw InvalidArgumentException ("GUIAllegro::setPlayers: snakeP1 == null");
	}

	this->_snakeP1 = snakeP1;
	this->_snakeP2 = snakeP2;
}

void						GUIAllegro::loadBoard (unsigned int soundTrack)
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

	if (this->_boardSample != NULL)
	{
		al_destroy_sample (this->_boardSample);
		this->_boardSample = NULL;
	}

	this->_boardSample = al_load_sample (boardMusicName.c_str());
	if (! this->_boardSample)
	{
		throw GUIException (this->_GUIName, "al_load_sample this->_boardSample");
	}

	if (this->_boardMusic != NULL)
	{
		al_destroy_sample_instance (this->_boardMusic);
		this->_boardMusic = NULL;
	}

	this->_boardMusic = al_create_sample_instance (this->_boardSample);
	if (! this->_boardMusic)
	{
		throw GUIException (this->_GUIName, "al_create_sample_instance this->_boardMusic");
	}

	if (! al_set_sample_instance_playmode (this->_boardMusic, ALLEGRO_PLAYMODE_LOOP))
	{
		throw GUIException (this->_GUIName, "al_set_sample_instance_playmode this->_boardMusic");
	}

	if (! al_attach_sample_instance_to_mixer (this->_boardMusic, al_get_default_mixer()))
	{
		throw GUIException (this->_GUIName, "al_attach_sample_instance_to_mixer this->_boardMusic");
	}

	if (this->_mainMenuMusic != NULL)
		al_detach_sample_instance (this->_mainMenuMusic);
	if (this->_mapSelectionMusic != NULL)
		al_detach_sample_instance (this->_mapSelectionMusic);
	al_stop_samples();
	al_play_sample_instance (this->_boardMusic);
	if (! this->_muted)
		al_set_mixer_playing (al_get_default_mixer(), ! this->_muted);
}

void						GUIAllegro::updateGameGUI (void)
{

	int boardCompletedScore;
	unsigned int currentGlobalScore;
	unsigned int speed;

	al_set_target_bitmap (this->_boardBitmap);

	this->drawBoard();
	this->drawSnakes();

	al_set_target_backbuffer (this->_window);

	al_draw_bitmap (this->_boardBitmap, 0, this->_textHeight, 0);

	this->drawScore();

	al_flip_display();

	currentGlobalScore = this->_snakeP1->getScore();
	if (this->_snakeP2)
		currentGlobalScore = currentGlobalScore > this->_snakeP2->getScore() ?
							 currentGlobalScore :
							 this->_snakeP2->getScore();

	if (currentGlobalScore > 95)
		currentGlobalScore = 95;

	boardCompletedScore = this->_board->getBoardCompletedScore();
	if (boardCompletedScore <= 1)
		speed = 100 - currentGlobalScore;
	else
		speed = 100 - (currentGlobalScore * 50 / (boardCompletedScore - 1));

	al_rest ((double)speed / 1200.0);
}

eGUIGameEvent				GUIAllegro::getGameEvent (void)
{
	ALLEGRO_EVENT events;
	eSnakeDirection snakeP1CurrentDirection, snakeP2CurrentDirection;

	snakeP1CurrentDirection = this->_snakeP1->getCurrentDirection();
	if (this->_snakeP2)
		snakeP2CurrentDirection = this->_snakeP2->getCurrentDirection();

	while (al_get_next_event (this->_eventQueue, &events))
	{
		switch (events.type)
		{
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				return eGUIGameEvent::quitGame;

			case ALLEGRO_EVENT_KEY_DOWN:
				switch (events.keyboard.keycode)
				{
					case ALLEGRO_KEY_E:
						this->_snakeP1->eat (1);
						break;

					case ALLEGRO_KEY_ESCAPE:
						return eGUIGameEvent::quitGame;

					/* Player 1 commands */
					case ALLEGRO_KEY_LEFT:
						if ((snakeP1CurrentDirection != eSnakeDirection::West) &&
							(snakeP1CurrentDirection != eSnakeDirection::East))
							return eGUIGameEvent::p1GoLeft;
						break;

					case ALLEGRO_KEY_RIGHT:
						if ((snakeP1CurrentDirection != eSnakeDirection::West) &&
							(snakeP1CurrentDirection != eSnakeDirection::East))
							return eGUIGameEvent::p1GoRight;
						break;

					case ALLEGRO_KEY_UP:
						if ((snakeP1CurrentDirection != eSnakeDirection::North) &&
							(snakeP1CurrentDirection != eSnakeDirection::South))
							return eGUIGameEvent::p1GoUp;
						break;

					case ALLEGRO_KEY_DOWN:
						if ((snakeP1CurrentDirection != eSnakeDirection::North) &&
							(snakeP1CurrentDirection != eSnakeDirection::South))
							return eGUIGameEvent::p1GoDown;
						break;

					/* Player 2 commands */
					case ALLEGRO_KEY_Q:
						if (this->_snakeP2)
							if ((snakeP2CurrentDirection != eSnakeDirection::West) &&
								(snakeP2CurrentDirection != eSnakeDirection::East))
								return eGUIGameEvent::p2GoLeft;
						break;

					case ALLEGRO_KEY_D:
						if (this->_snakeP2)
							if ((snakeP2CurrentDirection != eSnakeDirection::West) &&
								(snakeP2CurrentDirection != eSnakeDirection::East))
								return eGUIGameEvent::p2GoRight;
						break;

					case ALLEGRO_KEY_Z:
						if (this->_snakeP2)
							if ((snakeP2CurrentDirection != eSnakeDirection::North) &&
								(snakeP2CurrentDirection != eSnakeDirection::South))
								return eGUIGameEvent::p2GoUp;
						break;

					case ALLEGRO_KEY_S:
						if (this->_snakeP2)
							if ((snakeP2CurrentDirection != eSnakeDirection::North) &&
								(snakeP2CurrentDirection != eSnakeDirection::South))
								return eGUIGameEvent::p2GoDown;
						break;

					/* GUI Switchs */
					case ALLEGRO_KEY_1:
					case ALLEGRO_KEY_F1:
					case ALLEGRO_KEY_PAD_1:
						this-> _wantedGUI = eGUI::SDL;
						return eGUIGameEvent::changeGUI;

					case ALLEGRO_KEY_2:
					case ALLEGRO_KEY_F2:
					case ALLEGRO_KEY_PAD_2:
						this-> _wantedGUI = eGUI::SFML;
						return eGUIGameEvent::changeGUI;

					/* Audio */
					case ALLEGRO_KEY_P:
						if (! al_get_mixer_playing (al_get_default_mixer()))
							this->_muted = false;
						else
							this->_muted = true;

						al_set_mixer_playing (al_get_default_mixer(), ! this->_muted);
						break;

					case ALLEGRO_KEY_PAD_PLUS:
						this->_musicVolume = this->_musicVolume + 0.1f <= 10.0f ?
											 this->_musicVolume + 0.1f:
											 10.0f;
						al_set_mixer_gain (al_get_default_mixer(), this->_musicVolume);
						break;

					case ALLEGRO_KEY_MINUS:
					case ALLEGRO_KEY_PAD_MINUS:
						this->_musicVolume = this->_musicVolume >= 0.1f ?
											 this->_musicVolume - 0.1f:
											 0.0f;
						al_set_mixer_gain (al_get_default_mixer(), this->_musicVolume);
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

void						GUIAllegro::loadEndMenu (void)
{
	eBoardStatus boardStatus;
	std::string endMenuMusicName;

	if (this->_endMenuSample != NULL)
	{
		al_destroy_sample (this->_endMenuSample);
		this->_endMenuSample = NULL;
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

	this->_endMenuSample = al_load_sample (endMenuMusicName.c_str());
	if (! this->_endMenuSample)
	{
		throw GUIException (this->_GUIName, "al_load_sample this->_endMenuSample");
	}

	if (this->_mainMenuMusic != NULL)
		al_detach_sample_instance (this->_mainMenuMusic);
	if (this->_mapSelectionMusic != NULL)
		al_detach_sample_instance (this->_mapSelectionMusic);
	if (this->_boardMusic != NULL)
		al_detach_sample_instance (this->_boardMusic);
	al_stop_samples();
	al_play_sample (this->_endMenuSample, this->_musicVolume, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	if (! this->_muted)
		al_set_mixer_playing (al_get_default_mixer(), ! this->_muted);

	this->drawEndMenu();

	al_flip_display();
}

eGUIEndMenuEvent			GUIAllegro::getEndMenuEvent (void)
{
	ALLEGRO_EVENT events;

	while (al_get_next_event (this->_eventQueue, &events))
	{
		switch (events.type)
		{
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				return eGUIEndMenuEvent::quitGame;

			case ALLEGRO_EVENT_KEY_DOWN:
				switch (events.keyboard.keycode)
				{
					case ALLEGRO_KEY_ESCAPE:
						return eGUIEndMenuEvent::quitGame;

					/* GUI Switchs */
					case ALLEGRO_KEY_1:
					case ALLEGRO_KEY_F1:
					case ALLEGRO_KEY_PAD_1:
						this-> _wantedGUI = eGUI::SDL;
						return eGUIEndMenuEvent::changeGUI;

					case ALLEGRO_KEY_2:
					case ALLEGRO_KEY_F2:
					case ALLEGRO_KEY_PAD_2:
						this-> _wantedGUI = eGUI::SFML;
						return eGUIEndMenuEvent::changeGUI;

					/* Audio */
					case ALLEGRO_KEY_P:
						if (! al_get_mixer_playing (al_get_default_mixer()))
							this->_muted = false;
						else
							this->_muted = true;

						al_set_mixer_playing (al_get_default_mixer(), ! this->_muted);
						break;

					case ALLEGRO_KEY_PAD_PLUS:
						this->_musicVolume = this->_musicVolume + 0.1f <= 10.0f ?
											 this->_musicVolume + 0.1f:
											 10.0f;
						al_set_mixer_gain (al_get_default_mixer(), this->_musicVolume);
						break;

					case ALLEGRO_KEY_MINUS:
					case ALLEGRO_KEY_PAD_MINUS:
						this->_musicVolume = this->_musicVolume >= 0.1f ?
											 this->_musicVolume - 0.1f:
											 0.0f;
						al_set_mixer_gain (al_get_default_mixer(), this->_musicVolume);
						break;

					default:
						break;
				}
				break;

			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				if (events.mouse.button & 1)
				{
					if (this->_menuLeftButton.in (events.mouse.x, events.mouse.y))
						return eGUIEndMenuEvent::restartLevel;

					if (this->_menuRightButton.in (events.mouse.x, events.mouse.y))
						return eGUIEndMenuEvent::nextLevel;

					if (this->_menuMiddleButton.in (events.mouse.x, events.mouse.y))
						return eGUIEndMenuEvent::backToLobby;

					if (this->_menuBottomButton.in (events.mouse.x, events.mouse.y))
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
GUIAllegro					*createGUI (Board *board)
{
	return new GUIAllegro (board);
}

void						setPlayers (GUIAllegro *GUI, Snake *snakeP1, Snake *snakeP2)
{
	GUI->setPlayers (snakeP1, snakeP2);
}

void						destroyGUI (GUIAllegro *GUI)
{
	delete GUI;
}
