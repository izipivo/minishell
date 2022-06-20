#include "minishell.h"

extern t_mshell inf;

void print_env(void)
{
    void *tmp;

    tmp = inf.lenv;
    while (inf.lenv)
	{
		printf("%s=", inf.lenv->key);
		printf("%s\n", inf.lenv->val);
		inf.lenv = inf.lenv->next;
	}
    inf.lenv = tmp;
}

void env_main(void)
{
    print_env();
    return ;
}
