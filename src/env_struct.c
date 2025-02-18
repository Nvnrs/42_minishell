#include "minishell.h"

char	**split_on_first_equal(char *str)
{
	char	**split;
	int		i;
	int		equal_index;

	split = malloc(sizeof (char *) * 3);
	if (split == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	split[0] = ft_substr(str, 0, i);
	equal_index = i;
	i++;
	while (str[i])
		i++;
	split[1] = ft_substr(str, equal_index + 1, i - equal_index + 1);
	split[2] = NULL;
	return (split);
}

t_key_val	*init_env_var(char *key, char *value)
{
	t_key_val	*env_var;

	env_var = malloc(sizeof (t_key_val));
	env_var->key = ft_strdup(key);
	env_var->value = ft_strdup(value);
	return (env_var);
}

t_list	**init_list_env(char *envp[])
{
	t_list	**env;
	int		i;
	char	**split;

	i = 0;
	env = malloc(sizeof (t_list *));
	// *env = premier
	if (env == NULL)
		return (NULL);
	while (envp[i] && envp)
	{
		split = split_on_first_equal(envp[i]);
		if (i == 0)
		{
			*env = ft_lstnew(init_env_var(split[0], split[1]));
		}
		else
		{
		// if (len_split(split) == 2)
			ft_lstadd_back(env, ft_lstnew(init_env_var(split[0], split[1])));
		}
		// print_split(split);
		free_split(split);
		i++;
	}

	return (env);
}

void	free_env_var(void *env_var_void)
{
	t_key_val *env_var;

	env_var = env_var_void;
	free(env_var->key);
	free(env_var->value);
	free(env_var);
}

void	free_list_env(t_list **env)
{
	ft_lstclear(env, free_env_var);
	free(env);
	env = NULL;
}

void	print_env_var(t_key_val *env_var)
{
	printf("%s=%s\n", env_var->key, env_var->value);
}

void	print_list_env(t_list **env)
{
	t_list	*lst;

	lst = *env;
	while (lst)
	{
		print_env_var(lst->content);
		lst = lst->next;
	}
}