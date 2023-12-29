#include "../header/minishell.h"

int	ft_echo(char **param)
{
	int option;

	option = 0;
	if (param == NULL)
		return (dprintf(2, "ECHO : param is NULL"), 1);

	param++;
	if (str_n_compare(*param, "-n", ft_strlen(*param)))
		option == 1;
	while (*param)
	{
		printf("%s ", *param);
		if (option == 1)
			printf("\n");
		param++;
	}
	return (0);
}