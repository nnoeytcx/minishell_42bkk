#include "../header/minishell.h"

int	ft_env(t_env *env_list)
{
	t_env *lst;

	lst = env_list;
	if (!env_list)
		dprintf(2, "ENV : env variable is not set\n", 1);
	lst = env_list;
	while (lst)
	{
		printf("%s=%s\n", lst->key, lst->value);
		lst = lst->next;
	}
	return (0);
}