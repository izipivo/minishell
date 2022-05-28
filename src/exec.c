#include "../includes/minishell.h"

void	print_string(char **str)
{
	while (*str)
	{
		ft_putendl_fd(*str, 1);
		str++;
		ft_putendl_fd("---", 1);
	}
}

void	print_sss(char ***str)
{
	str++;
	while (str && *str)
	{
		ft_putendl_fd("new arr", 1);
		print_string(*str);
		str++;
	}
	ft_putendl_fd("gg", 1);
}

void	find_redir(t_list *token, char ****files)
{
	char	**file;

	file = (char **)malloc(sizeof(char *) * 2);
	if (!file)
		exit(1);								//!
	file[0] = NULL;
	file[1] = NULL;
	while (token)
	{
		if (token->key == INFILE)
			file[0] = token->val;
		else if (token->key == OUTFILE)
			file[1] = token->val;
		token = token->next;
	}
	**files = file;
}

int	count_pipes(t_list *token)
{
	int	count;

	count = 4;
	while (token)
	{
		if (token->key == PIPE)
			count++;
		token = token->next;
	}
	return (count);
}

//static char	*ft_strjoin_withspace(char const *s1, char const	*s2)
//{
//	char	*joined;
//	int		i;
//
//	i = -1;
//	joined = (char *) malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
//	if (!joined)
//		return (0);
//	while (s1 && *s1)
//		joined[++i] = *s1++;
//	if (i != -1)
//		joined[++i] = ' ';
//	while (s2 && *s2)
//		joined[++i] = *s2++;
//	joined[++i] = '\0';
//	return (joined);
//}

void	make_ar_str(t_list *token, int count, char ***str, int i)
{
	char	**arr;

	arr = (char **)malloc(sizeof(char *) * (++count + 3));
	if (!arr)
		exit(1);									//!
	//ft_putendl_fd(str[0][0], 1);
	arr[count + 2] = NULL;
	//ft_putendl_fd(str[0][1], 1);
	if (!str[0][1])
		arr[1 + count] = "/";
	else
		arr[1 + count] = str[0][1];
	while (count > 1)
	{
		while (token->key != COMMAND && token->key != WORD)
			token--;
		arr[count] = token->val;
		if (count-- - 1 >= 0)
			token--;
	}
	if (!str[0][0])
		arr[1] = "/";
	else
		arr[1] = str[0][0];
	arr[0] = "pipex";
	str[i] = arr;
}

char	***get_one_string(t_list *token, int pipes)
{
	char	***string;
	int		count;
	int		i;

	//print_list(token);
	i = 0;
	count = 0;
	string = (char ***)malloc(sizeof(char **) * pipes);
	if (!string)
		exit(1);									//!
	find_redir(token, &string);
	while (token->next)
	{
		if (token->key == PIPE)
		{
			make_ar_str(token, count, string, i);
			print_string(string[i]);
			count = 0;
		}
		else if (token->key == WORD || token->key == COMMAND)
		{
			count++;
		}
		token = token->next;
	}
	if (token->key == PIPE)
		ft_putendl_fd("wtf?", 1);
	make_ar_str(token, ++count, string, i);
	string[++i] = NULL;
	//print_sss(string);
	return (string);
}

void	exec(char ***commands, char **envp)
{
	pid_t	child;
	int		i;

	child = fork();
	if (child == -1)
		exit(1);								//!
	i = 0;
	if (!child)
	{
		execve("./bin/pipex", commands[++i], envp);
	}
}

int     main(int argc, char **argv, char **envp)
{
        char		*line;
		char		***pipex_args;
		
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

