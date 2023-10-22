#include "../minishell.h"

int	overflow_welcome(int lob)
{
	if (lob == -1)
		lob = 0;
	if (lob == 1)
		lob = -1;
	return (lob);
}

int	ft_atoi(const char *str)
{
	int				len;
	int				lob;
	unsigned long	result;

	len = 0;
	result = 0;
	lob = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v'\
				|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			lob = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
		len++;
	}
	if (len > 19 || result > 9223372036854775807)
		return (overflow_welcome(lob));
	return ((int)(result * lob));
}

unsigned int	plz_count(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
		n = n * -1;
		len++;
	}
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

void	min_int_welcome(int *n, char *a, unsigned int *len)
{
	if (*n == -2147483648)
	{
		a[*len - 1] = '8';
		*n = 214748364;
		*len = *len - 1;
	}
}

char	*ft_itoa(int n)
{
	char			*a;
	unsigned int	len;

	len = plz_count(n);
	a = ft_calloc((len + 1), sizeof(char));
	if (!a)
		return (0);
	if (n == 0)
		a[0] = '0';
	if (n < 0)
	{
		n = n * -1;
		a[0] = '-';
	}
	min_int_welcome(&n, a, &len);
	while (n && len > 0)
	{
		a[len-- - 1] = ('0' + (n % 10));
		n = n / 10;
	}
	return (a);
}

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
		if (!ft_strncmp((*token).env_token->key,"SHLVL",ft_strlen("SHLVL")))
		{
			int shvl = ft_atoi((*token).env_token->value);
			shvl = shvl + 1;
			free((*token).env_token->value);
			(*token).env_token->value = ft_itoa(shvl);
		}
	//	printf("[value is %s]\n\n", (*token).env_token->value);
		(*token).env_token->next = ft_calloc(sizeof(t_env), 1);
		(*token).env_token->next->next = NULL;
		(*token).env_token = (*token).env_token->next;
		i++;
	}
	(*token).env_token = tmp;
	return (0);
}
