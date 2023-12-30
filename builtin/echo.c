#include "../header/minishell.h"

int	ft_echo(char **param)
{
	int	option;
	int	i;

	if (param == NULL)
		return (dprintf(2, "ECHO : param is NULL"), 1);
	dprintf(2,"test\n");
	i = 0;
	while (param[i])
		i++;
	option = 0;
	if (i < 2)
		return (0);
	if (str_n_compare(param[1], "-n", ft_strlen(param[1])))
		option = 1;
	i = 1;
	while (param[i])
	{
		printf("%s ", param[i]);
		if (option != 1)
			printf("\n");
		i++;
	}
	return (0);
}