#include "pipex.h"

int	main(int ac, char **av)
{
	if (ac != 5)
	{
		ft_putstr_fd("Too few arguments.\n", 2);
		return (1);
	}
	else
	{
		ft_putstr_fd(av[0], 1);
	}
	return (0);
}
	
