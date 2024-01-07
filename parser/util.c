/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpoungla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 03:29:59 by tpoungla          #+#    #+#             */
/*   Updated: 2024/01/07 07:43:16 by tpoungla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	in_check_meta(char **res, int i, char two)
{
	char	temp;

	temp = res[i][0];
	if ((two && (is_meta(temp) && (two == '<' || two == '>'))) || \
	(i == 0 && temp == '|'))
	{
		parser_error2(temp);
		free_me(res);
		return (0);
	}
	return (1);
}

void	set_type(t_strm *stm, int type, int next_type)
{
	stm->type = type;
	if (stm->next)
		stm->next->type = next_type;
}

void	in_cmd_tab(t_strm *set[3], char **cmd_arg, int i)
{
	if (i == 0)
	{
		set[0] = new_str_with_mode(cmd_arg[i]);
		set[1] = set[0];
	}
	else
	{
		set[2] = new_str_with_mode(cmd_arg[i]);
		set[0]->next = set[2];
		set[0] = set[2];
	}
}

char	*joy_str(char *s, int num[2], char *new_str)
{
	char	*substr;
	char	*tmpstr;

	tmpstr = ft_substr(s, num[1] + 1, num[0] - 2);
	substr = new_str;
	new_str = ft_strjoy(substr, tmpstr);
	free(substr);
	free(tmpstr);
	return (new_str);
}

char	*new_str_getex(char *s, int num[2], t_tok *tok, char *new)
{
	int		k;
	int		len;
	char	*substr;
	char	*tmpstr;

	k = num[0];
	len = num[1];
	if (!len)
		return (new);
	substr = ft_substr(s, k, len);
	tmpstr = find_dollarsign(substr, tok);
	free(substr);
	substr = new;
	new = ft_strjoy(substr, tmpstr);
	free(tmpstr);
	free(substr);
	return (new);
}
