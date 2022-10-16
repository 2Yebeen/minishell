#include "../../includes/minishell.h"

t_environ	*get_envp_list(void)
{
	t_environ	*env_list;

	env_list = NULL;
	make_env_list(&env_list);
	return (env_list);
}
