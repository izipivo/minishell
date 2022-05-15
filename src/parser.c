/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 15:32:12 by sdonny            #+#    #+#             */
/*   Updated: 2022/05/15 15:54:13 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	to_free;

t_list	*invalid_args(void)
{
	ft_putstr_fd("tak nel'zya\n", 2);
	return (NULL);
}

void	free_val(t_list *token)
{
	//free(token->val);
	if (token && token->val)
	{
		free(token->val);
		token->val = NULL;
	}
}

void	print_list(t_list *tokens)
{
	while (tokens)
	{
		printf("key: %d, val: %s\n", tokens->key, tokens->val);
		tokens = tokens->next;
	}
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

void	streams(t_list *token)
{
	if (token->next && token->next->key == SPC)
	{
		//free_val(token->next);
		token->next = token->next->next;
	}
	if (token->next)
	{
		free_val(token);
		token->val = ft_strdup(token->next->val);
		//free_val(token->next);
		if (!token->val)
			exit(1);				//	!!!
		token->next = token->next->next;
	}
}

void	dollar_find(t_list *token, t_env *lenv)
{
	int	len;

	len = ft_strlen(token->val);
	if (!ft_strncmp(token->val, "$", len))
	{
		//free_val(token);
		token->val = ft_strdup("1488");
		if (!token->val)
			exit(1);
		return ;
	}
	while (lenv)
	{
		if (!ft_strncmp(lenv->key, token->val, len))
		{
			//free_val(token);
			token->val = ft_strdup(lenv->val);
			//printf("vot on: %s\n", token->val);
			if (!token->val)
				exit(1);
			return ;
		}
		lenv = lenv->next;
	}
}

void	dollar(t_list *dlr, t_env *lenv)
{
	//free_val(dlr);
	dlr->key = WORD;
	free_val(dlr);
	if (!dlr->next || dlr->next->key == SPC)
	{
		dlr->val = ft_strdup("$");
		if (!dlr->val)
			exit(1);
		if (dlr->next)
			dlr->next = dlr->next->next;
		ft_putstr_fd("opa\n", 1);
		return ;
	}
	dlr->val = dlr->next->val;
	dlr->next = dlr->next->next;
	dollar_find(dlr, lenv);
}

void	dol_spc_str(t_list *token, t_env *lenv)
{
	while (token)
	{
		if (token->key == DOLLAR)
			dollar(token, lenv);
		else if (token->key == SPC)
		{
			free_val(token);
			//token->val = ft_strdup(" ");
			//if (!token->val)
			//	exit(1);				//		!!!
		}
		else if (token->key > 2 && token->key < 7)
		{
			if (token->next && (token->next->key > 2 && token->next->key < 7))
			{
				ft_putstr_fd("parser error near '<'\n", 2);
				exit(1);
			}
			streams(token);
		}
		token = token->next;
	}
}

int	ft_strapp(char **s1, char *s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = ft_strjoin(tmp, s2);
	if (tmp)
	{
		free(tmp);
		tmp = NULL;
	}
	if (!*s1)
		return (1);					//		malloc_err
	return (0);
}

int	first_occ(t_list *token, char c, t_env *lenv)
{
	t_list	*cpy;
	char	*buf;

	buf = NULL;
	cpy = token;
	//print_list(token);
	//free_val(token);
	token = token->next;
	while (token && token->key != c)
	{
		if (c == DQUOTES && token->key == DOLLAR)
			dollar(token, lenv);
		//printf("dolare: %s\n", token->val);
		if (ft_strapp(&buf, token->val))
			return (1);
		//free_val(token);
		token = token->next;
		//printf("buf: %s\n", buf);
	}
	if (!token)			//		not closed " or '
	{
		if (buf)
			free(buf);
		return (1);
	}
	cpy->key = WORD;
	free_val(cpy);
	cpy->val = buf;
	//printf("cpy: %s\n", cpy->val);
	cpy->next = token->next;
	free_val(token);
	return (0);
}

int	concat(t_list *token, t_env *lenv)
{
	while (token)
	{
		if (token->key == SQUOTES || token->key == DQUOTES)
		{
			if (first_occ(token, token->key, lenv))
				return (1);
		}
		token = token->next;
	}
	return (0);
}

t_list	*cleaning(t_list *tokens, t_env *lenv)
{
	if (concat(tokens, lenv))
	{
		ft_putstr_fd("ne zakril\n", 2);
		exit(1);
	}
	dol_spc_str(tokens, lenv);
	return (tokens);
}

t_list	*parse(char *line, t_env *lenv)
{
	t_list	*tokens;
	int		i;
	int		sep;
	int		tmp;
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
		if (line[i + 1])
			tmp = token_key(line, i + 1);
		if (!line[i + 1] || sep != tmp || tmp == SQUOTES || tmp == DQUOTES
				|| tmp == DOLLAR)
		{
			if (make_token(&tokens[++n], line, i, j, sep))
			{
				free(tokens);						//		!!!!!!!
				return (invalid_args());
			}
			if (n > 0)
				tokens[n - 1].next = &tokens[n];
			j = 0;
			sep = tmp;
			//printf("dkdkdkdkd %d\n", sep);
		}
		else
			j++;
	}
	tokens[n].next = NULL;
	to_free = n;
	//print_list(tokens);
	return (cleaning(tokens, lenv));
}

void	free_tokens(t_list *token)
{
	int	i;
	int	n;

	i = -1;
	n = to_free;
	while (n >= 0)
	{
		free_val(&token[n]);
		token[n--].next = NULL;
	}
	//free_val(&token[i]);
	//token->next = NULL;
	if (token)
		free(token);
	token = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	//int			i;
	t_mshell	inf;
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
		//i = -1;
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
