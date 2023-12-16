#include "../header/minishell.h"

// like if_not_define_function but can change the value and add the new key value
void	env_change_or_define(char *env_name, char *value, t_env *env_lst)
{
	t_env *lst;
	
	lst = env_lst;
	while (lst->next)
	{
		if (0 == ft_strncmp(env_name, lst->key, ft_strlen(env_name))) // << if unset the key will not found
		{
            free(lst->value);
            lst->value = ft_strdup(value);
            return ;
        }
		lst = lst->next;
	}
	lst->next = new_env(env_name, value, O_KEYV);
	lst = lst->next;
	return ;
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