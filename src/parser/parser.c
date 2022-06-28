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
	// char	*cc;
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
				// cc = buf;
				strapp(&buf, cpy->val, 1);
				// ft_putendl_fd(buf, 1);
				// if (buf == 0);
				// {
				// 	ft_putstr_fd("while\n", 1);
				// 	exit(100);					
				// }
				// free(cc);
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

// int	first_occ(t_list *token, char c)
// {
// 	t_list	*cpy;
// 	char	*buf;

// 	buf = NULL;
// 	cpy = token;
// 	token = token->next;
// 	while (token && token->key != c)
// 	{
// 		if (c == DQUOTES && token->key == DOLLAR)
// 		{
// 			// ft_putstr_fd("dol\n", 1);
// 			dollar(token);
// 		}
// 		if (ft_strapp(&buf, token->val))
// 			return (1);
// 		free_val(token);
// 		token = token->next;
// 	}
// 	if (!token)			//		not closed " or '
// 	{
// 		if (buf)
// 			free(buf);
// 		return (1);
// 	}
// 	cpy->key = COMMAND;
// 	free_val(cpy);
// 	cpy->val = buf;
// 	cpy->next = token->next;
// 	free_val(token);
// 	return (0);
// }

// int	concat()
// {
// 	t_list	*token;

// 	token = inf.tokens;
// 	while (token)
// 	{
// 		if (token->key == SQUOTES || token->key == DQUOTES)
// 		{
// 			if (first_occ(token, token->key))
// 				return (1);
// 		}
// 		token = token->next;
// 	}
// 	return (0);
// }

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

t_pipes	*del(t_pipes *new)
{
	int	i;

	i = -1;
	while (new[++i].next)
	{
		if (!new[i].cmd[0])
		{
			if (i)
				new[i - 1].next = new[i].next;
		}
	}
	return (new);
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
	return (del(new));
}

t_pipes	*remalloc(void)
{
	// t_list	*cp;
	t_list	*old;
	t_pipes	*new;
	// int		i;

	// i = -1;
	old = inf.tokens;
	// print_list(old);
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

void	strapp(char **s1, char *s2, int f)
{
	char	*str;

	str = *s1;
	if (!str && !s2)
		return ;
	if (!str)
	{
		*s1 = ft_strdup(s2);
	}
	else if (s2)
	{
		*s1 = ft_strjoin(str, s2);
		if (f)
		{
			free(str);
			str = NULL;
		}
	}
	if (f == 2)
	{
		free(s2);
		s2 = NULL;
	}
	if (!(*s1))
		exit_ms("malloc", 1);
}

char	*find_env(char *find)
{
	t_env	*lenv;
	char	*found;

	lenv = inf.lenv;
	// printf("find_env: %s\n", find);
	if (!*find)
		return (NULL);
	while (lenv)
	{
		if (!ft_strncmp(lenv->key, find, ft_strlen(find)))
		{
			found = ft_strdup(lenv->val);
			if (!found)
				exit_ms(NULL, 1);
			return (found);
		}		
		lenv = lenv->next;
	}
	return (NULL);
}

int	get_last_char_of_dlr(char *str, t_list *token)
{
	int	i;

	i = -1;
	if (token->key != DQUOTES)
		return (ft_strlen(str));
	while (str[++i] && str[i] != '\'' && str[i] != '=' && str[i] != '/' &&str[i] != ' ')
		;
	// printf("glcod: %d\n", i);
	return (i);
}

void	check_dlr(t_list *token)
{
	char	*buf;
	char	*remainig;
	int		i;
	int		last_char;
	
	i = -1;
	remainig = NULL;
	buf = ft_strdup(token->val);
	if (!buf)
		exit_ms("malloc rip!", 1);
	// printf("1:check_dlr: %s\n", token->val);
	while(token->val[++i] && token->val[i] != '$')
		;
	buf[i] = 0;
	while (token->val[i] && token->val[i] == '$')
	{
		if (!token->val[i + 1])
		{
			strapp(&buf, "$", 1);
		}
		else if (token->val[i + 1] == '$')
		{
			strapp(&buf, "1488", 1);
			++i;
		}
		else if (token->val[i + 1] == '?')
		{
			strapp(&buf, "228", 1);
			++i;
		}
		++i;
	}
	// printf("check_dlr: %s\n", &token->val[i]);
	last_char = get_last_char_of_dlr(&token->val[i], token);
	if (last_char + i <= (int)ft_strlen(token->val))
	{
		remainig = ft_strdup(&token->val[i + last_char]);
		// printf("check_dlr: %s lc %d, i %d\n", remainig, last_char, i);
		if (!remainig)
			exit_ms("malloc rip", 1);
	}
	token->val[i + last_char] = 0;
	strapp(&buf, find_env(&token->val[i]), 2);
	if (remainig)
		strapp(&buf, remainig, 2);
	free(token->val);
	token->val = buf;
	// printf("2:check_dlr: %s\n", token->val);
}

void	check_redirs(void)
{
	t_list	*token;

	token = inf.tokens;
	while(token)
	{
		if (DLR(inf.mask) && (token->key == DQUOTES || token->key == DOLLAR))
			check_dlr(token);
		if (token->key == OUTFILE && ft_strlen(token->val) == 2)
			token->key = APPEND;
		else if (token->key == INFILE && ft_strlen(token->val) == 2)
			token->key = HEREDOC;
		if ((token->key == OUTFILE || token->key == INFILE) && ft_strlen(token->val) > 2)
			exit_ms("parser error near '>'", 1);
		else if (token->key == DOLLAR || token->key == SQUOTES || token->key == DQUOTES)
			token->key = COMMAND;
		token = token->next;
	}
}

void	remove_quotes(t_list *token)
{
	char	*buf;

	while (token)
	{
		if (token->key == SQUOTES || token->key == DQUOTES)
		{
			if (ft_strlen(token->val) == 2)
			{
				free(token->val);
				token->val = NULL;
				// printf("lol\n");
				if (token->prev)
					token->prev->next = token->next;
				token = token->next;
				continue ;
			}
			buf = token->val;
			token->val[ft_strlen(token->val) - 1] = 0;
			token->val = ft_strdup(token->val + 1);
			free(buf);
		}
		token = token->next;
	}
}

t_pipes	*cleaning(void)
{
	// print_list(inf.tokens);
	// ft_putstr_fd("_______________________\n",1);
	if (QUOTS(inf.mask))
	{
		remove_quotes(inf.tokens);
		// print_list(inf.tokens);
		// ft_putstr_fd("_______________________\n",1);
	}
	check_redirs();
	// print_list(inf.tokens);
	// ft_putstr_fd("_______________________\n",1);
	join_commands(inf.tokens);
	// print_list(inf.tokens);
	// ft_putstr_fd("_______________________\n",1);
	return (remalloc());
}

// int	same_token(char old, char new)
// {
// 	char	key;
// 
// 	key = token_key(new);
	// if (key == DQUOTES || key == SQUOTES)
	// {
	// 	inf.mask |= 1 << 1;
	// 	// printf("dqots: %d\n", inf.mask);
	// }
	// if (key == DOLLAR && old != SQUOTES)
	// {
	// 	inf.mask |= 1;
	// 	// printf("mask: %d %c\n", inf.mask, new);
	// }
	// if (new == '$' && old != SQUOTES)
	// 	return (0);
	// if (old == DOLLAR && ft_isdigit(new))
	// {
	// 	if (!DIGIT(inf.mask))
	// 	{
	// 		inf.mask |= 1 << 2;
	// 		// printf("fff\n");
	// 		return (1);
	// 	}
	// 	else
	// 		return (0);
	// }
	// if (old == DOLLAR)
		
	// if (old == DOLLAR && key != DOLLAR)
	// 	inf.mask |= 1 << 2;
	// if ((old == DQUOTES || old == SQUOTES) && old == key)
	// {
	// 	return (-1);
	// }
	// if (old == DOLLAR && (ft_isalnum(new) || new == '_'))
	// {
	// 	inf.mask |= 1 << 2;
	// 	// printf("old: %c\n", new);
	// 	return (1);
	// }
	// if (old == key || old == DQUOTES || old == SQUOTES)
	// 	return (1);
	// return (0);
// }

int	same_token(char old, char new)
{
	char	key;

	key = token_key(new);
	// if (new == '$' && old != SQUOTES)
	// 	return (0);
	if (key == SQUOTES || key == DQUOTES)
		inf.mask |= 1 << 1;
	if (key == DOLLAR && old != SQUOTES)
		inf.mask |= 1;
	if ((old == DQUOTES || old == SQUOTES) && old == key)
		return (-1);
	if (old != key && (old == SQUOTES || old == DQUOTES))
		return (1);
	if (old == DOLLAR && ft_isdigit(new))
	{
		if (!DIGIT(inf.mask))
		{
			inf.mask |= 1 << 2;
			// printf("fff\n");
			return (1);
		}
		else
		{
			inf.mask &= ~(1 << 2);
			return (0);
		}
	}
	if (old == DOLLAR && (ft_isalnum(new) || new == '_'))
	{
		// inf.mask |= 1 << 2;
		// printf("old: %c\n", new);
		return (1);
	}
	if (old == key)
		return (1);
	return (0);
}

int	tok_quant(char *line)
{
	char	key;
	int		count;
	int		i;

	count = 19;
	i = 0 ;
	key = 64;
	while (line[++i])
	{
		if (same_token(key, line[i]) == 1)
			continue ;
		else if (same_token(key, line[i]) == -1)
		{
			key = 88;
			continue ;
		}
		++count;
		key = token_key(line[i]);
	}
	// printf("tok_quant: %d\n", count);
	return (count);
}

void	make_new_token(int *token_index, int *val_index, char key)
{
	*val_index = 0;
	++(*token_index);
	inf.tokens[*token_index].key = key;
	inf.tokens[*token_index].val = (char *)malloc(sizeof(char) * 1000);					//			!!!!
	if (!inf.tokens[*token_index].val)
		exit_ms("malloc", 1);
}

int	fill_token(int old, char new, int *token_index, int *val_index)
{
	int	key;
	int		st;

	key = token_key(new);
	st = same_token(old, new);
	if (st == 1)
	{
		++(*val_index);
		return (*token_index);
	}
	if (st == -1)
	{
		inf.tokens[*token_index].val[*val_index + 1] = new;
		inf.tokens[*token_index].val[*val_index + 2] = 0;
		// printf("fill_token st==-1: %c, %s\n", new, inf.tokens[*token_index].val);
		*val_index = -1;
		return (*token_index);
	}
	if (old != 88 && old != 64)
		inf.tokens[*token_index].val[*val_index + 1] = 0;
	// if (old != 88 && old != 64)
		// printf("fill_token: %d\n", inf.tokens[*token_index].key);
	// printf("ti: %d\n", *token_index);
	if (old != 64)
	{
		inf.tokens[*token_index].next = &inf.tokens[*token_index + 1];
		inf.tokens[*token_index + 1].prev = &inf.tokens[*token_index];
	}
	make_new_token(token_index, val_index, key);
	return (*token_index);
}

t_pipes	*parse(char *line)
{
	int		j;
	int		i;
	int		n;
	char	key;

	i = -1;
	n = -1;
	inf.tokens = (t_list *)malloc(sizeof(t_list ) * tok_quant(line));
	if (!inf.tokens)
		exit_ms("malloc error", 1);
	key = 64;
	// if (!inf.tokens[0].val)
	// 	exit_ms("malloc", 1);
	while (line[++i])
	{
		if (line[i] == line[i + 1] && (line[i] == '\'' || line[i] == '"'))
		{
			++i;
			continue ;
		}
		fill_token(key, line[i], &n, &j);
		if (j == -1)
		{
			key = 88;
			continue ;
		}
		if (!same_token(key, line[i]))
			key = token_key(line[i]);
		// printf("key: %d, n: %d, c:  %c\n", key, n, line[i]);
		inf.tokens[n].val[j] = line[i];
	}
	if (j != -1)
		inf.tokens[n].val[++j] = 0;
	// printf("%d %s\n", inf.tokens[n].key, inf.tokens[n].val);
	inf.tokens[n].next = NULL;
	inf.tokens[0].prev = NULL;
	if ((inf.tokens[n].key == SQUOTES || inf.tokens[n].key == DQUOTES) && j != -1)
		exit_ms("not closed quote", 1);
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
