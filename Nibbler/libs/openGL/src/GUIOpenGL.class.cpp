#include <GUIOpenGL.class.hpp>

static int _size;

/*
 * Constructors
 */
GUIOpenGL::GUIOpenGL(Board &board, Snake &snake, int *ac, char **av)
	: _board (board), _snake (snake), _ac (ac), _av (av), _GUISwitch (eGUISwitch::openGL) { }

/*
 * Destructor
 */
GUIOpenGL::~GUIOpenGL(void) {}


/*
 * Private
 */
void			GUIOpenGL::drawTriangle (void)
{
	glClearColor (1.0f, 1.0f, 1.0f, 1.0f);
	glClear (GL_COLOR_BUFFER_BIT);

	gluOrtho2D (0.0, _size, 0.0, _size);

	glPointSize (100.0f);
//	glLineWidth (50.0f);

	glBegin (GL_POINTS);
//	glBegin (GL_LINES);
//	glBegin (GL_TRIANGLES);
//	glBegin (GL_QUADS);
		glColor3ub (255, 0, 0);
		glVertex2d (0.0, 0.0);

		glColor3ub (255, 255, 0);
		glVertex2d (_size, 0.0);

		glColor3ub (0, 255, 0);
		glVertex2d (_size, _size);

		glColor3ub (0, 0, 255);
		glVertex2d (0.0, _size);

	glEnd ();

	glFlush ();
}

void			GUIOpenGL::resizeWindows (int width, int height)
{
	_size = width;

	glutReshapeWindow (_size, _size);
	glutDisplayFunc (drawTriangle);

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
bool			GUIOpenGL::start (int size)
{
	_size = size;

	std::cout << "GUIOpenGL::start" << std::endl;
	glutInit (this->_ac, this->_av);
	glutInitDisplayMode (GLUT_SINGLE);
	glutInitWindowSize (_size, _size);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ((char *)"OpenGL - Creating a triangle");
	glutDisplayFunc (drawTriangle);
	glutReshapeFunc (resizeWindows);
	glutMainLoop ();
	//	glutIdleFunc (snakeAnimation);

	return true;
}

eGUISwitch		GUIOpenGL::getGUISwitch (void) const
{
	return this->_GUISwitch;
}

/*
 * Extern
 */
GUIOpenGL		*createGUI (Board &board, Snake &snake, int *ac, char **av)
{
	return new GUIOpenGL (board, snake, ac, av);
}

void			destroyGUI (GUIOpenGL *GUI)
{
	delete GUI;
}
