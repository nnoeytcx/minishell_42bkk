/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpoungla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 00:04:12 by tpoungla          #+#    #+#             */
/*   Updated: 2024/01/07 06:36:15 by tpoungla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	print_command_tab(t_cmd *cmd)
{
	int		k;
	t_cmd	*tmp;
	t_strm	*stt;

	k = 0;
	tmp = cmd;
	while (tmp != NULL)
	{
		stt = tmp->str_mode;
		dprintf(2, "\n - {%d} cmd [%p] -\n\n", k, cmd);
		while (stt)
		{
			dprintf(2, "[%s] mode [%d] -> ", stt->value, stt->type);
			stt = stt->next;
		}
		k++;
		tmp = tmp->next;
	}
	dprintf (2, "\n\033[0;97m");
}

void	print_tok(t_tok t)
{
	printf("\n\033[1;34m-----token-----\n");
	print_command_tab((t.command));
}

char	*get_newstr_expand(int num[2], char *new_str, \
		char const *s, t_tok *token)
{
	char	*substr;
	char	*tmpstr;
	int		k;
	int		len;

	len = num[0];
	k = num[1];
	if (s[k] == '\"')
	{
		len -= 2;
		k += 1;
	}
	substr = ft_substr(s, k, len);
	tmpstr = get_expand(substr, token);
	free(substr);
	substr = new_str;
	new_str = ft_strjoy(substr, tmpstr);
	free(substr);
	free(tmpstr);
	return (new_str);
}

int	check_quote_close(const char *c)
{
	char	qt;

	qt = 0;
	while (*c)
	{
		qt = get_quote_trigger(qt, c);
		c++;
	}
	if (qt != 0)
		return (0);
	return (1);
}

int	check_no_space(const char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (!ft_isspace(c[i]))
			return (1);
		i++;
	}
	return (0);
}
