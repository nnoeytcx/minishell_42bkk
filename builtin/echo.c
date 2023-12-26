#include "../header/minishell.h"

int	ft_echo(char **param, int fd)
{
	int option;

	option = 0;
	if (param == NULL)
		return (dprintf(2, "ECHO : param is NULL"), 1);
	if (fd < 0)
		return (dprintf(2, "ECHO : BAD fd"), 1);

	param++;
	if (str_n_compare(*param, "-n", ft_strlen(*param)))
		option == 1;
	while (*param)
	{
		dprintf(fd, "%s ", *param);
		if (option == 1)
			dprintf(fd, '\n');
		param++;
	}
	return (0);
}