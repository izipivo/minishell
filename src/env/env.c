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

int env_main(int index)
{
	int i;

	i = -1;
	while (inf.pipes[index].cmd[++ i])
		;
	if (i != 1)
	{
		ft_putstr_fd("env: ", 2);  // ‘228’: No such file or directory"
		ft_putchar_fd('\'', 2);
		ft_putstr_fd(inf.pipes[index].cmd[1], 2);
		ft_putchar_fd('\'', 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	print_env();
    return (0);
}
