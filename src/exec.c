#include "../includes/minishell.h"

//static int	rmandopen(char *filename)
//{
//	if (access(filename, F_OK) == 0)
//	{
//		if (unlink(filename) == -1)
//			return (-1);
//	}
//	return (open(filename, O_WRONLY | O_CREAT, 0664));
//}
//
//static void	check_outfile(char *outfile)
//{
//	if (access(outfile, F_OK) != 0)
//		return ;
//	if (access(outfile, W_OK) != 0)
//	{
//		perror(PERROR);
//		exit(EXIT_FAILURE);
//	}
//}

static int	check_file(char *file, int flag)
{
	if (!file)
		return (0);
	if (access(file, F_OK) != 0)
	{
		perror(PERROR);
		exit(EXIT_FAILURE);
	}
	if (flag && access(file, W_OK) != 0)
	{
		perror(PERROR);
		exit(EXIT_FAILURE);
	}
	if (!flag && access(file, R_OK) != 0)
	{
		perror(PERROR);
		exit(EXIT_FAILURE);
	}
	return (1);
}

char	**find_redir(t_list *token, char ***files)
{
	char	**file;

	file = *files;
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
	return (file);
}

void	change_fd(t_list *token)
{
	char	**files;
	int		fd;
	int		i;

	i = -1;
	files = find_redir(token, &files);
	while (++i < 2)
	{
		if (check_file(files[i], i) == 0)
			continue ;
		if (!i)
			fd = open(files[i], O_RDONLY);
		else
			fd = open(files[i], O_WRONLY);
		if (fd == -1)
		{
			perror(PERROR);
			exit(-1);
		}
		dup2(fd, i);
		close(fd);
	}
}

int     main(int argc, char **argv, char **envp)
{
        char            *line;
        //int                   i;
        t_mshell        inf;
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
                print_list(inf.tokens);
				change_fd(inf.tokens);





                free_tokens(inf.tokens);
        }
        free_lenv(inf.lenv);
}
