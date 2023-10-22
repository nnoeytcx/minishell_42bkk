#include "env_handle.h"

char *get_value_from_key(char *key, t_env *token)
{
	if (key == NULL)
		return (NULL);
	t_env *tmp;
	tmp = token;
	while (tmp->next)
	{
		if (!strncmp(key, tmp->key, strlen(tmp->key)))
			return(tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}