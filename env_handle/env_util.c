#include "../minishell.h"

void	print_env(t_tok token)
{
	t_env *tmp = token.env_token;
	while (tmp->next)
	{
		printf("[%s]=[%s]\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	printf("[output = %s]\n",get_value_from_key(tmp->key, token.env_token));
}