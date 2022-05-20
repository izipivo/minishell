#include "../includes/minishell.h"

int     main(int argc, char **argv, char **envp)
{
        char            *line;
        //int                   i;
        t_mshell        inf;
        (void)argc;
        (void)argv;
        //execve("/bin/echo", &argv[0], envp);
        inf.env = envp;
        inf.lenv = make_env_list(envp);
        //int m=0;
        while (3)
        {
                line = readline(PROMPT);
                inf.tokens = parse(line, inf.lenv);
                free(line);
                if (!inf.tokens)
                        continue ;
                print_list(inf.tokens);
                free_tokens(inf.tokens);
        }
        free_lenv(inf.lenv);
}

