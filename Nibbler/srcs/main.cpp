#include <nibbler.hpp>

int main (int ac, char **av)
{
	void *handle_GUISDL;
	Board board (std::stoi (av[1]));
	Snake snake (10, 10, 3, true);
	IGUI *currentGUI;

	IGUI *(*createGUI)(Board *, Snake *, int *, char **);
	void (*destroyGUI)(IGUI *);

	handle_GUISDL = dlopen ("./libs/SDL/lib/libguisdl.so", RTLD_LAZY);
	if (handle_GUISDL == NULL)
	{
		std::cerr << "dlopen GUISDL Failed" << std::endl;
		exit (0);
	}
	std::cout << "dlopen GUISDL Success" << std::endl;

	createGUI = (IGUI *(*)(Board *, Snake *, int *, char **)) dlsym (handle_GUISDL, "createGUI");
	if (createGUI == NULL)
	{
		std::cerr << "dlsym createGUI Failed" << std::endl;
		exit (0);
	}
	std::cout << "dlsym createGUI Success" << std::endl;

	destroyGUI = (void (*)(IGUI *)) dlsym (handle_GUISDL, "destroyGUI");
	if (destroyGUI == NULL)
	{
		std::cerr << "dlsym destroyGUI Failed" << std::endl;
		exit (0);
	}
	std::cout << "dlsym destroyGUI Success" << std::endl;

	currentGUI = createGUI (&board, &snake, &ac, av);
	if (currentGUI == NULL)
	{
		std::cerr << "createGUI GUISDL Failed" << std::endl;
		exit (0);
	}
	std::cout << "createGUI GUISDL Success" << std::endl;

	currentGUI->start();

	std::cout << "start GUISDL Success" << std::endl;

	while (currentGUI->run());

	destroyGUI (currentGUI);

//	std::cout << "MAIN Snake pos x = " << snake.getPositionX() << " | y = " << snake.getPositionY() << std::endl;

	dlclose (handle_GUISDL);

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
