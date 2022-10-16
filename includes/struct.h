#ifndef STRUCT_H
# define STRUCT_H

# include <termios.h>
# include "define.h"
# include "../lib/libft/libft.h"

typedef struct s_global
{
	int		status;
	char	**env;
	struct termios settings;
	// char	*path;
} t_global;

typedef struct s_environ
{
	char				*key;
	char				*value;
	struct s_environ	*next;
}	t_environ;

typedef struct s_token
{
	enum e_token	type;
	char			*data;
	struct s_token	*next;
}				t_token;

typedef struct s_node
{
	enum e_type		type;
	t_token			*tokens;
	t_token			*words;
	t_token			*redir;
	int				state;
	struct s_node	*left;
	struct s_node	*right;
}				t_node;

typedef struct s_minishell
{
	t_node		*root;
	t_token		*tokens;
	t_list		*list;
	t_environ	*envp;
}				t_minishell;

#endif