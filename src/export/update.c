#include "minishell.h"

extern t_mshell inf;

typedef struct s_lol
{
	int		ac_c;
	int		i;
	char	*key;
	char	*val;
}				t_lol;

char *parse_inf_key(char *s); //del; -->minishell.h
char *parse_inf_val(char *s); //del -->minishell.h

int ft_len_list(t_env *list)
{
    void *tmp;
    int i;

    i = 0;
    tmp = list;
    while (list)
    {
        i ++;
        list = list->next;
    }
    list = tmp;
    return (i);
}

t_env	*ft_update_env(t_env *lenv, t_env	*lenv_tmp, size_t size)
{
    int i;
    // void *tmp;

    i = 0;
    free_lenv(lenv);
    lenv = (t_env *)malloc(sizeof(t_env) * (size));
	if (!lenv)
		exit_ms("error malloc", -1);
    while (lenv_tmp)
    {
        lenv[i].key = ft_strdup(lenv_tmp->key);
        lenv[i].val = ft_strdup(lenv_tmp->val);
        if (i > 0)
            lenv[i - 1].next = &lenv[i];
        lenv_tmp = lenv_tmp->next;
        i ++;
    }
    if (i > 0)
		lenv[i - 1].next = NULL;
    return (lenv);
}

t_env	*add_new(t_env *lenv_tmp, t_lol *lol, int num, char **av)
{
    while (num > 0)
	{
		lol->key = parse_inf_key(av[lol->ac_c - 1]);
		lenv_tmp[lol->i].key = ft_strdup(lol->key);
		free(lol->key);
		lol->val = parse_inf_val(av[lol->ac_c - 1]);
		lenv_tmp[lol->i].val = ft_strdup(lol->val);
		free(lol->val);
		if (lol->i > 0)
			lenv_tmp[lol->i - 1].next = &lenv_tmp[lol->i];
		num --;
		lol->ac_c --;
		lol->i ++;
	}
    return (lenv_tmp);
}

t_env	*add_variable(t_env	*lenv, int ac, char **av)
{
	int	num;
	void *tmp;
	t_lol	lol;
	t_env	*lenv_tmp;
	
	num = ac - 1;
	tmp = lenv;
    lol.ac_c = ac;
	lol.i = ft_len_list(lenv);
	lenv_tmp = (t_env *)malloc(sizeof(t_env) * ((lol.i + num)));
	if (!lenv_tmp)
		exit_ms("error malloc", -1);
	lol.i = 0;
	while (lenv)
	{
		lenv_tmp[lol.i].key = ft_strdup(lenv->key);
		lenv_tmp[lol.i].val = ft_strdup(lenv->val);
		if (lol.i > 0)
			lenv_tmp[lol.i - 1].next = &lenv_tmp[lol.i];
		lenv = lenv->next;
		lol.i ++;
	}
    lenv_tmp = add_new(lenv_tmp, &lol, num, av);
    if (lol.i > 0)
		lenv_tmp[lol.i - 1].next = NULL;
	lenv = tmp;
	tmp = lenv_tmp;
	lenv = ft_update_env(lenv, lenv_tmp, lol.i);
	inf.mask |= 1 << 4;
	lenv_tmp = tmp;
	free_lenv(lenv_tmp);
	return (lenv);
}
