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

void	if_not_define(char *env_name, char *value, t_env *env_lst)
{
	t_env *lst;
	
	lst = env_lst;
	while (lst->next)
	{
		if (0 == ft_strncmp(env_name, lst->key, ft_strlen(env_name))) // << if unset the key will not found
			return ;
		lst = lst->next;
	}
	lst->next = new_env(env_name, value, O_KEYV);
	lst = lst->next;
	return ;
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