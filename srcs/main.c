#include "../includes/minishell.h"

static void	shell_loop(void);
static void	sig_handler(int signo);
static void	show_list_contents(t_list *ist);
static void	ft_nodisplay_ctrlx_set(void);
static void	ft_display_ctrlx_set(void);
static void	parse_exec(char *cli_str);
void	show_env_list(t_environ *env_list);

int	main(int ac, char **av, char **envp)
{
	ft_start_screen();
	(void)ac;
	(void)av;
	g_var.status = 0;
	g_var.env = envp;
	ft_nodisplay_ctrlx_set();
	shell_loop();
	ft_display_ctrlx_set();
	return (0);
}

static void	shell_loop()
{
	char 		*cli_str;

	while (LOOP)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		cli_str = readline("minsh$ ");
		if (cli_str)
		{
			parse_exec(cli_str);
		}
		else
		{
			printf("\033[1A");
			printf("\033[7C");
			printf("exit\n");
			free(cli_str);
			ft_display_ctrlx_set();
			exit(1);
		}
	}
}

static void	parse_exec(char *cli_str)
{
	t_minishell	sh;
	int			result;

	sh.envp = NULL;
	sh.list = NULL;
	sh.root = NULL;
	sh.tokens = NULL;
	sh.envp = get_envp_list();
	ft_lstadd_back(&sh.list, get_token_list(cli_str));
	result = tokenizer(&sh);
	if ( result == ERROR)
	{
		add_history(cli_str);
		free(cli_str);
		cli_str = NULL;
	}
	else
	{
		sh.root = create_node(sh.tokens);
		parsing(sh.root);
		show_wordnode_data(sh.root, "......FOR REDIRECTIONS......");
		exec_parse_tree(sh.root, sh.envp);
		add_history(cli_str);
		free(cli_str);
		cli_str = NULL;
	}
}

static void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", ON);
		rl_redisplay();
	}
	return;
}

void	show_env_list(t_environ *env_list)
{
	t_environ *tmp;

	tmp = env_list;
	while (tmp)
	{
		printf("show : %s === %s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

static void	show_list_contents(t_list *list)
{
	t_list	*tmp;

	if (!list)
		return;
	tmp = list;
	printf("\033[0;31m");
	printf("list : \n");
	while (tmp)
	{
		printf("\033[0;31m");
		printf("[%s]", (char *)tmp->content);
		tmp = tmp->next;
	}
	printf("\n");
	printf("\n\033[0;0m\x1b[1A\x1b[M");
}

void	show_tokens_data(t_token *tokens)
{
	t_token *tmp;

	if (!tokens)
		return;
	tmp = tokens;
	printf("\033[0;33m");
	printf("token : \n");
	printf("token type = %d\n", tmp->type);
	while (tmp)
	{
		printf("\033[0;33m");
		printf("[%s]", tmp->data);
		tmp = tmp->next;
	}
	printf("\n");
	printf("\n\033[0;0m\x1b[1A\x1b[M");
}

void	show_node_data(t_node *node, char *str)
{
	t_node	*tmp;

	if (!node)
		return;
	tmp = node;
	if (!tmp)
		return;
	printf("\033[0;36m");
	printf("node  - %s :\n", str);
	show_tokens_data(node->tokens);
	show_node_data(tmp->left, "left");
	show_node_data(tmp->right, "right");
	printf("\n\033[0;0m\x1b[1A\x1b[M");
}

static void	ft_nodisplay_ctrlx_set(void)
{
	if (tcgetattr(STDIN_FILENO, &g_var.settings) == ERROR)
		ft_perror("minsh: tcgetattr");
	g_var.settings.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &g_var.settings) == ERROR)
		ft_perror("minsh: tcsetattr");
}

static void	ft_display_ctrlx_set(void)
{
	if (tcgetattr(STDIN_FILENO, &g_var.settings) == ERROR)
		ft_perror("minsh: tcgetattr");
	g_var.settings.c_lflag &= ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &g_var.settings) == ERROR)
		ft_perror("minsh: tcsetattr");
}

void	ft_perror(char *str)
{
	printf("%s %s\n", str, strerror(errno));
}
