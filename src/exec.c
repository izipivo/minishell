#include "../includes/minishell.h"

void	print_string(char **str, int i)
{
	int j=-1;

	while (++j < i)
	{
		ft_putendl_fd(str[j], 1);
		ft_putendl_fd("---", 1);
	}
}

// void	print_sss(char ***str)
// {
// 	str++;
// 	while (str && *str)
// 	{
// 		ft_putendl_fd("new arr", 1);
// 		print_string(*str);
// 		str++;
// 	}
// 	ft_putendl_fd("gg", 1);
// }

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
			file[1] = "here_doc";
		else if (token->key == APPEND)
			file[pipes - 2] = "/hui/";
		token = token->next;
	}
}

int	count_pipes(t_list *token)
{
	int	count;

	count = 5;
	while (token)
	{
		if (token->key == PIPE)
			count++;
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

//void	make_str_com(t_list *token, int count, char ***str, int i)
//{
//	char	*arg;
//
//
//}

char	**get_one_string(t_list *token, int pipes)
{
	char	**string;
	char	*buf;
	int		i;

	//print_list(token);
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
		else if (token->key == WORD || token->key == COMMAND)
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
	if (token->key == WORD || token->key == COMMAND)
	{
		buf = ft_strjoin_withspace(buf, token->val);
		if (!buf)
			exit(1);                                //!
	}
	if (buf)
		string[++i] = buf;
	ft_putendl_fd("before pipex", 1);
	print_string(string, pipes);
	return (string);
}

void	exec(char **commands, char **envp)
{
	pid_t	child;
	int		*a=malloc(sizeof(int));

	child = fork();
	if (child == -1)
		exit(1);								//!
	if (!child)
	{
		execve("./bin/pipex", commands, envp);
	}
	else
		waitpid(child, a, 0);
}

int     main(int argc, char **argv, char **envp)
{
        char		*line;
		char		**pipex_args;
		
        //int                   i;
        t_mshell	inf;
        (void)argc;
        (void)argv;
        //execve("/bin/echo", &argv[0], envp);
        inf.env = envp;
        inf.lenv = make_env_list(envp);
        //int m=0;
        while (3)
        {
        		line = readline(PROMPT);
                inf.tokens = parse(line, inf.lenv);
                free(line);
                if (!inf.tokens)
                        continue ;
                //print_list(inf.tokens);
				pipex_args = get_one_string(inf.tokens,
					count_pipes(inf.tokens));
				exec(pipex_args, envp);





                free_tokens(inf.tokens);
        }
        free_lenv(inf.lenv);
}

