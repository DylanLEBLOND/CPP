#include <GUIOpenGL.class.hpp>


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

	glPointSize (50.0f);
//	glLineWidth (50.0f);

	glBegin (GL_POINTS);
//	glBegin (GL_LINES);
//	glBegin (GL_TRIANGLES);
//	glBegin (GL_QUADS);
		glColor3ub (255, 0, 0);
		glVertex2f (0.0f, 0.0f);

		glColor3ub (255, 255, 0);
		glVertex2f (-0.1f, 0.0f);

		glColor3ub (255, 0, 255);
		glVertex2f (0.1f, 0.0f);

		glColor3ub (0, 255, 0);
		glVertex2f (-1.0f, -1.0f);

		glColor3ub (0, 0, 255);
		glVertex2f (1.0f, 1.0f);

	glEnd ();

	glFlush ();
}

/*
 * Public
 */
bool			GUIOpenGL::start (void)
{
	std::cout << "GUIOpenGL::start" << std::endl;
	glutInit (this->_ac, this->_av);
	glutInitDisplayMode (GLUT_SINGLE);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (0, 0);
	glutCreateWindow ((char *)"OpenGL - Creating a triangle");
	glutDisplayFunc (drawTriangle);
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
