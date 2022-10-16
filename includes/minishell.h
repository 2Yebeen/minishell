#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../lib/ft_printf/ft_printf.h"
# include "../lib/get_next_line/get_next_line.h"

# include "builtin.h"
# include "struct.h"

t_global	g_var;
t_environ	*get_envp_list(void);
void	make_env_list(t_environ **env_list);

#endif