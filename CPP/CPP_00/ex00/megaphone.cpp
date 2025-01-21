#include <iostream>

int	main(int argc, char **argv)
{
	int i;
	int	x;

	if (argc < 2)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}
	i = 0;
	while(++i < argc)
	{
		x = -1;
		while(argv[i][++x])
		{
			if ('a' <= argv[i][x] && argv[i][x] <= 'z')
				argv[i][x] -= 32;
			std::cout << argv[i][x];
		}
	}
	std::cout << std::endl;
	return (0);
}
