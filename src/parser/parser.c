/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 15:32:12 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/12 15:14:55 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_mshell	inf;

int	join_commands(t_list *token)
{
	char	*buf;
	char	*cc;
	t_list	*cpy;
	int		f;
	
	f = 0;
	while(token)
	{
		if (token->key == COMMAND)
		{
			buf = token->val;
			cpy = token->next;
			while (cpy && cpy->key == COMMAND)
			{
				cc = buf;
				buf = ft_strjoin(buf, cpy->val);
				// ft_putendl_fd(buf, 1);
				// if (buf == 0);
				// {
				// 	ft_putstr_fd("while\n", 1);
				// 	exit(100);					
				// }
				free(cc);
				cpy = cpy->next;
				f = 1;
			}
			if (f)
			{
				token->val = buf;
				token->next = cpy;
				f = 0;
			}
		}
		token = token->next;
	}
	return (0);
}

int	first_occ(t_list *token, char c)
{
	t_list	*cpy;
	char	*buf;

	buf = NULL;
	cpy = token;
	token = token->next;
	while (token && token->key != c)
	{
		if (c == DQUOTES && token->key == DOLLAR)
		{
			// ft_putstr_fd("dol\n", 1);
			dollar(token);
		}
		if (ft_strapp(&buf, token->val))
			return (1);
		free_val(token);
		token = token->next;
	}
	if (!token)			//		not closed " or '
	{
		if (buf)
			free(buf);
		return (1);
	}
	cpy->key = COMMAND;
	free_val(cpy);
	cpy->val = buf;
	cpy->next = token->next;
	free_val(token);
	return (0);
}

int	concat()
{
	t_list	*token;

	token = inf.tokens;
	while (token)
	{
		if (token->key == SQUOTES || token->key == DQUOTES)
		{
			if (first_occ(token, token->key))
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

void	*free_tokens(t_list *token)
{
	t_list	*cpy;
	int		i;

	i = -1;
	cpy = token;
	while (1)
	{
		if (token[++i].val != NULL)
			free_val(&(token[i]));
		if (token[i].next == NULL)
			break ;
	}
	free(cpy);
	cpy = NULL;
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
	if (token->key == PIPE)
		token = token->next;
	while (token && token->key != PIPE)
	{
		if (token->key == COMMAND)
			count++;
		token = token->next;
	}
	return (count);
}

void	cap(t_pipes *new, int i, int j)
{
	new[i].cmd[j] = NULL;
	if (i)
	{
		new[i - 1].next = &new[i];
	}
}

void	copy_out(t_pipes *new, char *val, char key)
{
	if (new->out)
		free(new->out);
	new->out = ft_strdup(val);
	if (!new->out)
		exit(111);					//!!!!
	new->mask |= key % 2 << 1;
}

void	copy_in(t_pipes *new, char *val, char key)
{
	if (new->in)
		free(new->in);
	new->in = ft_strdup(val);
	if (!new->in)
		exit(111);					//!!!!
	new->mask |= key % 2;
}

int	copy_word(t_pipes *new, int j, t_list *old)
{
	if (!old->val)// && old->prev && old->prev->key == SPC && old->prev->prev && old->prev->prev->prev)
		new->cmd[++j] = ft_strdup(" ");
	else if (old->val)
		new->cmd[++j] = ft_strdup(old->val);
	else
		return (0);
	if (!new->cmd[j])
	{
		ft_putendl_fd("new cmd", 2);
		exit(1);					//!!!!
	}
	return (1);
}

t_pipes	*copy_pipes(t_pipes *new, t_list *old)
{
	t_list	*cp=old;
	// char	*buf;
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
			cap(new, i, ++j);
			ft_memset(&new[++i], 0, sizeof(t_pipes));
			new[i].cmd = (char **) malloc(sizeof(char *) * q_args(old));
			if (!q_args(old) && new->cmd)
			{
				ft_putendl_fd("q_args", 2);
				exit(1);					//!!!!
			}
			j = -1;
		}
		else if (old->key > 2 && old->key < 5)
			copy_in(&new[i], old->val, old->key);
		else if (old->key > 4 && old->key < 7)
			copy_out(&new[i], old->val, old->key);
		else if (old->key == COMMAND)
			j += copy_word(&new[i], j, old);
		old = old->next;
	}
	cap(new, i, ++j);
	if (i == -1)
	{
		free(new);
		new = NULL;
	}
	else
		new[i].next = NULL;
	inf.tokens = free_tokens(cp);
	return (new);
}

t_pipes	*remalloc(void)
{
	// t_list	*cp;
	t_list	*old;
	t_pipes	*new;
	// int		i;

	// i = -1;
	old = inf.tokens;
	print_list(old);
	// cp = old;
	inf.mask = count_pipes(old) << 16;
	new = (t_pipes *) malloc(sizeof(t_pipes) * (PIPES + 1));
	if (!new)
		exit(1);					//		!!!!
	ft_memset(&new[0], 0, sizeof(t_pipes));
	new[0].cmd = (char **) malloc(sizeof(char *) * q_args(old));
	if (!new[0].cmd)
		exit(1);					//		!!!!
	return (copy_pipes(new, old));
}

void	check_redirs(void)
{
	t_list	*token;

	token = inf.tokens;
	while(token)
	{
		if (token->key == OUTFILE && ft_strlen(token->val) == 2)
			token->key = APPEND;
		else if (token->key == INFILE && ft_strlen(token->val) == 2)
			token->key = HEREDOC;
		if ((token->key == OUTFILE || token->key == INFILE) && ft_strlen(token->val) > 2)
			exit_ms("parser error near '>'");
		token = token->next;
	}
}

t_pipes	*cleaning(void)
{
	check_redirs();
	if (concat())
	{
		ft_putstr_fd("ne zakril\n", 2);
		exit(1);
	}
	dol_spc_str();
	join_commands(inf.tokens);
	return (remalloc());
}

int	tok_quant(char *line)
{
	char	key;
	int		count;
	int		i;

	count = 2;
	i = -1;
	key = token_key(line[0]);
	while (line[++i])
	{
		if (key == token_key(line[i]))
			continue ;
		++count;
		key = token_key(line[i]);
	}
	printf("tok_quant: %d\n", count);
	return (count);
}

int	same_token(char old, char new)
{
	char	key;

	key = token_key(new);
	if (old == key)
		return (1);
	if (old == DOLLAR && key == COMMAND && new != '=' && new != '/')
		return (1);
	return (0);
}

int	fill_token(char old, char new, int *token_index, int *val_index)
{
	char	key;

	key = token_key(new);
	if (same_token(old, new))
	{
		++(*val_index);
		return (*token_index);
	}
	inf.tokens[*token_index].val[*val_index + 1] = 0;									//			null-terminated
	inf.tokens[*token_index].next = &inf.tokens[*token_index + 1];
	++(*token_index);
	inf.tokens[*token_index].prev = &inf.tokens[*token_index - 1];
	inf.tokens[*token_index].val = (char *)malloc(sizeof(char) * 1000);					//			!!!!
	if (!inf.tokens[*token_index].val)
		exit_ms("malloc");
	inf.tokens[*token_index].key = key;
	*val_index = 0;
	return (*token_index);
}

t_pipes	*parse(char *line)
{
	int		j;
	int		i;
	int		n;
	char	key;

	i = -1;
	j = -1;
	n = 0;
	inf.tokens = (t_list *)malloc(sizeof(t_list ) * tok_quant(line));
	if (!inf.tokens)
		exit_ms("malloc error");
	key = token_key(line[0]);
	inf.tokens[0].val = (char *)malloc(sizeof(char) * 100);					//			!!!!
	inf.tokens[0].key = key;
	if (!inf.tokens[0].val)
		exit_ms("malloc");
	while (line[++i])
	{
		inf.tokens[fill_token(key, line[i], &n, &j)].val[j] = line[i];
		key = token_key(line[i]);
	}
	inf.tokens[n].val[++j] = 0;
	inf.tokens[n].next = NULL;
	inf.tokens[0].prev = NULL;
	return (cleaning());
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
