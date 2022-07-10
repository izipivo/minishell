#include "minishell.h"

extern t_mshell inf;

char *parse_inf_key(char *s); //del; -->minishell.h
char *parse_inf_val(char *s); //del -->minishell.h

void	add_variable(t_env	*lenv, char **av)
{
	int i;

	i = 0;
	while (lenv->next)
		lenv = lenv->next;
	while (av[++ i])
	{
		lenv->next = malloc(sizeof(t_env));
		if (!lenv->next)
			exit_ms("malloc", 1);
		lenv = lenv->next;
		lenv->key = parse_inf_key(av[i]);
		lenv->val = parse_inf_val(av[i]);
	}
	lenv->next = NULL;
}
