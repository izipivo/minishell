/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 15:32:12 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/11 18:33:08 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	to_free;

t_pipes	*invalid_args(void)
{
	ft_putstr_fd("tak nel'zya\n", 2);
	return (NULL);
}

void	free_val(t_list *token)
{
	if (token && token->val)
	{
		free(token->val);
		token->val = NULL;
	}
}

void	print_list(t_list **tok)
{
	t_list	*tokens=*tok;
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
	ft_strlcpy(token->val, line + end - shift, sizeof(char) * (shift + 2));
	if ((sep == OUTFILE || sep == INFILE || sep == PIPE) && shift == 1)
		sep += 1;
	token->key = sep;
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
		token->next = token->next->next;
	}
	if (token->next)
	{
		free_val(token);
		token->val = ft_strdup(token->next->val);
		token->next->key = SPC;
		if (!token->val)
			exit(1);				//	!!!
	}
}

int	dollar_find(t_list *token, t_env *lenv)
{
	int	len;

	token->key = WORD;
	len = ft_strlen(token->val);
	if (!ft_strncmp(token->val, "$", len))
	{
		free_val(token);
		token->val = ft_strdup("1488");
		if (!token->val)
			exit(1);
		return (1);
	}
	while (lenv)
	{
		if (!ft_strncmp(lenv->key, token->val, len))
		{
			free_val(token);
			token->val = ft_strdup(lenv->val);
			//printf("vot on: %s\n", token->val);
			if (!token->val)
				exit(1);
			return (1);
		}
		lenv = lenv->next;
	}
	token->val[0] = 0;
	return (1);
}

int	dollar(t_list *dlr, t_env *lenv)
{
	if (!dlr->next || (dlr->next->key != DOLLAR && dlr->next->key != COMMAND))
	{
		free_val(dlr);
		dlr->val = ft_strdup("$");
		if (!dlr->val)
			exit(1);
		dlr->key = WORD;
		return (0);
	}
	dlr->val[0] = 0;
	//dlr->next = dlr->next->next;
	return (dollar_find(dlr->next, lenv));
}

void	dol_spc_str(t_list *token, t_env *lenv)
{
	t_list	*bl=token;

	while (token)
	{
		if (token->key == DOLLAR)
		{
			if (dollar(token, lenv))
				token = token->next;
		}
		else if (token->key > 2 && token->key < 7)
		{
			if (!token->next || (token->next && (token->next->key > 2
							&& token->next->key < 7)))
			{
				ft_putstr_fd("parser error near '<'\n", 2);
				free_list(bl);
				free_lenv(lenv);
				exit(1);
			}
			streams(token);
		}
		if (token)
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
	token = token->next;
	while (token && token->key != c)
	{
		if (c == DQUOTES && token->key == DOLLAR)
			dollar(token, lenv);
		//printf("dolare: %s\n", token->val);
		if (ft_strapp(&buf, token->val))
			return (1);
		free_val(token);
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

int	list_size(t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		if (list->val)
			i++;
		list = list->next;
	}
	return (i);
}

void	*free_tokens(t_list **tokens)
{
	t_list	*token;
	int		i;

	i = -1;
	token = *tokens;
	while (1)
	{
		if (token[++i].val != NULL)
			free_val(&(token[i]));
		if (token[i].next == NULL)
			break ;
	}
	free(*tokens);
	tokens = NULL;
	return (NULL);
}

int	token_cp(t_list *new, t_list *old)
{
	new->key = old->key;
	new->val = ft_strdup(old->val);
	if (!new->val)
		return (1);
	return (0);
}

int	q_args(t_list *token)
{
	int	count;

	count = 1;
	while (token->key != PIPE)
	{
		if (token->key == WORD || token->key == COMMAND)
			count++;
		token = token->next;
	}
	return (count);
}

t_pipes	*copy_pipes(t_pipes *new, t_list *old)
{
	t_list	*cp=old;
	char	*buf;
	int		i;
	int		j;

	j = -1;
	i = 0;
	if (old->key == PIPE)
	{
		ft_putendl_fd("??", 2);
		exit(1);						///!!!
	}
	while (old)
	{
		if (old->key == PIPE)
		{
			new[i].cmd[++j] = NULL;
			j = -1;
			new[i].next = &new[i + 1];
			new[++i].mask = 0;
			new[i].cmd = (char **) malloc(sizeof(char *) * q_args(old));
			if (!q_args(old) && new->cmd)
				exit(1);					//!!!!
		}
		else if (old->key > 2 && old->key < 5)
		{
			if (new[i].in)
				free(new[i].in);
			new->in = ft_strdup(old->val);
			if (!new[i].in)
				exit(1);					//!!!!
			new[i].mask |= old->key % 2;
		}
		else if (old->key > 4 && old->key < 7)
		{
			if (new[i].out)
				free(new[i].out);
			new[i].out = ft_strdup(old->val);
			if (!new[i].in)
				exit(1);					//!!!!
			new[i].mask |= (old->key % 2) << 1;
		}
		else
		{
			new[i].cmd[++j] = ft_strdup(old->val);
			if (!new[i].cmd)
				exit(1);					//!!!!
		}
		old = old->next;
	}
	if (i == -1)
	{
		free(new);
		new = NULL;
	}
	else
		new[i].next = NULL;
	free_tokens(&cp);
	return (new);
}

t_pipes	*remalloc(t_list *old)
{
	t_list	*cp;
	t_pipes	*new;
	int		size;
	int		i;

	i = -1;
	cp = old;
	size = count_pipes(old);
	//size = list_size(old);
	new = (t_pipes *) malloc(sizeof(t_pipes) * (size + 1));
	if (!new)
		exit(1);					//		!!!!
	new[0].mask = 0;
	new[0].cmd = (char **) malloc(sizeof(char *) * q_args(old));
	if (!new[0].cmd)
		exit(1);					//		!!!!
	return (copy_pipes(new, old));
}

t_pipes	*cleaning(t_list *tokens, t_env *lenv)
{
	if (concat(tokens, lenv))
	{
		ft_putstr_fd("ne zakril\n", 2);
		exit(1);
	}
	dol_spc_str(tokens, lenv);
	return (remalloc(tokens));
}

t_pipes	*parse(char *line, t_env *lenv)
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

void	free_list(t_list *list)
{
	t_list	*cp;

	cp = list;
	while (list)
	{
		if (list->val)
			free(list->val);
		list->val = NULL;
		list = list->next;
	}
	free(cp);
	cp = NULL;
}

//int	main(int argc, char **argv, char **envp)
//{
//	char		*line;
//	//int			i;
//	t_mshell	inf;
//	(void)argc;
//	(void)argv;
//	//execve("/bin/echo", &argv[0], envp);
//	inf.env = envp;
//	inf.lenv = make_env_list(envp);
//	//int m=0;
//	while (3)
//	{
//		line = readline(PROMPT);
//		inf.tokens = parse(line, inf.lenv);
//		free(line);
//		if (!inf.tokens)
//			continue ;
//		print_list(inf.tokens);
//		free_tokens(inf.tokens);
//	}
//	free_lenv(inf.lenv);
//}
