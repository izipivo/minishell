#include "minishell.h"

extern t_mshell inf;

int same_key(void)
{
    int i;
    void *tmp;

    tmp = inf.lenv;
    while (inf.lenv)
    {
        i = 1;
        while (inf.pipes[0].cmd[i])
        {
            if (!(ft_strncmp(inf.pipes[0].cmd[i], inf.lenv->key, ft_strlen(inf.lenv->key))))
            {
                inf.lenv = tmp;
                return (-1);
            }
            else
                i ++;
        }
        inf.lenv = inf.lenv->next;
    }
    inf.lenv = tmp;
    return (1);
}
