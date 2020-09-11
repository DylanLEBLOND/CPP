#include <GUISFML.class.hpp>

static unsigned int _mapWidth;
static unsigned int _mapHeight;

/*
 * Constructors
 */
GUISFML::GUISFML (Board *board)
	: _board (board), _snakeP1 (NULL), _snakeP2 (NULL), _wantedGUI (eGUI::SFML),
	  _textHeight (26),
	  _musicVolume (50), _muted (false),
	  _started (false)
{
	if (! board)
	{
		throw InvalidArgumentException ("GUISFML::GUISFML (Board *board, Snake *snake): board == null");
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
}

/*
 * Destructor
 */
GUISFML::~GUISFML (void) { }

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

	this->_menuMiddleButton.x = this->_menuMiddleButton.x * _mapWidth / 1000;
	this->_menuMiddleButton.y = this->_menuMiddleButton.y * _mapHeight / 1000;
	this->_menuMiddleButton.width = this->_menuMiddleButton.width * _mapWidth / 1000;
	this->_menuMiddleButton.height = this->_menuMiddleButton.height * _mapHeight / 1000;

	this->_menuBottomButton.x = this->_menuBottomButton.x * _mapWidth / 1000;
	this->_menuBottomButton.y = this->_menuBottomButton.y * _mapHeight / 1000;
	this->_menuBottomButton.width = this->_menuBottomButton.width * _mapWidth / 1000;
	this->_menuBottomButton.height = this->_menuBottomButton.height * _mapHeight / 1000;
}

void					GUISFML::drawMainMenu (void)
{
	eboadMode boardCurrentMode;
	std::string mainString;

	this->_window.clear (sf::Color::White);

	if (! this->_mainMenuTexture.loadFromFile ("ressources/images/main_menu.png"))
	{
		throw GUIException (this->_GUIName, "loadFromFile GUISFML::drawMainMenu");
	}
	this->_mainMenuTexture.setSmooth (true);

	this->_mainMenuSprite.setTexture (this->_mainMenuTexture);
	this->_mainMenuSprite.setScale (sf::Vector2f ((float)_mapWidth / 1000.0f, (float)_mapHeight / 1000.0f));

	this->_window.draw (this->_mainMenuSprite);

	/* Printing Nibbler Mode */

	boardCurrentMode = this->_board->getBoardMode();

	mainString = "Current Mode: ";
	if ((boardCurrentMode | eboadMode::Default) == eboadMode::Default)
		mainString += "Default";
	else
	{
		switch (boardCurrentMode)
		{
			case eboadMode::NoFriendlyFire:
				mainString += "NoFriendlyFire";
				break;
			case eboadMode::Endless:
				mainString += "Endless";
				break;
			case eboadMode::NoFriendlyFire | eboadMode::Endless:
				mainString += "NoFriendlyFire | Endless";
				break;
			default:
				mainString += "????";
				break;
		}
	}
	this->_mainText.setString (mainString);

	/* Printing Score Text */

	this->_mainText.setPosition (10, 3);
	this->_window.draw (this->_mainText);
}

void					GUISFML::drawBoard (void)
{
	unsigned int height, width, y, x;
	std::vector< std::vector<int> > *boardCells;
	sf::RectangleShape boardCellDraw;
	unsigned char r, g, b;

	boardCells = this->_board->getBoardCells();
	height = this->_board->getHeight();
	width = this->_board->getWidth();

	boardCellDraw.setSize (sf::Vector2f (10.f, 10.f));
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

				boardCellDraw.setFillColor (sf::Color (r, g, b));
				boardCellDraw.setPosition (x * 10, this->_textHeight + y * 10);
				this->_window.draw (boardCellDraw);
			}
		}
	}
}

void					GUISFML::drawSnakes (void)
{
	std::list<t_cell> snakeCells;
	std::list<t_cell>::iterator itSnakeCell;
	sf::CircleShape snakeHeadDraw;
	sf::RectangleShape snakeCellDraw;
	bool head;

	snakeCells = this->_snakeP1->getSnakeCells();

	snakeHeadDraw.setRadius (5.0f);
	snakeCellDraw.setSize (sf::Vector2f (10.f, 10.f));

	head = true;
	snakeHeadDraw.setFillColor (sf::Color (0, 128, 0));
	snakeCellDraw.setFillColor (sf::Color (0, 255, 0));
	for (itSnakeCell = snakeCells.begin(); itSnakeCell != snakeCells.end(); ++itSnakeCell)
	{
		if (head)
		{
			snakeHeadDraw.setPosition (itSnakeCell->positionX * 10, this->_textHeight + itSnakeCell->positionY * 10);
			this->_window.draw (snakeHeadDraw);
			head = false;
		}
		else
		{
			snakeCellDraw.setPosition (itSnakeCell->positionX * 10, this->_textHeight + itSnakeCell->positionY * 10);
			this->_window.draw (snakeCellDraw);
		}
	}

	if (this->_snakeP2)
	{
		snakeCells = this->_snakeP2->getSnakeCells();

		head = true;
		snakeHeadDraw.setFillColor (sf::Color (0, 128, 128));
		snakeCellDraw.setFillColor (sf::Color (0, 255, 255));
		for (itSnakeCell = snakeCells.begin(); itSnakeCell != snakeCells.end(); ++itSnakeCell)
		{
			if (head)
			{
				snakeHeadDraw.setPosition (itSnakeCell->positionX * 10, this->_textHeight + itSnakeCell->positionY * 10);
				this->_window.draw (snakeHeadDraw);
				head = false;
			}
			else
			{
				snakeCellDraw.setPosition (itSnakeCell->positionX * 10, this->_textHeight + itSnakeCell->positionY * 10);
				this->_window.draw (snakeCellDraw);
			}
		}
	}
}

void					GUISFML::drawScore (void)
{
	sf::RectangleShape scoreZone;
	std::wstring scoreString;
	int boardCompletedScore;

	/* Clearing Score zone */

	scoreZone.setSize (sf::Vector2f (_mapWidth, this->_textHeight));
	scoreZone.setFillColor (sf::Color (0x33, 0x33, 0x33));
	scoreZone.setPosition (0, 0);

	this->_window.draw (scoreZone);

	/* Setting Score Text */

	scoreString = L"Player1: ";
	scoreString += std::to_wstring (this->_snakeP1->getScore());
	scoreString += L"/";
	boardCompletedScore = this->_board->getBoardCompletedScore();
	if (boardCompletedScore != -1)
		scoreString += std::to_wstring (boardCompletedScore);
	else
		scoreString += L"∞";

	this->_scoreP1Text.setString (scoreString);

	if (this->_snakeP2)
	{
		scoreString = L"Player2: ";
		scoreString += std::to_wstring (this->_snakeP2->getScore());
		scoreString += L"/";
		boardCompletedScore = this->_board->getBoardCompletedScore();
		if (boardCompletedScore != -1)
			scoreString += std::to_wstring (boardCompletedScore);
		else
			scoreString += L"∞";

		this->_scoreP2Text.setString (scoreString);
	}

	/* Printing Score Text */

	this->_scoreP1Text.setPosition (10, 3);
	this->_window.draw (this->_scoreP1Text);

	if (this->_snakeP2)
	{
		this->_scoreP2Text.setPosition ((_mapWidth - 10) - this->_scoreP2Text.getGlobalBounds().width, 3);
		this->_window.draw (this->_scoreP2Text);
	}
}

void					GUISFML::drawEndMenu (void)
{
	eBoardStatus boardStatus;
	std::string endMenuFilename;

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
		default:
			throw ShouldNeverOccurException (__FILE__, __LINE__);
	}

	if (! this->_endMenuTexture.loadFromFile (endMenuFilename))
	{
		throw GUIException (this->_GUIName, "loadFromFile GUISFML::drawEndMenu");
	}
	this->_endMenuTexture.setSmooth (true);

	this->_endMenuSprite.setTexture (this->_endMenuTexture);
	this->_endMenuSprite.setScale (sf::Vector2f ((float)_mapWidth / 1000.0f, (float)_mapHeight / 1000.0f));

	this->_window.draw (this->_endMenuSprite);
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
	unsigned int scalingFactor;

	_mapWidth = this->_board->getWidth() * 10;
	_mapHeight = this->_textHeight + this->_board->getHeight() * 10;
	scalingFactor = (this->_board->getWidth() + this->_board->getHeight()) * 100 / (100 + 100 /* maximum possible board size*/);

#ifdef PROJ_DEBUG
	std::cout << "GUISFML::start" << std::endl;
#endif

	this->_window.create (sf::VideoMode (_mapWidth, _mapHeight), "Nibbler (SFML GUI)", sf::Style::Titlebar | sf::Style::Close);
	this->_window.setPosition (sf::Vector2i (100, 100));
	this->_window.setFramerateLimit (60);
	this->_window.setVerticalSyncEnabled (true);

	this->ajustBounds ();

	if (! this->_mainPolice.loadFromFile ("ressources/fonts/FreeMono.ttf"))
	{
		throw GUIException (this->_GUIName, "loadFromFile 1 (*** FONT FILE ***)");
	}
	this->_mainText.setFont (this->_mainPolice);
	this->_mainText.setCharacterSize (30 * scalingFactor / 100);
	this->_mainText.setFillColor (sf::Color::Black);

	if (! this->_scorePolice.loadFromFile ("ressources/fonts/Ubuntu-MI.ttf"))
	{
		throw GUIException (this->_GUIName, "loadFromFile 2 (*** FONT FILE ***)");
	}
	this->_scoreP1Text.setFont (this->_scorePolice);
	this->_scoreP1Text.setCharacterSize (this->_textHeight - 10);
	this->_scoreP1Text.setFillColor (sf::Color::White);

	this->_scoreP2Text.setFont (this->_scorePolice);
	this->_scoreP2Text.setCharacterSize (this->_textHeight - 10);
	this->_scoreP2Text.setFillColor (sf::Color::White);

	if (! this->_mainMenuMusic.openFromFile ("ressources/sounds/ff_main_menu.wav"))
	{
		throw GUIException (this->_GUIName, "openFromFile 1 (*** MUSIC FILE ***)");
	}

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

	this->_window.close();

	this->_started = false;
}

/* Main Menu */

void					GUISFML::loadMainMenu (void)
{
	this->_endMenuMusic.stop();
	this->_mainMenuMusic.play();
	if (this->_muted)
		this->_mainMenuMusic.pause();
	this->_mainMenuMusic.setLoop (true);
	this->_mainMenuMusic.setVolume (this->_musicVolume);

	this->_window.clear (sf::Color::White);

	this->drawMainMenu();

	this->_window.display();
}

eGUIMainMenuEvent		GUISFML::getMainMenuEvent (void)
{
	sf::Event events;

	while (this->_window.pollEvent (events))
	{
		switch (events.type)
		{
			case sf::Event::Closed:
				return eGUIMainMenuEvent::quitGame;

			case sf::Event::KeyPressed:
				switch (events.key.code)
				{
					case sf::Keyboard::Escape:
						return eGUIMainMenuEvent::quitGame;

					/* GUI Switchs */
					case sf::Keyboard::Num1:
					case sf::Keyboard::F1:
					case sf::Keyboard::Numpad1:
						this-> _wantedGUI = eGUI::SDL;
						return eGUIMainMenuEvent::changeGUI;

					case sf::Keyboard::Num3:
					case sf::Keyboard::F3:
					case sf::Keyboard::Numpad3:
						this-> _wantedGUI = eGUI::openGL;
						return eGUIMainMenuEvent::changeGUI;

					/* Audio */
					case sf::Keyboard::P:
						if (this->_mainMenuMusic.getStatus() == sf::SoundSource::Status::Paused)
						{
							this->_mainMenuMusic.play();
							this->_muted = false;
						}
						else
						{
							this->_mainMenuMusic.pause();
							this->_muted = true;
						}
						break;

					case sf::Keyboard::Add:
						this->_musicVolume = this->_musicVolume + 5 <= 100 ?
											 this->_musicVolume + 5:
											 100;
						this->_mainMenuMusic.setVolume (this->_musicVolume);
						break;

					case sf::Keyboard::Subtract:
						this->_musicVolume = this->_musicVolume >= 5 ?
											 this->_musicVolume - 5:
											 0;
						this->_mainMenuMusic.setVolume (this->_musicVolume);
						break;

					default:
						break;
				}
				break;

			case sf::Event::MouseButtonReleased:
				if (events.mouseButton.button == sf::Mouse::Left)
				{
					if (this->_menuLeftButton.in (events.mouseButton.x, events.mouseButton.y))
						return eGUIMainMenuEvent::startSinglePlayerGame;
					else if (this->_menuRightButton.in (events.mouseButton.x, events.mouseButton.y))
						return eGUIMainMenuEvent::startMultiPlayerGame;
					else if (this->_menuMiddleButton.in (events.mouseButton.x, events.mouseButton.y))
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

void					GUISFML::setPlayers (Snake *snakeP1, Snake *snakeP2)
{
	if (! snakeP1)
	{
		throw InvalidArgumentException ("GUISFML::setPlayers: snakeP1 == null");
	}

	this->_snakeP1 = snakeP1;
	this->_snakeP2 = snakeP2;
}

void					GUISFML::loadBoard (unsigned int soundTrack)
{
	switch (soundTrack)
	{
		case 0:
			if (! this->_boardMusic.openFromFile ("ressources/sounds/ff_main_theme.wav"))
			{
				throw GUIException (this->_GUIName, "openFromFile 3 (*** MUSIC FILE ***)");
			}
			break;

		case 1:
			if (! this->_boardMusic.openFromFile ("ressources/sounds/Twin Musicom - 8-bit March.wav"))
			{
				throw GUIException (this->_GUIName, "openFromFile 3 (*** MUSIC FILE ***)");
			}
			break;

		case 2:
			if (! this->_boardMusic.openFromFile ("ressources/sounds/Twin Musicom - NES Theme.wav"))
			{
				throw GUIException (this->_GUIName, "openFromFile 3 (*** MUSIC FILE ***)");
			}
			break;

		case 3:
		default:
			if (! this->_boardMusic.openFromFile ("ressources/sounds/ff_main_theme.wav"))
			{
				throw GUIException (this->_GUIName, "openFromFile 3 (*** MUSIC FILE ***)");
			}
			break;
	}


	this->_mainMenuMusic.stop();
	this->_endMenuMusic.stop();
	this->_boardMusic.play();
	if (this->_muted)
		this->_boardMusic.pause();
	this->_boardMusic.setLoop (true);
	this->_boardMusic.setVolume (this->_musicVolume);
}

void					GUISFML::updateGameGUI (void)
{
	unsigned int currentGlobalScore;

	this->_window.clear (sf::Color::White);

	this->drawBoard();
	this->drawSnakes();
	this->drawScore();

	this->_window.display();

	currentGlobalScore = this->_snakeP1->getScore();
	if (this->_snakeP2)
		currentGlobalScore = currentGlobalScore > this->_snakeP2->getScore() ? currentGlobalScore : this->_snakeP2->getScore();

	if (currentGlobalScore > 95)
		currentGlobalScore = 95;

	sf::sleep (sf::milliseconds (100 - currentGlobalScore));
}

eGUIGameEvent			GUISFML::getGameEvent (void)
{
	sf::Event events;
	eSnakeDirection snakeP1CurrentDirection, snakeP2CurrentDirection;

	snakeP1CurrentDirection = this->_snakeP1->getCurrentDirection();
	if (this->_snakeP2)
		snakeP2CurrentDirection = this->_snakeP2->getCurrentDirection();

	while (this->_window.pollEvent (events))
	{
		switch (events.type)
		{
			case sf::Event::Closed:
				return eGUIGameEvent::quitGame;

			case sf::Event::KeyPressed:
				switch (events.key.code)
				{
					case sf::Keyboard::E:
						this->_snakeP1->eat (1);
						break;

					case sf::Keyboard::Escape:
						return eGUIGameEvent::quitGame;

					/* Player 1 commands */
					case sf::Keyboard::Left:
						if ((snakeP1CurrentDirection != eSnakeDirection::West) &&
							(snakeP1CurrentDirection != eSnakeDirection::East))
							return eGUIGameEvent::p1GoLeft;
						break;

					case sf::Keyboard::Right:
						if ((snakeP1CurrentDirection != eSnakeDirection::West) &&
							(snakeP1CurrentDirection != eSnakeDirection::East))
							return eGUIGameEvent::p1GoRight;
						break;

					case sf::Keyboard::Up:
						if ((snakeP1CurrentDirection != eSnakeDirection::North) &&
							(snakeP1CurrentDirection != eSnakeDirection::South))
							return eGUIGameEvent::p1GoUp;
						break;

					case sf::Keyboard::Down:
						if ((snakeP1CurrentDirection != eSnakeDirection::North) &&
							(snakeP1CurrentDirection != eSnakeDirection::South))
							return eGUIGameEvent::p1GoDown;
						break;

					/* Player 2 commands */
					case sf::Keyboard::Q:
						if (this->_snakeP2)
							if ((snakeP2CurrentDirection != eSnakeDirection::West) &&
								(snakeP2CurrentDirection != eSnakeDirection::East))
								return eGUIGameEvent::p2GoLeft;
						break;

					case sf::Keyboard::D:
						if (this->_snakeP2)
							if ((snakeP2CurrentDirection != eSnakeDirection::West) &&
								(snakeP2CurrentDirection != eSnakeDirection::East))
								return eGUIGameEvent::p2GoRight;
						break;

					case sf::Keyboard::Z:
						if (this->_snakeP2)
							if ((snakeP2CurrentDirection != eSnakeDirection::North) &&
								(snakeP2CurrentDirection != eSnakeDirection::South))
								return eGUIGameEvent::p2GoUp;
						break;

					case sf::Keyboard::S:
						if (this->_snakeP2)
							if ((snakeP2CurrentDirection != eSnakeDirection::North) &&
								(snakeP2CurrentDirection != eSnakeDirection::South))
								return eGUIGameEvent::p2GoDown;
						break;

					/* GUI Switchs */
					case sf::Keyboard::Num1:
					case sf::Keyboard::F1:
					case sf::Keyboard::Numpad1:
						this-> _wantedGUI = eGUI::SDL;
						return eGUIGameEvent::changeGUI;

					case sf::Keyboard::Num3:
					case sf::Keyboard::F3:
					case sf::Keyboard::Numpad3:
						this-> _wantedGUI = eGUI::openGL;
						return eGUIGameEvent::changeGUI;

					/* Audio */
					case sf::Keyboard::P:
						if (this->_boardMusic.getStatus() == sf::SoundSource::Status::Paused)
						{
							this->_boardMusic.play();
							this->_muted = false;
						}
						else
						{
							this->_boardMusic.pause();
							this->_muted = true;
						}
						break;

					case sf::Keyboard::Add:
						this->_musicVolume = this->_musicVolume + 5 <= 100 ?
											 this->_musicVolume + 5:
											 100;
						this->_boardMusic.setVolume (this->_musicVolume);
						break;

					case sf::Keyboard::Subtract:
						this->_musicVolume = this->_musicVolume >= 5 ?
											 this->_musicVolume - 5:
											 0;
						this->_boardMusic.setVolume (this->_musicVolume);
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

void					GUISFML::loadEndMenu (void)
{
	eBoardStatus boardStatus;
	std::string endMenuMusicName;

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

	if (! this->_endMenuMusic.openFromFile (endMenuMusicName))
	{
		throw GUIException (this->_GUIName, "openFromFile endMenuMusicName (*** MUSIC FILE ***)");
	}

	this->_mainMenuMusic.stop();
	this->_boardMusic.stop();
	this->_endMenuMusic.play();
	if (this->_muted)
		this->_endMenuMusic.pause();
	this->_endMenuMusic.setVolume (this->_musicVolume);

	this->_window.clear (sf::Color::White);

	this->drawEndMenu();

	this->_window.display();
}

eGUIEndMenuEvent		GUISFML::getEndMenuEvent (void)
{
	sf::Event events;

	while (this->_window.pollEvent (events))
	{
		switch (events.type)
		{
			case sf::Event::Closed:
				return eGUIEndMenuEvent::quitGame;

			case sf::Event::KeyPressed:
				switch (events.key.code)
				{
					case sf::Keyboard::Escape:
						return eGUIEndMenuEvent::quitGame;

					/* GUI Switchs */
					case sf::Keyboard::Num1:
					case sf::Keyboard::F1:
					case sf::Keyboard::Numpad1:
						this-> _wantedGUI = eGUI::SDL;
						return eGUIEndMenuEvent::changeGUI;

					case sf::Keyboard::Num3:
					case sf::Keyboard::F3:
					case sf::Keyboard::Numpad3:
						this-> _wantedGUI = eGUI::openGL;
						return eGUIEndMenuEvent::changeGUI;

					/* Audio */
					case sf::Keyboard::P:
						if (this->_endMenuMusic.getStatus() == sf::SoundSource::Status::Paused)
						{
							this->_endMenuMusic.play();
							this->_muted = false;
						}
						else
						{
							this->_endMenuMusic.pause();
							this->_muted = true;
						}
						break;

					case sf::Keyboard::Add:
						this->_musicVolume = this->_musicVolume + 5 <= 100 ?
											 this->_musicVolume + 5:
											 100;
						this->_endMenuMusic.setVolume (this->_musicVolume);
						break;

					case sf::Keyboard::Subtract:
						this->_musicVolume = this->_musicVolume >= 5 ?
											 this->_musicVolume - 5:
											 0;
						this->_endMenuMusic.setVolume (this->_musicVolume);
						break;

					default:
						break;
				}
				break;

			case sf::Event::MouseButtonReleased:
				if (events.mouseButton.button == sf::Mouse::Left)
				{
					if (this->_menuLeftButton.in (events.mouseButton.x, events.mouseButton.y))
						return eGUIEndMenuEvent::restartLevel;
					else if (this->_menuRightButton.in (events.mouseButton.x, events.mouseButton.y))
						return eGUIEndMenuEvent::nextLevel;
					else if (this->_menuMiddleButton.in (events.mouseButton.x, events.mouseButton.y))
						return eGUIEndMenuEvent::backToLobby;
					else if (this->_menuBottomButton.in (events.mouseButton.x, events.mouseButton.y))
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
