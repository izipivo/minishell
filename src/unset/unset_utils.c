#include "../../includes/minishell.h"

void    ft_strdup_env(t_env *lenv, t_env *lenv_tmp, int j)
{
    lenv_tmp[j].key = ft_strdup(lenv->key);
	lenv_tmp[j].val = ft_strdup(lenv->val);
	if (j > 0)
	    lenv_tmp[j - 1].next = &lenv_tmp[j];
}

t_env	*delete_env(t_env *lenv, t_env *lenv_tmp, int num, char **del)
{
    int i;
    int j;
    void *tmp;

    j = 0;
    tmp = lenv;
    while (lenv)
    {
        i = 2;                                              //изменить потом, не учитывая ./a.out
        while (del[i])
        {
            if (ft_strncmp(lenv->key, del[i], ft_strlen(del[i])))
                i ++;
            else
                break ;
            if (i == num)
            {
                ft_strdup_env(lenv, lenv_tmp, j);
		        j ++;
            }
        }
        lenv = lenv->next;
    }
    if (j > 0)
		lenv_tmp[j - 1].next = NULL;
    lenv = tmp;
    return (lenv_tmp);
}
