#include "../../includes/minishell.h"

typedef struct s_lol
{
	char	*val;
	char	*key;
}				t_lol;

int ft_strlen_env(char *en)
{
	int i;

	i = 0;
	while (en[i])
		i ++;
	return (i);
}

void	print_exp(char **exp)
{
	int i;

	i = -1;
	while (exp[++ i])
	{
		printf("%s", "declare -x ");
		printf("%s\n", exp[i]);
	}
}

void free_exp(char **exp)
{
    int i;
    
	i = 0;
	while (exp[i])
	{
		free(exp[i]);
		i ++;
	}
	free(exp);
}

char *parse_inf_key(char *s)
{
	int i;
	char *res;

	i = 0;
	while (s[i] != '=')
		i ++;
	res = (char *)malloc(i + 1);
	res[i] = 0;
	i = 0;
	while (s[i] != '=')
	{
		res[i] = s[i];
		i ++;
	}
	// printf("%s\n", res);
	return (res);
}

char *parse_inf_val(char *s)
{
	int i;
	int j;
	char *res;

	i = 0;
	while (s[i] != '=')
		i ++;
	i ++;
	j = i;
	while (s[j])
		j ++;
	res = (char *)malloc((j - i) + 1);
	res[j - i] = 0;
	j = 0;
	while (s[j])
	{
		res[j] = s[i];
		i ++;
		j ++;
	}
	return (res);
}

void add_variable(t_mshell	*inf, int ac, char **av)
{
	int i;
	int j = 48;
	int	num;
	void *tmp;
	t_lol *lol;

	i = ac - 1;
	num = ac - 2;
	tmp = inf->lenv;
	while (inf->lenv)
	{
		inf->lenv = inf->lenv->next;
		j --;
	}
	if (ac == 2)
		return ;
	while (num > 0)
	{
		lol->key = parse_inf_key(av[i]);
		printf("%s\n", lol->key);
		inf->lenv->key = ft_strdup(lol->key);
		free(lol->key);
		lol->val = parse_inf_val(av[i]);
		inf->lenv->key = ft_strdup(lol->val);
		free(lol->val);
		num --;
		i ++;
		// inf->lenv->next = NULL;
		// inf->lenv = inf->lenv->next;
	}
	inf->lenv = tmp;
}
