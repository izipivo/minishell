#include "minishell.h"

extern t_mshell	inf;

long long	ft_atoi_exit(const char *str)
{
	long long int	n;
	long long int	k;
	int				i;

	k = 1;
	n = 0;
	i = 0;
	while ((str[i]) && (((str[i] > 8) && (str[i] < 14)) || (str[i] == 32)))
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i++] == 45)
			k = k * (-1);
	}
	while (str[i] && !(str[i] < 48 || str[i] > 57))
	{
		n = n * 10 + str[i++] - 48;
		if (n < 0)
		{
			if (k > 0)
				return (-1);
			return (0);
		}
	}
	return (n * k);
}

int errors_exit(int signal, int res)
{
    if (signal == 0)
    {
        // ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        exit_ms("minishell: exit: too many arguments\n", 1);
    }
    if (signal == 1)
        exit_ms(NULL, res % 256);
    if (signal == 2)
    {
        // ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
        exit_ms("minishell: exit: numeric argument required\n", 2);
    }
    if (signal == 255)
        exit_ms(NULL, 255);
    if (signal == -1)
    {
        if (res < -255)
            exit_ms(NULL, 2);
        exit_ms(NULL, 255 + (res + 1));
    }
    return (0);
}

int parse_exit(char *cmd)
{
    int i;
    int plus;
    int minus;

    i = 0;
    minus = 0;
    plus = 0;
    while (cmd[i])
    {
        if (!ft_isdigit(cmd[i]) && cmd[i] != 43 && cmd[i] != 45)
            errors_exit(2, 0);
        if (cmd[i] == 43)
            plus ++;
        if (cmd[i] == 45)
            minus ++;
        i ++;
    }
    if (plus > 1 || minus > 1)
        errors_exit(2, 0);
    return (-1);
}

int	check_cmd(char *cmd)
{
	if (!(ft_strncmp(cmd, "export", 8)))
		return (1);
	else if (!(ft_strncmp(cmd, "unset", 7)))
		return (1);
	else if (!(ft_strncmp(cmd, "exit", 5)))
		return (1);
	else if (!(ft_strncmp(cmd, "env", 4)))
		return (1);
    else if (!(ft_strncmp(cmd, "cd", 3)))
		return (1);
    else if (!(ft_strncmp(cmd, "echo", 5)))
		return (1);
	else
		return (0);
}

void exit_main(void)
{
    int i;
    long long res;

    i = -1;
    res = 0;
    while (inf.pipes[0].cmd[++ i])
        ;
    printf("%s %s %d\n", inf.pipes[0].cmd[0], inf.pipes[0].cmd[1], i);
    if (i > 2)
    {
        if (check_cmd(inf.pipes[0].cmd[1]) == 1)
            errors_exit(2, res);
        errors_exit(0, res);
    }
    i = 0;
    if (check_cmd(inf.pipes[0].cmd[i + 1]))
        errors_exit(2, res);
    parse_exit(inf.pipes[0].cmd[i + 1]);
    res = ft_atoi_exit(inf.pipes[0].cmd[1]);
    if (res > 255 && res <= 2147483647)
        errors_exit(1, res);
    if (res > 2147483647)
        errors_exit(255, res);
    if (res < 1)
        errors_exit(-1, res);
    else
        exit_ms(NULL, res);
}

// если аргументов больше двух, то статус выхода = 1
// если в качестве аргумента была подана строка, то статус выхода = 255
// если в качестве аргумента было подано число и оно очень большое, то статус выхода = "число" %256