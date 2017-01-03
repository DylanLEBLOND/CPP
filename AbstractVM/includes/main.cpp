#include "abstractVM.hpp"

int main (int ac, char **av)
{

	if (DEBUG)
		std::cout << "Debut du programme" << std::endl;

	switch (ac)
	{
		case 1:
			if (DEBUG)
				std::cout << "Flux: Standard Workflow" << std::endl;
			try
			{
				standard_workflow ();
			}
			catch (std::exception &e)
			{
				std::cerr << "Error: " << e.what() << std::endl;
			}
			break;
		case 2:
			if (DEBUG)
				std::cout << "Flux: File Workflow" << std::endl;
			try
			{
				file_workflow (av[1]);
			}
			catch (std::exception &e)
			{
				std::cerr << "Error: " << e.what() << std::endl;
			}
			break;
		default:
			if (DEBUG)
				std::cout << "Flux: Default" << std::endl;
			//TEMP INVALID PARAMETERS
			exit (0);
			break;
	}

	if (DEBUG)
		std::cout << "Fin du programme" << std::endl;
	return 0;
}
