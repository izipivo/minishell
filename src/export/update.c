#include "minishell.h"

extern t_mshell inf;

char *parse_inf_key(char *s); //del; -->minishell.h
char *parse_inf_val(char *s); //del -->minishell.h

// t_env	*new_lenv(t_env	*lenv)
// {
// 	void *tmp;
// 	t_env *new_lenv;
// 	int i;

// 	i = 0;
// 	tmp = lenv;
// 	while (lenv)
// 	{
// 		lenv = lenv->next;
// 		i ++;
// 	}
// 	lenv = tmp;
// 	new_lenv = (t_env *)malloc(sizeof(t_env) * (i + 1));
// 	if (!new_lenv)
// 		exit_ms("malloc", 1);
// 	i = 0;
// 	while (lenv)
// 	{
// 		new_lenv[i].key = lenv->key;
// 		new_lenv[i].val = lenv->val;
// 		lenv = lenv->next;
// 		i ++;
// 	}
// 	lenv = tmp;
// 	if (i > 0)
// 		new_lenv[i - 1].next = NULL;
// 	free_lenv(lenv);
// 	return (new_lenv);

// }

void	add_variable(t_env	*lenv, char **av)
{
	int i;

	i = 1;
	while (lenv->next)
		lenv = lenv->next;
	while (av[i])
	{
		lenv->next = malloc(sizeof(t_env));
		lenv->next->key = parse_inf_key(av[i]);
		lenv->next->val = parse_inf_val(av[i]);
		++ i;
		lenv = lenv->next;
	}
	lenv->next = NULL;
	// return (new_lenv(lenv));
}
