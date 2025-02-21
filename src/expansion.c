/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:53:47 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/21 17:53:46 by nveneros         ###   ########.fr       */
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




int	expansion_var(char *str, char *out, int *i_out, t_list **lst_env)
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

void	handle_single_quote(char *str, int *i, char *output, int *i_out)
{
	output[*i_out] = str[*i];
	*i += 1;
	*i_out += 1;
	while (str[*i] != SINGLE_QUOTE)
	{
		output[*i_out] = str[*i];
		*i += 1;
		*i_out += 1;
	}
}

int	handle_double_quote(char *str, char *output, int *i_out_main, t_list **lst_env)
{
	int	i;
	int	i_out;

	i = 0;
	i_out = *i_out_main;
	output[i_out++] = str[i++];
	while (str[i] != DOUBLE_QUOTE)
	{
		if (is_start_of_env_var(str, i))
		{
			i++;
			i+= expansion_var(&str[i], output, &i_out, lst_env);
			continue;
		}	
		output[i_out++] = str[i++];
	}
	*i_out_main = i_out;
	return (i);
}

int	add_len_expansion_var(char *str, int *i_out, t_list **lst_env)
{
	char	*value;
	char	*key;
	int		len_key;

	key = get_key_in_str(str);
	len_key = ft_strlen(key);
	value = find_value_in_env(key, lst_env);
	if (value == NULL)
	{
		free(key);
		return (len_key);
	}
	*i_out += ft_strlen(value);
	free(key);
	return (len_key);
}

int	len_in_double_quote(char *str, int *i_out, t_list **lst_env)
{
	int	i;

	i = 0;
	i++;
	*i_out += 1;
	while (str[i] != DOUBLE_QUOTE)
	{
		if (is_start_of_env_var(str, i))
		{
			i++;
			i+= add_len_expansion_var(&str[i], i_out, lst_env);
			continue;
		}	
		i++;
		*i_out+=1;
	}
	return (i);
}
void	len_in_single_quote(char *str, int *i, int *i_out, t_list **lst_env)
{
	*i += 1;
	*i_out += 1;
	while (str[*i] != SINGLE_QUOTE)
	{
		*i += 1;
		*i_out += 1;
	}
}


int	len_expansion_str(char *str, t_list **lst_env)
{
	int		i;
	int		i_out;

	init_int_zero(&i, &i_out, NULL, NULL);
	while (str[i])
	{
		if (str[i] == SINGLE_QUOTE)
			len_in_single_quote(str, &i, &i_out, lst_env);
		else if (str[i] == DOUBLE_QUOTE)
			i+= len_in_double_quote(&str[i], &i_out, lst_env);
		else if (is_start_of_env_var(str, i))
		{
			i++;
			i+= add_len_expansion_var(&str[i], &i_out, lst_env);
			continue;
		}
		i++;
		i_out++;
	}
	return (i_out);
}

char	*expansion_str(char *str, t_list **lst_env)
{
	int		i;
	int		i_out;
	char	*output;

	init_int_zero(&i, &i_out, NULL, NULL);
	output = malloc((len_expansion_str(str, lst_env) + 1) * sizeof(char));
	output[0] = '\0';
	while (str[i])
	{
		if (str[i] == SINGLE_QUOTE)
			handle_single_quote(str, &i, output, &i_out);
		else if (str[i] == DOUBLE_QUOTE)
			i+= handle_double_quote(&str[i], output, &i_out, lst_env);
		else if (is_start_of_env_var(str, i))
		{
			i++;
			i+= expansion_var(&str[i], output, &i_out, lst_env);
			continue;
		}
		output[i_out++] = str[i++];
	}
	output[i_out] = '\0';
	return (output);
}

// void	test(char *str, t_list **env, char *expected)
// {
// 	char			*output;
// 	static int		i = 1;

// 	output = expansion_str(str, env);
// 	// printf("expected : %s\n", expected);
// 	printf("Len exp : %d\n", (int)ft_strlen(output));
// 	printf("Len out : %d\n", len_expansion_str(str, env));
// 	printf("Test %d | ", i);
// 	if (ft_strcmp(output, expected) == 0)
// 	{
// 		printf("\033[0;32mOK");
// 	}
// 	else
// 		printf("\033[0;31mKO");
// 	printf("\033[0;37m\n");
// 	free(output);
// 	i++;
// }

// int	main()
// {
// 	t_list	*lst1;

// 	lst1 = ft_lstnew(init_key_val("USER", "nveneros"));

// 	// expansion_var("salut $123\"$USER\"suite $'$USER' '$USER'$", &lst1);
// 	// expansion_var("$USER | $'$USER'\"$USER\" $$", &lst1);
// 	// expansion_var("$hello_bye_bye$", &lst1);
// 	// expansion_var("hel$'$'USER", &lst1);
// 	test("\"$USER|$USER>\"", &lst1, "\"nveneros|nveneros>\"");
// 	test("salut $123", &lst1, "salut $123");
// 	test("hel$'$'USER", &lst1, "hel$'$'USER");
// 	test("$USER | $'$USER'\"$USER\" $$", &lst1, "nveneros | $'$USER'\"nveneros\" $$");
// 	free_key_val(lst1->content);
// 	free(lst1);
// 	return (0);
// }
