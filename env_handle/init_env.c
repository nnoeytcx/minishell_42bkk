#include "../header/minishell.h"

char *getenv_value(char *env_v)
{
	if (env_v == NULL)
		return (NULL);
	while (*env_v != '=')
		env_v++;
	env_v++;
	char *value = ft_calloc(sizeof(char), (1 + ft_strlen(env_v)));
	int i = 0;
	while (env_v[i])
	{
		value[i] = env_v[i];
		i++;
	}
	return (value);
}

char *getenv_key(char *env_v)
{
	if (env_v == NULL)
		return (NULL);
	int i = 0;
	while(env_v[i] != '=')
		i++;
	char *key = ft_calloc(sizeof(char), ft_strlen(env_v));
	int j = 0;
	while(env_v[j] != '=')
	{
		key[j] = env_v[j];
		j++;
	}
	return (key);
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