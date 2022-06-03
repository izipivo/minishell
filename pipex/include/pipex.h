/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdursley <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 00:41:10 by pdursley          #+#    #+#             */
/*   Updated: 2022/03/31 00:41:10 by pdursley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../../includes/minishell.h"
# include "../../libft/libft.h"

typedef struct s_pipex
{
	int			in;
	int			pid1;
	int			pid2;
	int			out;
	int			pip[2];
	char		**command;
	char		**cmd_av;
	char		*cmd;
	char		*path;
	char		**split_command;
	char		*result;
}				t_pipex;

char	*ft_parse_path(char **envp);
void	ft_close(t_pipex *pipex);
char	*make_cmd(t_pipex *pipex, char *av, char **command);
void	ft_clean_main(t_pipex pipex);
void	ft_clean_child(t_pipex *pipex);
void	ft_open_fd(t_pipex *pipex, char *av[], int ac);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *str1, const char *str2, size_t vol);
void	ft_child_one(t_pipex *pipex, char **av, char **envp);
void	ft_child_two(t_pipex *pipex, char **av, char **envp);
void	ft_execve(t_pipex *pipex, char **envp);
void	ft_exit(t_pipex pipex);

#endif
