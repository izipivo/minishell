#include "../../includes/minishell.h"

t_env	*ft_update_env(t_mshell	*inf, t_env	*lenv_tmp, size_t size)
{
    int i;
    void *tmp;

    i = 0;
    free_lenv(inf->lenv);
    inf->lenv = (t_env *)malloc(sizeof(t_env) * (size + 1));
    tmp = lenv_tmp;
    while (lenv_tmp)
    {
        inf->lenv[i].key = ft_strdup(lenv_tmp->key);
        inf->lenv[i].val = ft_strdup(lenv_tmp->val);
        if (i > 0)
            inf->lenv[i - 1].next = &inf->lenv[i];
        lenv_tmp = lenv_tmp->next;
        i ++;
    }
    if (i > 0)
		inf->lenv[i - 1].next = NULL;
    lenv_tmp = tmp;
    free_lenv(lenv_tmp);
    return (inf->lenv);
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

t_env	*add_variable(t_mshell	*inf, int ac, char **av)
{
	int	num;
	void *tmp;
	t_lol	lol;
	t_env	*lenv_tmp;
	
	lol.i = 0;
	num = ac - 2;
	tmp = inf->lenv;
    lol.ac_c = ac;
	while (inf->lenv)
	{
		inf->lenv = inf->lenv->next;
		lol.i ++;
	}
	inf->lenv = tmp;
	lenv_tmp = (t_env *)malloc(sizeof(t_env) * ((lol.i + num)) + 1);
	lol.i = 0;
	while (inf->lenv)
	{
		lenv_tmp[lol.i].key = ft_strdup(inf->lenv->key);
		lenv_tmp[lol.i].val = ft_strdup(inf->lenv->val);
		if (lol.i > 0)
			lenv_tmp[lol.i - 1].next = &lenv_tmp[lol.i];
		inf->lenv = inf->lenv->next;
		lol.i ++;
	}
	lol.i --;
    lenv_tmp = add_new(lenv_tmp, &lol, num, av);
    if (lol.i > 0)
		lenv_tmp[lol.i - 1].next = NULL;
	inf->lenv = tmp;
	return (ft_update_env(inf, lenv_tmp, lol.i));
}
