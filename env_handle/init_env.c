#include "env_handle.h"

char *getenv_value(char *env_v)
{
	if (env_v == NULL)
		return (NULL);
	while (*env_v != '=')
		env_v++;
	env_v++;
	char *value = calloc(sizeof(char), (1 + strlen(env_v)));
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

int init_env_token(t_tok *token, char **env)
{
	if (!env)
		return(printf("env not found take the risk!!!!\n"), 1);
	int i = 0;
	(*token).env_token = ft_calloc(sizeof(t_env),1);
	t_env *tmp = (*token).env_token;
	while (env[i])
	{
	//	printf("\n-------------- [%s] -------------------\n",env[i]);
		(*token).env_token->key = getenv_key(env[i]);
	//	printf("[key is %s]\n", (*token).env_token->key);
		(*token).env_token->value = getenv_value(env[i]);
	//	printf("[value is %s]\n\n", (*token).env_token->value);
		(*token).env_token->next = ft_calloc(sizeof(t_env), 1);
		(*token).env_token->next->next = NULL;
		(*token).env_token = (*token).env_token->next;
		i++;
	}
	(*token).env_token = tmp;
}