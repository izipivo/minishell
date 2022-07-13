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
		// ft_putstr_fd(pipes[0].cmd[0], 1);
		while (pipes->cmd[++i])
		{
			// printf("free_pipes: %s\n", pipes->cmd[i]);
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
	int i=-1;

	while (str[++i] && *str[i])
	{
		ft_putendl_fd(str[i], 1);
	}
}

int cnt=1;

void	print_pipes(t_pipes *pipe)
{
	int	i = -1;
	while (pipe)
	{
		ft_putstr_fd("pipe #", 1);
		ft_putnbr_fd(++i, 1);
		ft_putchar_fd('\n', 1);
		print_string(pipe->cmd);
		printf("input: %s\noutput: %s\n", pipe->in, pipe->out);
		ft_putstr_fd("_______________________\n", 1);
		pipe = pipe->next;
	}
	cnt = 1;
}

char	*change_filename(char **str, char *prefix)
{
	char	*buf;

	buf = ft_strjoin(prefix, *str);
	if (!buf)
		exit(1);																//!!!
	free(*str);
	*str = buf;
	return (*str);
}

void	find_redir(t_list *token, char ***files, int pipes)
{
	char	**file;

	file = *files;
	file[0] = "pipex";
	file[1] = "/";
	// ft_putendl_fd("hui", 1);
	file[pipes - 2] = "/";
	file[pipes - 1] = NULL;
	while (token)
	{
		if (token->key == INFILE)
			file[1] = token->val;
		else if (token->key == OUTFILE)
			file[pipes - 2] = token->val;
		else if (token->key == HEREDOC)
			file[1] = change_filename(&token->val, "//");
		else if (token->key == APPEND)
			file[pipes - 2] = change_filename(&token->val, "\\/");				//!!!
		token = token->next;
	}
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

static char	*ft_strjoin_withspace(char *s1, char const	*s2)
{
	char	*joined;
	int		i;
	int		j;

	i = -1;
	j = 0;
	joined = (char *) malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!joined)
		return (0);
	while (s1 && s1[j])
		joined[++i] = s1[j++];
	if (i != -1)
		joined[++i] = ' ';
	while (s2 && *s2)
		joined[++i] = *s2++;
	joined[++i] = '\0';
	if (j != 0)
		free(s1);
	return (joined);
}

char	**get_one_string(t_list *token, int pipes)
{
	char	**string;
	char	*buf;
	int		i;

	i = 1;
	buf = NULL;
	string = (char **)malloc(sizeof(char *) * pipes);
	if (!string)
		exit(1);									//!
	find_redir(token, &string, pipes);
	while (token->next)
	{
		if (token->key == PIPE)
		{
			string[++i] = buf;
			buf = NULL;
		}
		else if (token->key == COMMAND)
		{
			buf = ft_strjoin_withspace(buf, token->val);
			//ft_putendl_fd(buf, 1);
			if (!buf)
				exit(1);							//!
		}
		token = token->next;
	}
	if (token->key == PIPE)
		ft_putendl_fd("wtf?", 1);
	if (token->key == COMMAND)
	{
		buf = ft_strjoin_withspace(buf, token->val);
		if (!buf)
			exit(1);                                //!
	}
	if (buf)
		string[++i] = buf;
	return (string);
}

void	exec(void)
{
	//pid_t	child;
	//int		*a=malloc(sizeof(int));

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
	// (void)sig;
	if (inf.pids)
	{
		while (++i < PIPES)
		{
			if (inf.pids[i])
			{
				if (sig == SIGINT)
					kill(inf.pids[i], SIGKILL);
				else
					kill(inf.pids[i], SIGQUIT);
				inf.pids[i] = 0;
			}
		}
	}
	else if (sig == SIGQUIT)
	{
		rl_redisplay();
		// ft_putstr_fd(PROMPT, 1);
		return ;
	}
	inf.code = 128 + sig;
	if (sig == SIGQUIT)
		ft_putstr_fd("\nQuit\n"PROMPT, 1);
	else
		ft_putstr_fd("\n"PROMPT, 1);
}

void	exit_ms(char *err, int status)
{
	ft_putendl_fd(err, 2);
	sig_quit(0);
	if (inf.line)
		free(inf.line);
	if (inf.tokens)
		inf.tokens = free_tokens(inf.tokens);
	if (inf.lenv)
		inf.lenv = free_lenv(inf.lenv);
	if (inf.pipes)
		inf.pipes = free_pipes(inf.pipes);
	if (status >= 0)
		exit(status);
	rl_clear_history();
	exit(1);
}
