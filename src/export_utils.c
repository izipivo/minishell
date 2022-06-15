#include "../includes/minishell.h"

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

char *parse_inf_key(char *s)
{
	int i;
	char *res;

	i = 0;
	while (s[i] != 61)
		i ++;
	res = (char *)malloc(i + 1);
	res[i] = 0;
	i = 0;
	while (s[i] != '=')
	{
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
		i ++;
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
