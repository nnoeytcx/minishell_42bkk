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

t_env	*create_env(char **env)
{
	t_env 	*env_list;
	t_env	*res;
	int		i;

	if (!env)
		return (printf("ENV not found!!!\n"), NULL);
	i = 0;
	while (env[i])
	{
		if (i == 0)
		{
			env_list = new_env(env[i], NULL, O_WSTR);
			res = env_list;
			i++;
		}
		else
		{
			env_list->next = new_env(env[i], NULL, O_WSTR);
			env_list = env_list->next;
			i++;
		}
	}
	if_not_define("PATH", DEFAULT_PATH_VALUE, res);
	return (res);
}