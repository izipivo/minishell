#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct s_lol
{
	char	*res;
	char	*key;
}				t_lol;

int ft_strlen_env(char *en)
{
	int i;

	i = 0;
	while (en[i] != '=')
    {
        i ++;
    }
	return (i);
}

int ft_strlen_env_res(char *str, int start)
{
	int i;

	i = start;
	while (str[i])
		i ++;
	return (i);
}

char *ft_diff(char *str, char **envp, t_lol *msh)
{
	int i;
	int k;
	int len;
	char *result;
	int j;

	len = 0;
	i = 0;
	j = 0;
	k = 0;
	while (str[i] != '=')
		i ++;
	msh->key = malloc(i + 1);
	msh->key[i] = '\0';
	i ++;
	while (str[k] != '=')
	{
		msh->key[k] = str[k];
		k ++;
	}
	len = ft_strlen_env_res(str, i);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	while (str[i])
	{
		result[j] = str[i];
		i ++;
		j ++;
	}
	return (result);
}

void	ft_replacement(t_lol *msh, t_mshell *mshell)
{
	int i;
	int j;
	char *flag;
	void *tmp;

	i = -1;
	j = -1;
	tmp = mshell->lenv;
	while (mshell->lenv)
	{
		if (!ft_strncmp(mshell->lenv->key, msh->key , ft_strlen_env(mshell->lenv->key)))
		{
			while (msh->res[++ i])
				;
			free(mshell->lenv->val);
			mshell->lenv->val = ft_strdup(msh->res);
			break ;
		}
		mshell->lenv = mshell->lenv->next;
	}
	mshell->lenv = tmp;
}

int main(int argc, char *argv[], char *envp[])
{
	int i;
	char **exp;
	int j;
	(void)argc;
	(void)argv;
	t_lol		msh;
	t_mshell	inf;

	i = 0;
	j = 1;
	inf.lenv = make_env_list(envp, 0);
	while (envp[i])
	{
		if ((ft_strncmp(envp[i], argv[j] , ft_strlen_env(envp[i]))) == 0)
		{
			msh.res = ft_diff(argv[j], envp, &msh);
			ft_replacement(&msh, &inf);
			break ;
		}	
		i ++;
	}
	while (inf.lenv)
	{
		printf("%s=", inf.lenv->key);
		printf("%s\n", inf.lenv->val);
		inf.lenv = inf.lenv->next;

	}
	free_lenv(inf.lenv);
	return (0);
}

//gcc exp_c.c ../../includes/minishell.h ../../libft/ft_strjoin.c ../../libft/ft_strlen.c ../../libft/ft_strchr.c ../../libft/ft_strdup.c ../env_list.c ../../libft/ft_strncmp.c