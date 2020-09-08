#include <GUIOpenGL.class.hpp>

static unsigned int _mapWidth;
static unsigned int _mapHeight;

/*
 * Constructors
 */
GUIOpenGL::GUIOpenGL(Board *board)
	: _board (board), _snakeP1 (NULL), _snakeP2 (NULL),
	  _wantedGUI (eGUI::openGL),
	  _started (false)
{
	if (! board)
	{
		throw InvalidArgumentException ("GUIOpenGL::GUIOpenGL (Board *board, Snake *snake): board == null");
	}

	this-> _ac = new int[1];
	if (! this-> _ac)
	{
		throw ShouldNeverOccurException (__FILE__, __LINE__);
	}
	this->_ac[0] = 1;

	this-> _av = new char *[1];
	if (! this-> _ac)
	{
		throw ShouldNeverOccurException (__FILE__, __LINE__);
	}
	this->_av[0] = (char*)"GUIOpenGL";

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
GUIOpenGL::~GUIOpenGL(void)
{
	if (this->_ac)
		delete this->_ac;

	if (this->_av)
		delete this->_av;
}


/*
 * Private
 */
void					GUIOpenGL::ajustBounds (void)
{
	this->_mainMenuSinglePlayer.x *= this->_mainMenuSinglePlayer.x * _mapWidth / 1000;
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

void					GUIOpenGL::drawMainMenu (void)
{

}

void					GUIOpenGL::drawBoard (void)
{
	glClearColor (1.0f, 1.0f, 1.0f, 1.0f);
	glClear (GL_COLOR_BUFFER_BIT);

	gluOrtho2D (0.0, _mapWidth, 0.0, _mapHeight);

	glPointSize (100.0f);
//	glLineWidth (50.0f);

	glBegin (GL_POINTS);
//	glBegin (GL_LINES);
//	glBegin (GL_TRIANGLES);
//	glBegin (GL_QUADS);
		glColor3ub (255, 0, 0);
		glVertex2d (0.0, 0.0);

		glColor3ub (255, 255, 0);
		glVertex2d (_mapWidth, 0.0);

		glColor3ub (0, 255, 0);
		glVertex2d (_mapWidth, _mapHeight);

		glColor3ub (0, 0, 255);
		glVertex2d (0.0, _mapHeight);

	glEnd ();

	glFlush ();
}

void					GUIOpenGL::drawSnakes (void)
{

}

void					GUIOpenGL::drawEndMenu (void)
{

}

void					GUIOpenGL::resizeWindows (int width, int height)
{
	_mapWidth = width;
	_mapHeight = height;

	glutReshapeWindow (_mapWidth, _mapHeight);
//	glutDisplayFunc (this->drawBoard);

//	glViewport (0, 0, (GLsizei)_size, (GLsizei)_size);
//	glMatrixMode (GL_PROJECTION);
//	glLoadIdentity ();
//	if (height == 0)
//		height = 1;
//	gluPerspective (60, (GLfloat)width / (GLfloat)height, 0.0, 1.0);
//	glMatrixMode (GL_MODELVIEW);
}

/*
 * Public
 */
eGUI					GUIOpenGL::getGUIName (void) const
{
	return this->_GUIName;
}

void					GUIOpenGL::start (void)
{
	_mapWidth = this->_board->getWidth() * 10;
	_mapHeight = this->_board->getHeight() * 10;

	std::cout << "GUIOpenGL::start" << std::endl;
	glutInit (this->_ac, this->_av);
	glutInitDisplayMode (GLUT_SINGLE);
	glutInitWindowSize (_mapWidth, _mapHeight);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ((char *)"OpenGL - Creating a triangle");
//	glutDisplayFunc (this->drawBoard);
//	glutReshapeFunc (this->resizeWindows);
	glutMainLoop ();
	//	glutIdleFunc (snakeAnimation);

	this->ajustBounds ();

	this->_started = true;
}

bool					GUIOpenGL::alreadyStarted (void) const
{
	return this->_started;
}

eGUI					GUIOpenGL::wantedGUI (void) const
{
	return this->_wantedGUI;
}

void					GUIOpenGL::stop (void)
{
	this->_started = false;
}

/* Main Menu */

void					GUIOpenGL::loadMainMenu (void)
{

}

eGUIMainMenuEvent		GUIOpenGL::getMainMenuEvent (void)
{
	return eGUIMainMenuEvent::unknownMainMenuEvent;
}

/* Game */

void					GUIOpenGL::setPlayers (Snake *snakeP1, Snake *snakeP2)
{
	if (! snakeP1)
	{
		throw InvalidArgumentException ("GUIOpenGL::setPlayers: snakeP1 == null");
	}

	this->_snakeP1 = snakeP1;
	this->_snakeP2 = snakeP2;
}

void					GUIOpenGL::loadBoard (unsigned int soundTrack)
{

}

void					GUIOpenGL::updateGameGUI (void)
{
	this->drawBoard();
	this->drawSnakes();

//	SDL_RenderPresent (this->_boardRenderer);
//
//	currentGlobalScore = this->_snakeP1->getScore();
//	if (this->_snakeP2)
//		currentGlobalScore = currentGlobalScore > this->_snakeP2->getScore() ? currentGlobalScore : this->_snakeP2->getScore();
//
//	if (currentGlobalScore > 95)
//		currentGlobalScore = 95;
//
//	SDL_Delay (100 - currentGlobalScore);
}

eGUIGameEvent			GUIOpenGL::getGameEvent (void)
{
	return eGUIGameEvent::unknownGameEvent;
}

/* End Menu */

void					GUIOpenGL::loadEndMenu (void)
{

}

eGUIEndMenuEvent		GUIOpenGL::getEndMenuEvent (void)
{
	return eGUIEndMenuEvent::unknownEndMenuEvent;
}


/*
 * Extern
 */
GUIOpenGL				*createGUI (Board *board)
{
	return new GUIOpenGL (board);
}

void					destroyGUI (GUIOpenGL *GUI)
{
	delete GUI;
}
