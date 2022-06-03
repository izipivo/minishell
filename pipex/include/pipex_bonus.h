/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdursley <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 00:42:09 by pdursley          #+#    #+#             */
/*   Updated: 2022/03/31 00:42:09 by pdursley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../gnl/get_next_line.h"
# include "../../libft/libft.h"

typedef struct s_pipex
{
	int			in;
	int			all_pid;
	int			num_child;
	int			out;
	int			*pip;
	char		**command;
	char		**cmd_av;
	char		*cmd;
	char		*path;
	char		**split_command;
	char		*result;
	int			here_doc;
	int			pipe_num;
	int			number_cmd;
}				t_pipex_b;

char	*ft_parse_path(char **envp);
char	*make_cmd(t_pipex_b *pipex, char *av, char **command);
void	ft_clean_main(t_pipex_b pipex);
void	ft_clean_child(t_pipex_b *pipex);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *str1, const char *str2, size_t vol);
void	infile(t_pipex_b *pipex, char **av, int ac);
void	check_heredoc(t_pipex_b *pipex, char **av);
void	outfile(t_pipex_b *pipex, char **av, int ac);
void	ft_child(t_pipex_b *pipex, char **argv, char **envp);
void	ft_dup(int fd1, int fd2, t_pipex_b *pipex);
void	ft_close(t_pipex_b *pipex);
void	ft_close_pip(t_pipex_b *pipex);
void	ft_error(t_pipex_b *pipex);
void	ft_error_in_out(char *str);
#endif
