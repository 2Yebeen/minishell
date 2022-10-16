#include "../../includes/minishell.h"

void	ft_env(char **envs)
{
	int	i;

	i = 0;
	while (envs[i])
	{
		write(STDOUT_FILENO, envs[i], ft_strlen(envs[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}