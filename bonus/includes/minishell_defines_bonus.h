/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_defines.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:59:08 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/11 15:20:12 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEFINES_BONUS_H
# define MINISHELL_DEFINES_BONUS_H

/*
//		token's keys
*/
//# define AND 0 			//	&&
# define PIPE 1			//	|
//# define OR 2			//	||
# define INFILE 3		//	<
# define HEREDOC 4		//	<<
# define OUTFILE 5		//	>
# define APPEND 6 		//	>>
# define DQUOTES 7		//	"
# define SQUOTES 8		//	'
# define SPC 9			//	_
# define COMMAND 10		//	...
//# define PARENT_O 11	//	(
//# define PARENT_C 12	//	)
//# define DOLLAR 13		//	$

//# define INPUT(x) (x & 1)
//# define DLR(x) (x & 1)
//# define QUOTS(x) ((x >> 1) & 1)
//# define DIGIT(x) ((x >> 2) & 1)
//# define UPDATELENV(x) ((x >> 4) & 1)
//# define FILES_NOT_FOUND (void *)0
# define PIPE_OK 1
# define PIPE_KO 0
# define EXIT_ERROR 1
# define RETURN_PROMPT -228

/*
//		readline colours
*/
# define CYELLOW "\001\e[0;31m\002"
# define YELLOW "\001\033[1;33m\002"
# define LYELLOW "\e[38;5;227m"
# define READLINE_BLUE "\001\033[1;94m\002"
# define RESET   "\001\e[0m\002"
# define RED "\001\033[1;91m\002"
# define GREEN "\e[00;32m"
# define SINIY "\e[00;34m"
# define PURPLE "\e[00;35m"
# define BRIGHT_BLUE "\e[01;34m"
# define ORANGE "\e[38;5;202m"
//# define PERROR YELLOW"mini"RED"error"RESET
# define PERROR "minierror"
# define PROMPT "minipchel$> "
// # define RL_PROMT_START_IGNORE '\001'
// # define RL_PROMT_END_IGNORE '\002'

#endif
