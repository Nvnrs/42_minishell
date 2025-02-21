/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:53:47 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/21 15:19:06 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char *find_value_in_env(char *key, t_list **lst_env)
{
	t_list	*lst;
	t_key_val *content;

	lst = *lst_env;

	while (lst)
	{
		content = lst->content;
		if (ft_strncmp(key, content->key, ft_strlen(key)) == 0)
		{
			return (content->value);
		}
		lst = lst->next;
	}
	
	return (NULL);
}
int	len_key_in_str(char *str)
{
	int	i;
	int len_key;

	i = 0;
	len_key = 0;
	if (str[i] == '$')
		i++;
	while (str[i]
		&& ft_isalnum(str[i])
		|| str[i] == '_')
	{
		len_key++;
		i++;
	}
	return (len_key);
}

char	*get_key_in_str(char *str)
{
	int	i;
	int i_key;
	char *key;

	i = 0;
	i_key = 0;
	key = malloc(len_key_in_str(str) + 1 * sizeof(char));
	if (str[i] == '$')
		i++;
	while (str[i] 
		&& (ft_isalnum(str[i])
		|| str[i] == '_'))
	{
		key[i_key] = str[i];
		i_key++;
		i++;
	}
	key[i_key] = '\0';
	return (key);
}

int	expansion(char *str, char *out, int *i_out, t_list **lst_env)
{
	char	*value;
	char	*key;
	int		len_key;
	int		i;

	i = 0;
	key = get_key_in_str(str);
	len_key = ft_strlen(key);
	value = find_value_in_env(key, lst_env);
	if (value == NULL)
	{
		free(key);
		return len_key;
	}
	printf("%s\n", value);
	printf("%s\n", key);
	printf("%d\n", len_key);
	while (value[i])
	{
		out[*i_out] = value[i];
		i++;
		*i_out += 1;
	}
	free(key);
	return (len_key);
}


t_bool	is_start_of_env_var(char *str, int i)
{
	if (str[i] == '$'
		&&  str[i + 1]
		&& ft_isalpha(str[i + 1]) || str[i + 1] == '_')
		return (TRUE);
	return (FALSE);
}

char	*expansion_var(char *str, t_list **lst_env)
{
	// printf("before %s\n", str);
	int		i;
	int		i_out;
	char	*output;

	i = 0;
	i_out = 0;
	output = malloc(1000);
	output[0] = '\0';
	while (str[i])
	{
		if (str[i] == SINGLE_QUOTE)
		{
			output[i_out++] = str[i++];
			while (str[i] != SINGLE_QUOTE)
				output[i_out++] = str[i++];
		}
		else if (str[i] == DOUBLE_QUOTE)
		{
			output[i_out++] = str[i++];
			while (str[i] != DOUBLE_QUOTE)
			{
				if (is_start_of_env_var(str, i))
				{
					i++;
					i+= expansion(&str[i], output, &i_out, lst_env);
					continue;
				}	
				output[i_out++] = str[i++];
			}
		}
		if (is_start_of_env_var(str, i))
		{
			i++;
			i+= expansion(&str[i], output, &i_out, lst_env);
			continue;
		}
		output[i_out++] = str[i++];
	}
	output[i_out] = '\0';
	printf("\nafter : %s\n", output);
	return (output);
}


// void	expansion_var(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		i++;
// 	}
	
// }



void	test(char *str, t_list **env, char *expected)
{
	char			*output;
	static int		i = 1;

	output = expansion_var(str, env);
	// printf("expected : %s\n", expected);
	printf("Test %d | ", i);
	if (ft_strcmp(output, expected) == 0)
	{
		printf("\033[0;32mOK");
	}
	else
		printf("\033[0;31mKO");
	printf("\033[0;37m\n");
	i++;
}

int	main()
{
	t_list	*lst1;

	lst1 = ft_lstnew(init_key_val("USER", "nveneros"));

	// expansion_var("salut $123\"$USER\"suite $'$USER' '$USER'$", &lst1);
	// expansion_var("$USER | $'$USER'\"$USER\" $$", &lst1);
	// expansion_var("$hello_bye_bye$", &lst1);
	// expansion_var("hel$'$'USER", &lst1);
	test("\"$USER|$USER>\"", &lst1, "\"nveneros|nveneros>\"");
	test("salut $123", &lst1, "salut $123");
	test("hel$'$'USER", &lst1, "hel$'$'USER");
	test("$USER | $'$USER'\"$USER\" $$", &lst1, "nveneros | $'$USER'\"nveneros\" $$");
	free_key_val(lst1->content);
	free(lst1);
	return (0);
}
