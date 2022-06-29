#include "minishell.h"

int	ft_strlen_env(char *en)
{
	int	i;

	i = 0;
	while (en[i])
		i ++;
	return (i);
}

void	print_exp(char **exp)
{
	int	i;

	i = -1;
	while (exp[++ i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(exp[i], 1);
		ft_putstr_fd("\n", 1);
	}
}

void	free_exp(char **exp)
{
	int	i;

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
	if ((c >= 33 && c <= 45) || (c >= 46 && c <= 47) || (c == 64) || \
		(c == 91) || (c >= 93 && c <= 94) || (c == 96))
		return (1);
	return (-1);
}
