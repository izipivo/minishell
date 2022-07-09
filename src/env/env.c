#include "minishell.h"

extern t_mshell inf;

void print_env(void)
{
	void *tmp;

	tmp = inf.lenv;
	while (inf.lenv)
	{
		ft_putstr_fd(inf.lenv->key, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(inf.lenv->val, 1);
		ft_putchar_fd('\n', 1);
		inf.lenv = inf.lenv->next;
	}
	inf.lenv = tmp;
}

int env_main(void)
{
    print_env();
    return (0);
}
