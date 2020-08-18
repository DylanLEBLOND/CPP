#include <nibbler.hpp>

int main (int ac, char **av)
{
	void *handle_GUIopenGL;
	Board board;
	Snake snake;
	IGUI *currentGUI;

	IGUI *(*createGUI)(Board, Snake, int *, char **);
	void (*destroyGUI)(IGUI *);

	handle_GUIopenGL = dlopen ("./libs/openGL/lib/libguiopengl.so", RTLD_LAZY);
	if (handle_GUIopenGL == NULL)
	{
		std::cerr << "dlopen GUIopenGL Failed" << std::endl;
		exit (0);
	}
	std::cout << "dlopen GUIopenGL Success" << std::endl;

	createGUI = (IGUI *(*)(Board, Snake, int *, char **)) dlsym (handle_GUIopenGL, "createGUI");
	if (createGUI == NULL)
	{
		std::cerr << "dlsym createGUI Failed" << std::endl;
		exit (0);
	}
	std::cout << "dlsym createGUI Success" << std::endl;

	destroyGUI = (void (*)(IGUI *)) dlsym (handle_GUIopenGL, "destroyGUI");
	if (destroyGUI == NULL)
	{
		std::cerr << "dlsym destroyGUI Failed" << std::endl;
		exit (0);
	}
	std::cout << "dlsym destroyGUI Success" << std::endl;

	currentGUI = createGUI (board, snake, &ac, av);
	if (currentGUI == NULL)
	{
		std::cerr << "createGUI GUIopenGL Failed" << std::endl;
		exit (0);
	}
	std::cout << "createGUI GUIopenGL Success" << std::endl;

	if (! currentGUI->start (std::stoi (av[1])))
	{
		std::cerr << "start GUIopenGL Failed" << std::endl;
		exit (0);
	}
	std::cout << "start GUIopenGL Success" << std::endl;

	destroyGUI (currentGUI);

	dlclose (handle_GUIopenGL);

	switch (ac)
	{
		case 1:
			break;
		case 2:
			(void)av[1];
			break;
		default:
			break;
	}
	return 0;
}
