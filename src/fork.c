/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:59:08 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/11 15:20:12 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

extern t_mshell inf;

static char	**cmdparse(char *old, char **envp)
{
	char	**new;
	char	*tmp;

	new = ft_split(old, ' ');
	tmp = new[0];
	new[0] = checkpath(tmp, envp);
	free(tmp);
	tmp = NULL;
	return (new);
}

static void	killchild(char **cmd)
{
	cleansplit(cmd);
	close(0);
	close(1);
	exit(EXIT_SUCCESS);
}

static pid_t	*createpids(int **fd)
{
	pid_t	*pid;

	printf("%d pipes\n", PIPES);
	pid = (pid_t *)malloc(sizeof(pid_t) * PIPES);
	if (!pid)
		exitmalloc(fd);
	return (pid);
}

pid_t	*forks(int **fd)
{
	int		m;
	pid_t	*pid;
	char	**cmd;
	int		quantity;
	t_list	*token;

	m = -1;
	token = *(inf.tokens);
	quantity = PIPES;
	pid = createpids(fd);
	while (token) {
		if (token->key != WORD && token->key != COMMAND)
		{
			token = token->next;
			continue;
		}
		pid[m] = fork();
		if (pid[m] < 0)
			exitpid(fd, pid, "fork");
		if (!pid[m])
		{
			close_fd(quantity + 1, m, fd);
			cmd = cmdparse(inf.tokens[m]->val, inf.env);
			if (!cmd[0])
				exitcmd(fd, pid);
			if (execve(cmd[0], cmd, inf.env) == -1)
				exitpid(fd, pid, cmd[0]);
			killchild(cmd);
		}
		token = token->next;
	}
	return (pid);
}
