/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 15:32:12 by sdonny            #+#    #+#             */
/*   Updated: 2022/05/01 20:03:20 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*invalid_args(void)
{
	ft_putstr_fd("tak nel'zya\n", 2);
	return (NULL);
}

//void	print_list(t_list *tokens)
//{
//	while (token)
//	{
//		printf("key: %s, val: %s\n", tokens->key, tokens->val);
//		tokens = tokens->next;
//	}
//}

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
	//if (sep == SPC)
	//{
	//	token->val[0] = ' ';
	//	token->val[1] = '\0';
	//}
	//else
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

char	*ft_getenv(t_env *lenv, char *key)
{
	int		len;
	char	*tmp;

	len = ft_strlen(key);
	if (*key == 32 || (*key >=9 && *key <= 13))
	{
		free(key);
		tmp = ft_strdup("$");
		if (!tmp)
			exit(1);			//	!!!
		return (tmp);
	}
	while (lenv)
	{
		if (!ft_strncmp(lenv->key, key, len))
		{
			free(key);
			tmp = ft_strdup(lenv->val);
			if (!tmp)
				exit(1);			//	!!!
			return (tmp);
		}
		lenv = lenv->next;
	}
	return (NULL);
}

void	streams(t_list *token)
{
	if (token->next->key == SPC)
	{
		free(token->next->val);
		token->next = token->next->next;
	}
	if (token->val)
		free(token->val);
	token->val = ft_strdup(token->next->val);
	if (!token->val)
		exit(1);				//	!!!
	token->next = token->next->next;
}

void	dollar(t_list *token, t_env *lenv)
{
	while (token)
	{
		if (token->key == DOLLAR)
		{
			if (token->val)
				free(token->val);
			token->val = ft_getenv(lenv, token->next->val);
			token->next = token->next->next;
			token->key = COMMAND;
		}
		else if (token->key == SPC)
		{
			free(token->val);
			token->val = " ";
		}
		else if (token->key >= 3 && token->key <= 6)
			streams(token);
		token = token->next;
	}
}

char	*change_next(t_list *token, t_env *lenv)
{
	free(token->val);
	token->next->val = ft_getenv(lenv, token->next->val);
	return (NULL);
}

int	first_occ(t_list *token, char c, t_env *lenv)
{
	t_list	*cpy;
	char	*tmp;
	char	*buf;

	buf = NULL;
	cpy = token;
	free(token->val);
	token = token->next;
	while (token && token->key != c)
	{
		if (c == DQUOTES && token->key == DOLLAR)
			token->val = change_next(token, lenv);
		tmp = buf;
		buf = ft_strjoin(tmp, token->val);
		if (tmp)
			free(tmp);
		free(token->val);
		token = token->next;
	}
	if (!token)
		return (1);
	cpy->key = COMMAND;
	cpy->val = buf;
	cpy->next = token->next;
	free(token->val);
	return (0);
}
int	concat(t_list *token, char c, t_env *lenv)
{
	while (token)
	{
		if (token->key == SQUOTES)
		{
			if (first_occ(token, SQUOTES, lenv))
				return (1);
		}
		else if (token->key == DQUOTES)
		{
			if (first_occ(token, DQUOTES, lenv))
				return (1);
		}
		token = token->next;
	}
	return (0);
}

t_list	*cleaning(t_list *tokens, t_env *lenv)
{
	if (concat(tokens, SQUOTES, lenv))
	{
		ft_putstr_fd("ne zakril\n", 2);
		exit(1);
	}
	if (concat(tokens, DQUOTES, lenv))
	{
		ft_putstr_fd("ne zakril\n", 2);
		exit(1);
	}
	dollar(tokens, lenv);
	return (tokens);
}

t_list	*parse(char *line, t_env *lenv)
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
	return (cleaning(tokens, lenv));
}

void	free_tokens(t_list *token)
{
	t_list	*bl;

	bl = token;
	while (token)
	{
		free(token->val);
		token->next = NULL;
		token->val = NULL;
		token = token->next;
	}
	free(bl);
	bl = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	int			i;
	t_mshell	inf;
	(void)argc;
	//execve("/bin/echo", &argv[0], envp);
	inf.env = envp;
	inf.lenv = make_env_list(envp);
	while (1)
	{
		line = readline(PROMPT);
		inf.tokens = parse(line, inf.lenv);
		free(line);
		if (!inf.tokens)
			continue ;
		i = -1;
		t_list	*tmp=inf.tokens;
		while (tmp)
		{
			printf("key: %d, val:%s_\n", tmp->key, tmp->val);
			tmp = tmp->next;
		}
		free_tokens(inf.tokens);
	}
	free_lenv(inf.lenv);
}
