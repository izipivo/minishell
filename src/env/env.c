#include "minishell.h"

extern t_mshell inf;

void print_env(void)
{
	int	i;

	i = 0;
    while (inf.env_cpy[i])
	{
		ft_putstr_fd(inf.env_cpy[i], 1);
		ft_putchar_fd('\n', 1);
		i ++;
	}
}

int env_main(void)
{
    print_env();
    return (0);
}
