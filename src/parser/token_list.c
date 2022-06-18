#include "minishell.h"

extern t_mshell	inf;

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

void	print_list(t_list *tokens)
{
	while (tokens)
	{
		// ft_putstr_fd("hh\n", 1);
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
		sig_hand(1);
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

int	leng(char *s)
{
	int	i;
	int	f;

	i = -1;
	if (ft_isdigit(s[0]))
		return (1);
	// f = ft_isdigit(s[0]);
	while (s[++i])
	{
		if (s[i] == '$' || s[i] == '/' || s[i] == '=')
			return (i);
	}
	return (ft_strlen(s));
}

int	dollar_find(t_list *token, t_env *lenv)
{
	char	*buf;
	int		len;

	token->key = COMMAND;
	len = leng(token->val);		//$/=
	// printf("len: %d\n", len);
	if (!ft_strncmp(token->val, "$", 2))
	{
		free_val(token);
		token->val = ft_strdup("1488");
		if (!token->val)
			exit(1);
		return (1);
	}
	while (lenv)
	{
		// if (!ft_strncmp(lenv->key, token->val, ft_strlen(lenv->key)))
		if (!ft_strncmp(lenv->key, token->val, len))
		{
			buf = ft_strjoin(lenv->val, token->val + ft_strlen(lenv->key));
			free_val(token);
			token->val = buf;
			// printf("vot on: %s\n", token->val);
			if (!token->val)
				exit(1);
			return (1);
		}
		lenv = lenv->next;
	}
	if (ft_strlen(token->val) != len)
	{
		buf = token->val;
		token->val = ft_strdup(token->val + len);
		if (!token->val)
			exit(3432423);
		free(buf);
		// printf("token->val: %s\n", token->val);
		return (1);
	}
	token->val[0] = 0;
	if (token->prev)
	{
		// printf("dollar find: %s\n", "ff");
		token->prev->next = token->next;
	}
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
		dlr->key = COMMAND;
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
	if (!tmp)
		*s1 = ft_strdup(s2);
	else
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
