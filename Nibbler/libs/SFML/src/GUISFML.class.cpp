#include <GUISFML.class.hpp>

static unsigned int _mapWidth;
static unsigned int _mapHeight;

/*
 * Constructors
 */
GUISFML::GUISFML (Board *board)
	: _board (board), _snakeP1 (NULL), _snakeP2 (NULL), _wantedGUI (eGUI::SFML),
	  _started (false)
{
	if (! board)
	{
		throw InvalidArgumentException ("GUISFML::GUISFML (Board *board, Snake *snake): board == null");
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

	this->_menuQuitButton.x = this->_menuQuitButton.x * _mapWidth / 1000;
	this->_menuQuitButton.y = this->_menuQuitButton.y * _mapHeight / 1000;
	this->_menuQuitButton.width = this->_menuQuitButton.width * _mapWidth / 1000;
	this->_menuQuitButton.height = this->_menuQuitButton.height * _mapHeight / 1000;
}

void					GUISFML::drawMainMenu (void)
{
	this->_window.clear (sf::Color::White);

	if (! this->_mainMenuTexture.loadFromFile ("res/images/main_menu.png"))
	{
		throw GUIException (this->_GUIName, "loadFromFile GUISFML::drawMainMenu");
	}
	this->_mainMenuTexture.setSmooth (true);

	this->_mainMenuSprite.setTexture (this->_mainMenuTexture);
	this->_mainMenuSprite.setScale (sf::Vector2f ((float)_mapWidth / 1000.0f, (float)_mapHeight / 1000.0f));

	this->_window.draw (this->_mainMenuSprite);
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
				boardCellDraw.setPosition (x * 10, y * 10);
				this->_window.draw (boardCellDraw);
			}
		}
	}
}

void					GUISFML::drawSnakes (void)
{
	std::list<t_cell> snakeCells;
	std::list<t_cell>::iterator itSnakeCell;
	sf::RectangleShape snakeCellDraw;

	snakeCells = this->_snakeP1->getSnakeCells();

	snakeCellDraw.setSize (sf::Vector2f (10.f, 10.f));

	snakeCellDraw.setFillColor (sf::Color (0, 255, 0));
	for (itSnakeCell = snakeCells.begin(); itSnakeCell != snakeCells.end(); ++itSnakeCell)
	{
		snakeCellDraw.setPosition (itSnakeCell->positionX * 10, itSnakeCell->positionY * 10);
		this->_window.draw (snakeCellDraw);
	}

	if (this->_snakeP2)
	{
		snakeCells = this->_snakeP2->getSnakeCells();

		snakeCellDraw.setFillColor (sf::Color (0, 255, 255));
		for (itSnakeCell = snakeCells.begin(); itSnakeCell != snakeCells.end(); ++itSnakeCell)
		{
			snakeCellDraw.setPosition (itSnakeCell->positionX * 10, itSnakeCell->positionY * 10);
			this->_window.draw (snakeCellDraw);
		}
	}
}

void					GUISFML::drawEndMenu (void)
{
	std::string endMenuFilename;

	if (this->_snakeP1->isAlive())
	{
		if (this->_snakeP2)
		{
			if (this->_snakeP2->isAlive())
				endMenuFilename = "res/images/multiplayer_draw.png";
			else
				endMenuFilename = "res/images/multiplayer_player1_win.png";
		}
		else
			endMenuFilename = "res/images/singleplayer_win.png";;
	}
	else
	{
		if (this->_snakeP2)
		{
			if (this->_snakeP2->isAlive())
				endMenuFilename = "res/images/multiplayer_player2_win.png";
			else
				endMenuFilename = "res/images/multiplayer_draw.png";
		}
		else
			endMenuFilename = "res/images/singleplayer_lose.png";
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
	_mapWidth = this->_board->getWidth() * 10;
	_mapHeight = this->_board->getHeight() * 10;

#ifdef PROJ_DEBUG
	std::cout << "GUISFML::start" << std::endl;
#endif

	this->_window.create (sf::VideoMode (_mapWidth, _mapHeight), "Nibbler (SFML GUI)", sf::Style::Titlebar | sf::Style::Close);
	this->_window.setPosition (sf::Vector2i (100, 100));
	this->_window.setFramerateLimit (60);
	this->_window.setVerticalSyncEnabled (true);

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

	this->_window.close();

	this->_started = false;
}

/* Main Menu */

void					GUISFML::loadMainMenu (void)
{
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
					/* GUI Switchs */
					case sf::Keyboard::Num1:
					case sf::Keyboard::Numpad1:
						this-> _wantedGUI = eGUI::SDL;
						return eGUIMainMenuEvent::changeGUI;

					case sf::Keyboard::Numpad3:
					case sf::Keyboard::Num3:
						this-> _wantedGUI = eGUI::openGL;
						return eGUIMainMenuEvent::changeGUI;

					case sf::Keyboard::Escape:
						return eGUIMainMenuEvent::quitGame;

					default:
						return eGUIMainMenuEvent::nothingTODO;
				}

			case sf::Event::MouseButtonReleased:
				if (events.mouseButton.button == sf::Mouse::Left)
				{
					if (this->_menuLeftButton.in (events.mouseButton.x, events.mouseButton.y))
						return eGUIMainMenuEvent::startSinglePlayerGame;
					else if (this->_menuRightButton.in (events.mouseButton.x, events.mouseButton.y))
						return eGUIMainMenuEvent::startMultiPlayerGame;
					else if (this->_menuQuitButton.in (events.mouseButton.x, events.mouseButton.y))
						return eGUIMainMenuEvent::quitGame;
				}
				break;

			default:
				return eGUIMainMenuEvent::nothingTODO;
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

void					GUISFML::updateGameGUI (void)
{
	unsigned int currentGlobalScore;

	this->_window.clear (sf::Color::White);

	this->drawBoard();
	this->drawSnakes();

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

					/* Player 1 commands */
					case sf::Keyboard::Left:
						return eGUIGameEvent::p1GoLeft;

					case sf::Keyboard::Right:
						return eGUIGameEvent::p1GoRight;

					case sf::Keyboard::Up:
						return eGUIGameEvent::p1GoUp;

					case sf::Keyboard::Down:
						return eGUIGameEvent::p1GoDown;

					/* Player 2 commands */
					case sf::Keyboard::Q:
						if (this->_snakeP2)
							return eGUIGameEvent::p2GoLeft;
						break;

					case sf::Keyboard::D:
						if (this->_snakeP2)
							return eGUIGameEvent::p2GoRight;
						break;

					case sf::Keyboard::Z:
						if (this->_snakeP2)
							return eGUIGameEvent::p2GoUp;
						break;

					case sf::Keyboard::S:
						if (this->_snakeP2)
							return eGUIGameEvent::p2GoDown;
						break;

					/* GUI Switchs */
					case sf::Keyboard::Num1:
					case sf::Keyboard::Numpad1:
						this-> _wantedGUI = eGUI::SDL;
						return eGUIGameEvent::changeGUI;

					case sf::Keyboard::Numpad3:
					case sf::Keyboard::Num3:
						this-> _wantedGUI = eGUI::openGL;
						return eGUIGameEvent::changeGUI;

					case sf::Keyboard::Escape:
						return eGUIGameEvent::quitGame;

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
					/* GUI Switchs */
					case sf::Keyboard::Num1:
					case sf::Keyboard::Numpad1:
						this-> _wantedGUI = eGUI::SDL;
						return eGUIEndMenuEvent::changeGUI;

					case sf::Keyboard::Numpad3:
					case sf::Keyboard::Num3:
						this-> _wantedGUI = eGUI::openGL;
						return eGUIEndMenuEvent::changeGUI;

					case sf::Keyboard::Escape:
						return eGUIEndMenuEvent::quitGame;

					default:
						return eGUIEndMenuEvent::nothingTODO;
				}

			case sf::Event::MouseButtonReleased:
				if (events.mouseButton.button == sf::Mouse::Left)
				{
					if (this->_menuLeftButton.in (events.mouseButton.x, events.mouseButton.y))
						return eGUIEndMenuEvent::restartLevel;
					else if (this->_menuRightButton.in (events.mouseButton.x, events.mouseButton.y))
						return eGUIEndMenuEvent::nextLevel;
					else if (this->_menuQuitButton.in (events.mouseButton.x, events.mouseButton.y))
						return eGUIEndMenuEvent::quitGame;
				}
				break;

			default:
				return eGUIEndMenuEvent::nothingTODO;
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
