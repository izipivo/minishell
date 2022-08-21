#include "minishell.h"

extern t_mshell g_inf;

void print_env(void)
{
	void *tmp;

	tmp = g_inf.lenv;
	while (g_inf.lenv)
	{
		ft_putstr_fd(g_inf.lenv->key, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(g_inf.lenv->val, 1);
		ft_putchar_fd('\n', 1);
		g_inf.lenv = g_inf.lenv->next;
	}
	g_inf.lenv = tmp;
}

int env_main(int index)
{
	int i;

	i = -1;
	while (g_inf.pipes[index].cmd[++ i])
		;
	if (i != 1)
	{
		ft_putstr_fd("env: ", 2);  // ‘228’: No such file or directory"
		ft_putchar_fd('\'', 2);
		ft_putstr_fd(g_inf.pipes[index].cmd[1], 2);
		ft_putchar_fd('\'', 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	print_env();
    return (0);
}
