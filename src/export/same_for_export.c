#include "minishell.h"

extern t_mshell inf;

char  **new_key(char **cmd)
{
    int i;
    char **str;

    i = 0;
    while (cmd[i])
        i ++;
    str = (char **)malloc(sizeof(char *) * (i + 1));
    str[i] = 0;
    i = 0;
    while (cmd[i])
    {
        str[i] = ft_strdup(cmd[i]);
        i ++;
    }
    i = 0;
    while (str[i])
    {
        printf("%s\n", str[i]);
        i ++;
    }
    return (str);
}

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
            if (!(ft_strncmp(inf.lenv->key, inf.pipes[0].cmd[i], ft_strlen(inf.lenv->key))))
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
