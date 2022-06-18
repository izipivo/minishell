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

#include "../includes/minishell.h"

extern t_mshell	inf;

int	join_commands(t_list *token)
{
	char	*buf;

	if (token->next && token->next->key == COMMAND && token->next->val != NULL)
	{
		buf = ft_strjoin(token->val, token->next->val);
		if (!buf)
			exit(1488);
		free(token->val);
		token->val = buf;
		token->next = token->next->next;
		if (token->next)
			token->next->prev = token;
	}
	if (token->prev && token->prev->key == COMMAND && token->prev->val != NULL)
	{
		buf = ft_strjoin(token->prev->val, token->val);
		if (!buf)
			exit(1488);
		free(token->prev->val);
		token->prev->val = buf;
		if (token->next)
			token->next->prev = token->prev;
		token->prev->next = token->next;
	}
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
		{
			ft_putstr_fd("dol\n", 1);
			dollar(token, lenv);
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
	if (!cpy->val)
		return (0);
	return (join_commands(cpy));
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
	if (token->key == PIPE)
		token = token->next;
	while (token && token->key != PIPE)
	{
		if (token->key == COMMAND)
			count++;
		token = token->next;
	}
	// printf("quant of cmds = %d\n", count);
	return (count);
}

void	cap(t_pipes *new, int i, int j)
{
	new[i].cmd[j] = NULL;
	if (i)
	{
		// printf("i\n");
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

void	copy_word(t_pipes *new, int j, char *val)
{
	new->cmd[j] = ft_strdup(val);
	if (!new->cmd[j])
	{
		ft_putendl_fd("new cmd", 2);
		exit(1);					//!!!!
	}
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
		else if (old->key == COMMAND && old->val)
			copy_word(&new[i], ++j, old->val);
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
	free_tokens(&cp);
	return (new);
}

t_pipes	*remalloc(t_list *old)
{
	t_list	*cp;
	t_pipes	*new;
	int		i;

	i = -1;
	print_list(old);
	//printf("\n\n");
	cp = old;
	inf.mask = count_pipes(old) << 16;
	//printf("2: %x - %d\n", inf.mask, inf.mask);
	// printf("2: %x - %d\n", PIPES, PIPES);
	new = (t_pipes *) malloc(sizeof(t_pipes) * (PIPES + 1));
	if (!new)
		exit(1);					//		!!!!
	ft_memset(&new[0], 0, sizeof(t_pipes));
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

	tokens = (t_list *)malloc(sizeof(t_list ) * ft_strlen(line));
	if (!tokens)
		sig_hand(1);
	i = -1;
	j = 0;
	n = -1;
	sep = token_key(line, 0);
	while (line[++i])
	{
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
			{
				tokens[n - 1].next = &tokens[n];
				tokens[n].prev = &tokens[n - 1];
			}
			j = 0;
			sep = tmp;
		}
		else
			j++;
	}
	tokens[n].next = NULL;
	tokens[0].prev = NULL;
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
