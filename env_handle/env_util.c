#include "../header/minishell.h"

void	print_env(t_tok token)
{
	t_env *tmp = token.env_token;
	while (tmp)
	{
		printf("[%s]=[%s]\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}