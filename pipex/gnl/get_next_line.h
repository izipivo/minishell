/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdursley <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:41:23 by pdursley          #+#    #+#             */
/*   Updated: 2021/11/14 14:41:25 by pdursley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "../include/pipex_bonus.h"

# define BUFFER_SIZE 100

typedef struct s_line
{
	int		fd;
	int		kol_b;
	char	*string;
}				t_line;

char	*get_next_line(int fd, char **line);
char	*ft_strchr(const char *str, int ch);
char	*ft_strdup(const char *str);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_read_from_file(int fd, char *str_file, char *buf, t_line *res);
char	*ft_ost_from_line(char *str_file);
char	*ft_copy_line(char *str_file);

#endif
