#include "../header/minishell.h"

int	is_sp_symbol(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if (0 == ft_strncmp(">", str, len))
		return (1);
	else if (0 == ft_strncmp("<", str, len))
		return (1);
	else if (0 == ft_strncmp("<<", str, len))
		return (1);
	return (0);
}

int	set_mode(t_strm *str)
{
	t_strm	*stm;
	int		len;
	enum	type;
	if (!str)
		return (-1);
	stm = str;
	while (stm)
	{
		len = ft_strlen(stm->value);
		if (stm->type == def)
		{
			if (0 == ft_strncmp("\"", stm->value, 1))
				stm->type = double_quote_str;
			else if (0 == ft_strncmp("\'", stm->value, 1))
				stm->type = single_quote_str;
			else if (0 == ft_strncmp(">", stm->value, len))
			{
				stm->type = redout_symbol;
				if (stm->next && !is_sp_symbol(stm->next->value))
					stm->next->type = file_out_str;
				else
				{
					if (str->next)
						parser_error(str->next->value);
					else
						parser_error(NULL);
				}
			}
			else if (0 == ft_strncmp("<", stm->value, len))
			{
				stm->type = redin_symbol;
				if (stm->next && !is_sp_symbol(stm->next->value))
					stm->next->type = file_in_str;
				else
				{
					if (str->next)
						parser_error(str->next->value);
					else
						parser_error(NULL);
				}
			}
			else if (0 == ft_strncmp("<<", stm->value, len))
			{
				stm->type = h_doc_symbol;
				if (stm->next && !is_sp_symbol(stm->next->value))
					stm->next->type = h_doc_cut_str;
				else
				{
					if (str->next)
						parser_error(str->next->value);
					else
						parser_error(NULL);
				}
			}
			else if (0 == ft_strncmp(">>", stm->value, len))
			{
				stm->type = append_symbol;
				if (stm->next && !is_sp_symbol(stm->next->value))
					stm->next->type = file_out_append_str;
				else
				{
					if (str->next)
						parser_error(str->next->value);
					else
						parser_error(NULL);
				}
			}
			else if (0 == ft_strncmp("$", stm->value, 1))
				stm->type = variable;
			else
				stm->type = string;
		}
		stm = stm->next;
	}
	return (1);
}

int	in_value_split(t_strm *str)
{
	t_strm	*stm;
	t_strm	*new;
	int		len;
	int		i;
	char	*cmd;

	if (!str)
		return (-1);
	stm = str;
	while (stm)
	{
		cmd = stm->value;
		len = ft_strlen(cmd);
		i = 1;
		while (cmd[i])
		{
			
			i++;
		}
		stm = stm->next;
	}
	return (1);
}
