#include "../../includes/minishell.h"

int	ft_exit(char *exit_code)
{
	int		code;
	code = atoi(exit_code);
	exit(code);
}