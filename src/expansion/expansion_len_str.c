/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_len_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:35:37 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/06 17:27:39 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_len_expansion_var(char *str, int *i_out, t_list **lst_env)
{
	char	*value;
	char	*key;
	int		len_key;

	key = get_key_in_str(str);
	len_key = ft_strlen(key);
	value = get_value_from_key(key, lst_env);
	if (value == NULL)
	{
		free(key);
		return (len_key);
	}
	*i_out += ft_strlen(value);
	free(value);
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
		if (is_start_of_expansion(str, i))
		{
			i++;
			i += add_len_expansion_var(&str[i], i_out, lst_env);
			continue ;
		}
		i++;
		*i_out += 1;
	}
	return (i);
}

void	len_in_single_quote(char *str, int *i, int *i_out)
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
			len_in_single_quote(str, &i, &i_out);
		else if (str[i] == DOUBLE_QUOTE)
			i += len_in_double_quote(&str[i], &i_out, lst_env);
		else if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
		{
			i++;
			i += add_len_expansion_var(&str[i], &i_out, lst_env);
			continue ;
		}
		i++;
		i_out++;
	}
	return (i_out);
}
