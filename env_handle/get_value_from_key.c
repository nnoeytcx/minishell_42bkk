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

char *get_value_from_key(char *key, t_env *token)
{
	if (key == NULL)
		return (NULL);
	t_env *tmp;
	tmp = token;
	while (tmp->next)
	{
		if (!ft_strncmp(key, tmp->key, ft_strlen(tmp->key)))
			return(ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}