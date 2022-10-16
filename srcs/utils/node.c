#include "../../includes/minishell.h"

t_node	*create_node(t_token *tokens)
{
	int		type;
	t_node	*root;

	root = NULL;
	if (tokens == NULL)
		return (NULL);
	root = ft_calloc(1, sizeof(t_node));
	if (!root)
	{
		printf("Error\n");
		exit(1);
	}
	type = node_type(tokens->type);

	root->type = type;
	root->tokens = tokens;
	root->state = 1;
	return (root);
}

void	insert_node(t_token **tokens, t_token *root)
{
	t_token	*token;

	token = NULL;
	if (!tokens || !root)
		return ;
	token = *tokens;
	while (token->next)
	{
		if (token->next == root)
			break ;
		token = token->next;
	}
	token->next = NULL;
}

void	del_node(t_node *node)
{
	if (!node)
		return ;
	if (node)
	{
		del_node(node->left);
		del_node(node->right);
		del_token(node->tokens);
		free(node);
		node = NULL;
	}
}

int	node_type(int token_type)
{
	int	node_type;

	node_type = 0;
	if (token_type == AND)
		node_type = TK_AND;
	else if (token_type == OR)
		node_type = TK_OR;
	else if (token_type == PIPE)
		node_type = TK_PIPE;
	else if (token_type == PARENS)
		node_type = TK_PARENS;
	else
		node_type = TK_WORD;
	return (node_type);
}
