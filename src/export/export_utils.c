#include "minishell.h"

int ft_strlen_env(char *en)
{
	int i;

	i = 0;
	while (en[i])
		i ++;
	return (i);
}

void	print_exp(char **exp)
{
	int i;

	i = -1;
	while (exp[++ i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(exp[i], 1);
		ft_putstr_fd("\n", 1);
	}
}

void free_exp(char **exp)
{
    int i;
    
	i = 0;
	while (exp[i])
	{
		free(exp[i]);
		i ++;
	}
	free(exp);
}

int check_val(char c)
{
	if (c == '\0')
		return (0);
	if (c == 33 || c == 40 || c == 41)
		return (1);
	return (-1);
}

int	check_key(char c)
{
	if (c == '\0')
		return (0);
	if ((c >= 33 && c <= 45) || (c >= 46 && c <= 47) || (c == 64) || (c == 91) || (c >= 93 && c <= 94) || (c == 96))
		return (1);
	return (-1);
}

char *parse_while(char *res, char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != 61)
	{
		if (check_key(s[i]) == 0)
			break ;
		if (s[i] == 92)
		{
			i ++;
			continue;
		}
		res[j] = s[i];
		i ++;
		j ++;
	}
	return (res);
}

char *parse_inf_key(char *s)
{
	int i;
	int	j;
	char *res;

	i = 0;
	j = 0;
	while (s[i] != 61)
	{
		if (check_key(s[i]) == 0)
			break ;
		if (s[i] == 92)
		{
			i ++;
			continue;
		}
		i ++;
		j ++;
	}
	res = (char *)malloc(j + 1);
	if (!res)
		exit_ms("error malloc", -1);
	res[j] = 0;
	return (parse_while(res, s));
}

char *one_c(char *c, int flag)
{
	if (flag == 1)
	{
		c = malloc(sizeof(char));
		if (!c)
			exit_ms("error malloc", -1);
		c[0] = '\0';
		return (c);
	}
	else
	{
		c = malloc(sizeof(char) + 1);
		if (!c)
			exit_ms("error malloc", -1);
		c[0] = '=';
		c[1] = '\0';
		return (c);
	}
}

char *val_malloc(char *s, char *res)
{

	if (*s == 61 && !(*s + 1))
		return (one_c(res, 2));
	s ++;
	res = ft_strdup(s);
	return (res);
}

char *parse_inf_val(char *s)
{
	char *res;

	res = 0;
	while (*s != 61)
	{
		if (*s == '\0')
			return (one_c(res, 1));
		s ++;
	}
	res = val_malloc(s, res);
	return (res);
}
