/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:41:23 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/06 17:17:55 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_valid_key(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]) || str[i] == '_')
	{
		i++;
		while (str[i] && str[i] != '=')
		{
			if (!ft_isalnum(str[i]) && str[i] != '_')
				return (FALSE);
			i++;
		}
		return (TRUE);
	}
	return (FALSE);
}

t_key_val	*create_new_var(char *str)
{
	int			i;
	t_key_val	*var;

	i = 0;
	var = malloc(sizeof(t_key_val));
	if ((ft_isalpha(str[i]) || str[i] == '_'))
		while (str[i] && str[i] != '=')
			i++;
	if (str[i] == '\0' || str[i] != '=')
	{
		free(var);
		return (NULL);
	}
	var->key = ft_substr(str, 0, i);
	i++;
	var->value = ft_substr(str, i, (ft_strlen(str) - 1));
	return (var);
}

void	save_new_var(t_key_val *new_var, t_list **env)
{
	t_list		*lst;
	t_key_val	*content_env;

	lst = *env;
	while (lst)
	{
		content_env = lst->content;
		if (ft_strcmp(content_env->key, new_var->key) == 0)
		{
			free_key_val(lst->content);
			lst->content = new_var;
			return ;
		}
		lst = lst->next;
	}
	ft_lstadd_back(env, ft_lstnew(new_var));
}

void	builtin_export(char **args, t_list **env)
{
	int			i;
	t_key_val	*var;

	i = 0;
	exit_status(0, TRUE);
	if (args == NULL)
		return ;
	while (args[i])
	{
		if (!is_valid_key(args[i]))
		{
			force_print_stderr("export: '");
			force_print_stderr(args[i]);
			force_print_stderr("': not a valid identifier\n");
			exit_status(1, TRUE);
		}
		else
		{
			var = create_new_var(args[i]);
			if (var)
				save_new_var(var, env);
		}
		i++;
	}
}
