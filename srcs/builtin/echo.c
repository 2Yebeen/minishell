#include "../../includes/minishell.h"

int	ft_echo(char **av)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (av[i] && ft_strncmp(av[i], "-n", ft_strlen(av[i])) == 0)
	{
		flag = 1;
		i++;
	}
	while (av[i])
	{
		ft_putstr_fd(av[i], STDOUT_FILENO);
		if (av[i + 1])
				write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (!flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
