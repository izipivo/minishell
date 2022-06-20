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
		printf("%s", "declare -x ");
		printf("%s\n", exp[i]);
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

int	check_key(char c)
{
	if (c == '\0')
		return (0);
	if ((c >= 33 && c <= 47) || (c == 64) || (c >= 91 && c <= 96))
		return (1);
	return (-1);
}

char *parse_inf_key(char *s)
{
	int i;
	char *res;

	i = 0;
	while (s[i] != 61)
	{
		if (check_key(s[i]) == 0)
			break ;
		i ++;
	}
	res = (char *)malloc(i + 1);
	res[i] = 0;
	i = 0;
	while (s[i] != '=')
	{
		if (s[i] == '\0')
			break ;
		res[i] = s[i];
		i ++;
	}
	return (res);
}

char *parse_inf_val(char *s)
{
	int i;
	int j;
	char *res;

	i = 0;
	while (s[i] != 61)
	{
		if (s[i] == '\0')
		{
			res = malloc(sizeof(char));
			res[0] = '\0';
			return (res);
		}
		i ++;
	}
	if (s[i] == 61 && !s[i + 1])
		return (NULL);
	i ++;
	j = i;
	while (s[j])
		j ++;
	res = (char *)malloc((j - i) + 1);
	res[j - i] = 0;
	j = 0;
	while (s[i])
	{
		res[j] = s[i];
		i ++;
		j ++;
	}
	return (res);
}
