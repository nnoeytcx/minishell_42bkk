#include "../header/minishell.h"

t_env	*new_env(char	*key, char	*value, int	mode)
{
	t_env	*new;

	if (key == NULL)
		return (NULL);
	new = ft_calloc(sizeof(t_env), 1);
	new->next = NULL;
	if (mode == O_KEYV)
	{
		new->key = ft_strdup(key);
		new->value = ft_strdup(value);
	}
	else if (mode == O_WSTR)
	{
		new->key = getenv_key(key);
		new->value = getenv_value(key);
	}
	return (new);
}

void	print_env(t_tok token)
{
	t_env *tmp = token.env_token;
	while (tmp)
	{
		printf("[%s]=[%s]\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}