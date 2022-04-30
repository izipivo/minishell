/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdpwdechoexit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:37:50 by sdonny            #+#    #+#             */
/*   Updated: 2022/04/30 19:59:47 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_npchararraylen(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		;
	return (i);
}

t_list	*invalid_args(void)
{
	ft_putstr_fd("tak nel'zya\n", 2);
	return (NULL);
}

int	token_key(char *line, int end)
{
	if (line[end] == '|')
		return (PIPE);
	else if ((line[end] >= 9 && line[end] <= 13) || line[end] == 32)
		return (SPC);
	else if (line[end] == '"')
		return (DQUOTES);
	else if (line[end] == 39)
		return (SQUOTES);
	else if (line[end] == '(')
		return (PARENT_O);
	else if (line[end] == ')')
		return (PARENT_C);
	else if (line[end] == '$')
		return (DOLLAR);
	else if (line[end] == '<')
		return (INFILE);
	else if (line[end] == '>')
		return (OUTFILE);
	else if (line[end] == '&')
		return (AND);
	else if (line[end] == '|')
		return (OR);
	//else if (line[end] && line[end] == '<' && line[end + 1] != '<')
	//	return (INFILE);
	//else if (line[end] && line[end] == '>' && line[end + 1] != '>')
	//	return (OUTFILE);
	//else if (line[end] && line[end] == '>' && line[end + 1] == '>')
	//	return (APPEND);
	//else if (line[end] && line[end] == '<' && line[end + 1] == '<')
	//	return (HEREDOC);
	//else if (line[end] && line[end] == '&' && line[end + 1] == '&')
	//	return (AND);
	//else if (line[end] && line[end] == '|' && line[end + 1] == '|')
	//	return (OR);
	else
		return (COMMAND);
}

int	make_token(t_list *token, char *line, int end, int shift, int sep)
{
	if ((sep == AND  && shift != 1) || (sep <= 5 && shift > 1))
		return (1);
	token->val = (char *)malloc(sizeof(char) * (shift + 2));
	if (!token->val)
		exit(1);
	if (sep == SPC)
	{
		token->val[0] = ' ';
		token->val[1] = '\0';
	}
	else
		ft_strlcpy(token->val, line + end - shift, sizeof(char) * (shift + 2));
	//printf("val: %s\n", token->val);
	if ((sep == OUTFILE || sep == INFILE || sep == PIPE) && shift == 1)
		sep += 1;
	token->key = sep;
	//printf("key: %d\n", token->key);
	return (0);
}

int	is_separator(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ' || c == '&' || c == 39 || c == '"'
		|| c == '<' || c == '>' || c == '(' || c == ')' || c == '|')
		return (1);
	else
		return (0);
}

//t_list	*cleaning(t_list *tokens, *env)


t_list	*parse(char *line, char **envp)
{
	t_list	*tokens;
	int		i;
	int		sep;
	int		j;
	int		n;

	if (!line || !line[0])
		return (NULL);
	tokens = (t_list *)malloc(sizeof(t_list ) * ft_strlen(line));
	if (!tokens)
		exit(1);
	i = -1;
	j = 0;
	n = -1;
	sep = token_key(line, 0);
	while (line[++i])
	{
		//printf("sep: %d, tk: %d\n", sep, token_key(line, i+1));
		if (!line[i + 1] || sep != token_key(line, i + 1))
		{
			if (make_token(&tokens[++n], line, i, j, sep))
			{
				free(tokens);
				return (invalid_args());
			}
			if (n > 0)
				tokens[n - 1].next = &tokens[n];
			j = 0;
			if (line[i + 1])
			sep = token_key(line, i + 1);
			//printf("dkdkdkdkd %d\n", sep);
		}
		else
			j++;
	}
	tokens[n].next = NULL;
	return (tokens);
	//return (cleaning(tokens, envp));
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	int			i;
	t_mshell	inf;
	(void)argc;
	//execve("/bin/echo", &argv[0], envp);
	inf.env = envp;
	while (1)
	{
		line = readline(PROMPT);
		inf.tokens = parse(line, inf.env);
		free(line);
		if (!inf.tokens)
			continue ;
		i = -1;
		while (inf.tokens && inf.tokens[++i].next != NULL)
			printf("key: %d, val:%s_\n", inf.tokens[i].key, inf.tokens[i].val);
		printf("key: %d, val:%s_\n", inf.tokens[i].key, inf.tokens[i].val);
		free(inf.tokens);
	}
}
