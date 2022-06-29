#include "minishell.h"

t_mshell	inf;

void	*free_pipes(t_pipes *pipes)
{
	t_pipes	*cp;
	int		i;

	cp = pipes;
	while (pipes)
	{
		i = -1;
		while (pipes->cmd[++i])
		{
			free(pipes->cmd[i]);
		}
		free(pipes->cmd);
		if (pipes->in)
			free(pipes->in);
		if (pipes->out)
			free(pipes->out);
		pipes = pipes->next;
	}
	free(cp);
	return (NULL);
}

void	print_string(char **str)
{
	int	i;

	i = -1;
	while (str[++i] && *str[i])
	{
		ft_putendl_fd(str[i], 1);
	}
}

int cnt=1;

void	print_pipes(t_pipes *pipe)
{
	int	i;

	i = -1;
	while (pipe)
	{
		ft_putstr_fd("pipe #", 1);
		ft_putnbr_fd(++i, 1);
		ft_putchar_fd('\n', 1);
		print_string(pipe->cmd);
		ft_putstr_fd("_______________________\n", 1);
		pipe = pipe->next;
	}
	cnt = 1;
}

int	count_pipes(t_list *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->key == COMMAND && token->val && !count)
			++count;
		else if (count && token->key == PIPE)
			++count;
		token = token->next;
	}
	return (count);
}

void	exec(void)
{
	pipex();
}

void	*free_pipex_args(char **ar, int pipes)
{
	int	i;

	i = 1;
	while (++i < pipes - 2)
	{
		if (ar[i])
		{
			free(ar[i]);
			ar[i] = NULL;
		}
	}
	free(ar);
	ar = NULL;
	return (NULL);
}

void	sig_hand(int sig)
{
	sig_quit(0);
	if (inf.tokens)
		inf.tokens = free_tokens(inf.tokens);
	if (inf.lenv)
		inf.lenv = free_lenv(inf.lenv);
	if (inf.pipes)
		inf.pipes = free_pipes(inf.pipes);
	ft_putendl_fd("\nbye", 1);
	exit(sig);
}

void	sig_quit(int sig)
{
	int	i;

	i = -1;
	(void)sig;
	if (inf.pid != -228)
	{
		kill(inf.pid, SIGKILL);
		inf.pid = -228;
	}
}

void	exit_ms(char *err, int status)
{
	ft_putendl_fd(err, 2);
	sig_quit(0);
	if (inf.tokens)
		inf.tokens = free_tokens(inf.tokens);
	if (inf.lenv)
		inf.lenv = free_lenv(inf.lenv);
	if (inf.pipes)
		inf.pipes = free_pipes(inf.pipes);
	if (status >= 0)
		exit(status);
	exit(1);
}
