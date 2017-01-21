#include <abstractVM.hpp>

int main (int ac, char **av)
{
	switch (ac)
	{
		case 1:
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
			exit (0);
			break;
	}
	return 0;
}
