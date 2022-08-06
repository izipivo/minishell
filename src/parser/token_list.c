#include "minishell.h"

extern t_mshell	inf;

//t_pipes	*invalid_args(void)
//{
//	ft_putstr_fd("tak nel'zya\n", 2);
//	return (NULL);
//}

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

int	token_key(char line)
{
	if (line == '|')
		return (PIPE);
	else if ((line >= 9 && line <= 13) || line == 32)
		return (SPC);
	else if (line == '"')
		return (DQUOTES);
	else if (line == 39)
		return (SQUOTES);
	else if (line == '<')
		return (INFILE);
	else if (line == '>')
		return (OUTFILE);
	else
		return (COMMAND);
}

//int	make_token(t_list *token, char *line, int end, int shift, int sep)
//{
//	if ((sep == AND  && shift != 1) || (sep <= 5 && shift > 1))
//		return (1);
//	token->val = (char *)malloc(sizeof(char) * (shift + 2));
//	if (!token->val)
//		sig_hand(1);
//	ft_strlcpy(token->val, line + end - shift, sizeof(char) * (shift + 2));
//	if ((sep == OUTFILE || sep == INFILE || sep == PIPE) && shift == 1)
//		sep += 1;
//	token->key = sep;
//	return (0);
//}

//int	is_separator(char c)
//{
//	if ((c >= 9 && c <= 13) || c == ' ' || c == '&' || c == 39 || c == '"'
//		|| c == '<' || c == '>' || c == '(' || c == ')' || c == '|')
//		return (1);
//	else
//		return (0);
//}

//void	streams(t_list *token)
//{
//	if (token->next && token->next->key == SPC)
//	{
//		token->next = token->next->next;
//	}
//	if (token->next)
//	{
//		free_val(token);
//		token->val = ft_strdup(token->next->val);
//		token->next->key = SPC;
//		if (!token->val)
//			exit(1);				//	!!!
//	}
//}

//int	ft_strapp(char **s1, char *s2)
//{
//	char	*tmp;
//
//	tmp = *s1;
//	if (!tmp)
//		*s1 = ft_strdup(s2);
//	else
//		*s1 = ft_strjoin(tmp, s2);
//	if (tmp)
//	{
//		free(tmp);
//		tmp = NULL;
//	}
//	if (!*s1)
//		return (1);					//		malloc_err
//	return (0);
//}
