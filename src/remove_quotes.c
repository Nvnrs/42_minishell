/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:50:45 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/04 17:08:18 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_pair_of_quotes_in_str(char *str)
{
	int	i;
	int	count;
	
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == SINGLE_QUOTE)
		{
			i++;
			while (str[i] != SINGLE_QUOTE)
				i++;
			count += 2;
		}
		else if (str[i] == DOUBLE_QUOTE)
		{
			i++;
			while (str[i] != DOUBLE_QUOTE)
				i++;
			count +=2;
		}
		i++;
	}
	return (count);
}

void	single_quote_case(char *str, char *newstr, int *i_str, int *i_newstr)
{
	*i_str += 1;
	while (str[*i_str] != SINGLE_QUOTE)
	{
		newstr[*i_newstr] = str[*i_str];
		*i_str += 1;
		*i_newstr += 1;
	}
}

void	double_quote_case(char *str, char *newstr, int *i_str, int *i_newstr)
{
	*i_str += 1;
	while (str[*i_str] != DOUBLE_QUOTE)
	{
		newstr[*i_newstr] = str[*i_str];
		*i_str += 1;
		*i_newstr += 1;
	}
}

void	others_case(char *str, char *newstr, int *i_str, int *i_newstr)
{
	newstr[*i_newstr] = str[*i_str];
	*i_newstr += 1;
}


char	*remove_quotes_in_str(char *str)
{
	char	*newstr;
	int		i_str;
	int		i_newstr;
	int		len_newstr;
	
	if (count_pair_of_quotes_in_str(str) == 0)
		return (str);
	len_newstr = ft_strlen(str) - count_pair_of_quotes_in_str(str) + 1;
	newstr = malloc(sizeof (char) * len_newstr);
	if (newstr == NULL)
		return (NULL);
	init_int_zero(&i_str, &i_newstr, NULL, NULL);
	while (str[i_str])
	{
		if (str[i_str] == SINGLE_QUOTE)
			single_quote_case(str, newstr, &i_str, &i_newstr);
		else if (str[i_str] == DOUBLE_QUOTE)
			double_quote_case(str, newstr, &i_str, &i_newstr);
		else if (str[i_str] != SINGLE_QUOTE && str[i_str] != DOUBLE_QUOTE)
			others_case(str, newstr, &i_str, &i_newstr);
		i_str++;
	}
	newstr[len_newstr - 1] = '\0';
	free(str);
	return (newstr);
}

static void	apply_remove_quotes_args_exec(char **args_exec)
{
	int i;

	i = 0;
	while (args_exec[i])
	{
		args_exec[i] = remove_quotes_in_str(args_exec[i]);
		i++;
	}
}

static void	apply_remove_quotes_operators(t_list **operators)
{
	t_list	*lst;
	t_key_val *content;

	lst = *operators;
	while (lst)
	{
		content = lst->content;
		content->value = remove_quotes_in_str(content->value);
		lst = lst->next;
	}
		
}

void	apply_remove_quotes(t_list **lst_cmd)
{
	t_list	*lst;
	t_cmd	*cmd;

	lst = *lst_cmd;

	while (lst)
	{
		cmd = lst->content;
		if (cmd->name)
			cmd->name = remove_quotes_in_str(cmd->name);
		apply_remove_quotes_args_exec(cmd->args_exec);
		apply_remove_quotes_operators(cmd->lst_operator);
		lst = lst->next;
	}
}