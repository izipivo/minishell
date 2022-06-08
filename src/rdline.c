#include "../includes/minishell.h"

int     main(int argc, char **argv, char **envp)
{
        inf.env = envp;
        inf.lenv = make_env_list(envp);
        while (3)
        {
        		line = readline(PROMPT);
                inf.tokens = parse(line, inf.lenv);
                free(line);
                if (!inf.tokens)
                        continue ;
                //print_list(inf.tokens);
				pipes = count_pipes(inf.tokens);
				pipex_args = get_one_string(inf.tokens, pipes);
				exec(pipex_args, envp);





                free_tokens(inf.tokens);
				free_pipex_args(pipex_args, pipes);
        }
        free_lenv(inf.lenv);
}
