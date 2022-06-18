#include "minishell.h"

void print_env(char **env)
{
    t_mshell	inf;
    void *tmp;

    inf.lenv = make_env_list(env);
    tmp = inf.lenv;
    while (inf.lenv)
	{
		printf("%s=", inf.lenv->key);
		printf("%s\n", inf.lenv->val);
		inf.lenv = inf.lenv->next;
	}
    inf.lenv = tmp;
    free_lenv(inf.lenv);
}

int main(int argc, char *argv[], char *envp[])
{
    (void)argc;
	(void)argv;

    print_env(envp);
    return (0);
}

//gcc env.c ../../includes/minishell.h ../../libft/ft_strjoin.c ../../libft/ft_strlen.c ../../libft/ft_strchr.c ../../libft/ft_strdup.c ../env_list.c ../../libft/ft_strncmp.c