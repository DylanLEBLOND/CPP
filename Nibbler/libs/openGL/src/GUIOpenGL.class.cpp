#include <GUIOpenGL.class.hpp>

static unsigned int _mapWidth;
static unsigned int _mapHeight;

/*
 * Constructors
 */
GUIOpenGL::GUIOpenGL(Board *board, Snake *snake)
	: _board (board), _snakeP1 (snake), _snakeP2 (NULL),
	  _wantedGUI (eGUI::openGL),
	  _started (false)
{
	if (! board)
	{
		throw InvalidArgumentException ("GUIOpenGL::GUIOpenGL (Board *board, Snake *snake): board == null");
	}

	if (! snake)
	{
		throw InvalidArgumentException ("GUIOpenGL::GUIOpenGL (Board *board, Snake *snake): snake == null");
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
}

GUIOpenGL::GUIOpenGL(Board *board, Snake *snakeP1, Snake *snakeP2)
	: _board (board), _snakeP1 (snakeP1), _snakeP2 (snakeP2),
	  _wantedGUI (eGUI::openGL),
	  _started (false)
{
	if (! board)
	{
		throw InvalidArgumentException ("GUIOpenGL::GUIOpenGL (Board *board, Snake *snake): board == null");
	}

	if (! snakeP1 || ! snakeP2)
	{
		throw InvalidArgumentException ("GUIOpenGL::GUIOpenGL (Board *board, Snake *snakeP1, Snake *snakeP2): snakeP1 and/or snakeP2 == null");
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
void				GUIOpenGL::drawBoard (void)
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

void				GUIOpenGL::drawSnakes (void)
{

}

void				GUIOpenGL::drawMenu (void)
{

}

void				GUIOpenGL::resizeWindows (int width, int height)
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
eGUI				GUIOpenGL::getGUIName (void) const
{
	return this->_GUIName;
}

void				GUIOpenGL::start (void)
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

	this->_started = true;
}

bool				GUIOpenGL::alreadyStarted (void) const
{
	return this->_started;
}

void				GUIOpenGL::stop (void)
{
	this->_started = false;
}

eGUIEvent			GUIOpenGL::getEvent (void)
{
	return eGUIEvent::unknownEvent;
}

void				GUIOpenGL::updateGUI (void)
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

eGUI				GUIOpenGL::wantedGUI (void) const
{
	return this->_wantedGUI;
}

void				GUIOpenGL::loadMenu (void)
{

}

eGUIMenuEvent		GUIOpenGL::getMenuEvent (void)
{
	return eGUIMenuEvent::unknownMenuEvent;
}


/*
 * Extern
 */
GUIOpenGL			*createGUI (Board *board, Snake *snakeP1, Snake *snakeP2)
{
	if (! snakeP2)
		return new GUIOpenGL (board, snakeP1);
	return new GUIOpenGL (board, snakeP1, snakeP2);
}

void				destroyGUI (GUIOpenGL *GUI)
{
	delete GUI;
}
