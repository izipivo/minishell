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

int	token_key(char *line, int end)
{
	if (line[end] == '|')
		return (PIPE);
	else if ((line[end] >= 9 && line[end] <= 13) || line[end] == 32)
		return (SPACE);
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
	else if (line[end] && line[end] == '<' && line[end + 1] != '<')
		return (INFILE);
	else if (line[end] && line[end] == '>' && line[end + 1] != '>')
		return (OUTFILE);
	else if (line[end] && line[end] == '>' && line[end + 1] == '>')
		return (APPEND);
	else if (line[end] && line[end] == '<' && line[end + 1] == '<')
		return (HEREDOC);
	else if (line[end] && line[end] == '&' && line[end + 1] == '&')
		return (AND);
	else if (line[end] && line[end] == '|' && line[end + 1] == '|')
		return (OR);
	else
		return (COMMAND);
}

void	make_token(t_list *token, char *line, int end, int shift, int sep)
{
	token->val = (char *)malloc(sizeof(char) * (shift + 2));
	if (!token->val)
		exit(1);
	ft_strlcpy(token->val, line + end - shift, sizeof(char) * (shift + 2));
	//printf("val: %s\n", token->val);
	token->key = sep;
	//printf("key: %d\n", token->key);
}

int	is_separator(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ' || c == '&' || c == 39 || c == '"'
		|| c == '<' || c == '>' || c == '(' || c == ')' || c == '|')
		return (1);
	else
		return (0);
}

t_list	*parse(char *line)
{
	t_list	*tokens;
	int		i;
	int		sep;
	int		j;
	int		n;

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
			make_token(&tokens[++n], line, i, j, sep);
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
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_list	*tokens;
	int		i;
	(void)argc;
	//execve("/bin/echo", &argv[0], envp);
	while (1)
	{
		line = readline(PROMPT);
		tokens = parse(line);
		i = -1;
		while (tokens[++i].next != NULL)
			printf("key: %d, val: %s\n", tokens[i].key, tokens[i].val);
		printf("key: %d, val: %s\n", tokens[i].key, tokens[i].val);
		free(tokens);
	}
}
