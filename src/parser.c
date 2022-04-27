/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdpwdechoexit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:37:50 by sdonny            #+#    #+#             */
/*   Updated: 2022/04/27 18:51:20 by sdonny           ###   ########.fr       */
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

void	token_key(t_list *token, char *line, int end)
{
	if (line[end] == '|')
		token->key = PIPE;
	else if (line[end] == '"')
		token->key = DQUOTES;
	else if (line[end] == 39)
		token->key = SQUOTES;
	else if (line[end] == '(')
		token->key = PARENT_O;
	else if (line[end] == ')')
		token->key = PARENT_C;
	else if (line[end] == '$')
		token->key = DOLLAR;
	else if (line[end] == '<' && line[end + 1] != '<')
		token->key = INFILE;
	else if (line[end] == '>' && line[end + 1] != '>')
		token->key = OUTFILE;
	else if (line[end] == '>' && line[end + 1] == '>')
		token->key = APPEND;
	else if (line[end] == '<' && line[end + 1] == '<')
		token->key = HEREDOC;
	else if (line[end] == '&' && line[end + 1] == '&')
		token->key = AND;
	else if (line[end] == '|' && line[end + 1] == '|')
		token->key = OR;
	else
		token->key = COMMAND;
}

int	make_token(t_list *token, char *line, int end, int shift)
{
	int	ret;

	ret = 0;
	token = (t_list *)malloc(sizeof(t_list));
	if (!token)
		return (0);
	token->val = (char *)malloc(sizeof(char) * shift);
	if (!token->val)
		return (0);
	ft_strlcpy(token->val, line + end - shift + 1, sizeof(char) * shift);
	printf("%s\n", token->val);
	if ((shift > end) || (line[end] >= 9 && line[end] <= 13) || line[end] == 32)
	{
		token->key = SPACE;
		//while ((line[++end] >= 9 && line[end] <= 13) || line[end] == 32)
		//	ret++;
		printf("%d\n", token->key);
		return (ret);
	}
	else
		token_key(token, line, end);
	printf("%d\n", token->key);
	return (ret);
}

int	is_separator(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ' || c == '&' || c == 39 || c == '"'
		|| c == '<' || c == '>' || c == '(' || c == ')' || c == '|')
		return (1);
	else
		return (0);
}

t_list	**parse(char *line)
{
	t_list	**tokens;
	int		i;
	int		j;
	int		n;

	tokens = (t_list **)malloc(sizeof(t_list *) * ft_strlen(line));
	if (!tokens)
		return (NULL);
	i = -1;
	j = 0;
	n = -1;
	while (line[++i])
	{
		if (is_separator(line[i]))
		{
			i += make_token(tokens[++n], line, i, j + 1);
			j = 0;
		}
		else
			j++;
	}
	if (j)
		make_token(tokens[++n], line, i, j + 1);
	tokens[n] = NULL;
	return (tokens);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_list	**tokens;
	int		i;
	(void)argc;
	//execve("/bin/echo", &argv[0], envp);
	while (1)
	{
		line = readline(PROMPT);
		tokens = parse(line);
		i = -1;
		while (tokens[++i])
			printf("key: %d, val: %s\n", tokens[i]->key, tokens[i]->val);
		free(tokens);
	}
}
