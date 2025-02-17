/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:10:56 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/17 15:27:24 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
		i++;
	return (i);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	print_split(char **split)
{
	int	i;
	int	len;

	i = 0;
	len = len_split(split);
	while (i < len)
	{
		ft_printf("split[%d]: %s\n", i, split[i]);
		i++;
	}
}
t_bool	is_double_redirection(char *str, int index)
{
	if ((str[index] == '>' && str[index + 1] == '>')
		|| (str[index] == '<' && str[index + 1] == '<'))
		return (TRUE);
	return (FALSE);
}

t_bool	is_single_operator(char *str, int index)
{
	if (c_is_in_charset(str[index], "><|"))
		return (TRUE);
	return (FALSE);
}

int	handle_quote(char **split, int split_index, char *str, int i_start)
{
	int		i_end;

	i_end = i_start;
	if (ft_strlen(str) - i_start >= 2)
	{
		while (str[i_end] == SINGLE_QUOTE || str[i_end] == DOUBLE_QUOTE || (str[i_end] != ' ' && !is_single_operator(str, i_end)))
		{
			if (str[i_end] == SINGLE_QUOTE)
			{
				i_end++;
				while (str[i_end] != SINGLE_QUOTE)
					i_end++;
			}
			else if (str[i_end] == DOUBLE_QUOTE)
			{
				i_end++;
				while (str[i_end] != DOUBLE_QUOTE)
					i_end++;
			}
			i_end++;
		}
		split[split_index] = ft_substr(str, i_start, i_end - i_start);
		return (i_end - i_start);
	}
	return (0);
}

int	count_quote(char *str, int i_start)
{
	int		i_end;

	i_end = i_start;
	if (ft_strlen(str) - i_start >= 2)
	{
		while (str[i_end] == SINGLE_QUOTE || str[i_end] == DOUBLE_QUOTE || (str[i_end] != ' ' && !is_single_operator(str, i_end)))
		{
			if (str[i_end] == SINGLE_QUOTE)
			{
				i_end++;
				while (str[i_end] != SINGLE_QUOTE)
					i_end++;
			}
			else if (str[i_end] == DOUBLE_QUOTE)
			{
				i_end++;
				while (str[i_end] != DOUBLE_QUOTE)
					i_end++;
			}
			i_end++;
		}
		return (i_end - i_start);
	}
	return (0);
}

int	handle_no_quote(char **split, int split_index, char *str, int i_start)
{
	int	i_end;

	i_end = i_start;
	while (str[i_end] != ' ' && str[i_end] != '\0' && !is_single_operator(str, i_end))
		i_end++;
	split[split_index] = ft_substr(str, i_start, i_end - i_start);
	return (i_end - i_start);
}

int	count_no_quote(char *str, int i_start)
{
	int	i_end;

	i_end = i_start;
	while (str[i_end] != ' ' && str[i_end] != '\0' && !is_single_operator(str, i_end))
		i_end++;
	return (i_end - i_start);
}

void	count_token2(int *count, int *i, char *str)
{
	if (str[*i] == SINGLE_QUOTE || str[*i] == DOUBLE_QUOTE)
	{
		*count += 1;
		*i += count_quote(str, *i);
	}
	else if (is_double_redirection(str, *i))
	{
		*count += 1;
		*i += 2;//i + 2
	}
	else if (is_single_operator(str, *i))
	{
		*count += 1;
		*i += 1;
	}
	else if (str[*i] != ' ')
	{
		*count += 1;
		*i += count_no_quote(str, *i);
	}
	else
		*i += 1;
}

int	count_token(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		count_token2(&count, &i, str);
	}
	return (count);
}

char	**parse_str(char *str)
{
	char	**split;
	int		i_split;
	int		i;

	i = 0;
	i_split = 0;
	split = malloc((count_token(str) + 1 )* sizeof (char *));
	while (str[i])
	{
		if (str[i] == SINGLE_QUOTE || str[i] == DOUBLE_QUOTE)
		{
			i += handle_quote(split, i_split, str, i);
			i_split++;
		}
		else if (is_double_redirection(str, i))// << >>
		{
			split[i_split] = ft_substr(str, i, 2);
			i += 2;//i + 2
			i_split++;
		}
		else if (is_single_operator(str, i))// < > |
		{
			split[i_split] = ft_substr(str, i, 1);
			i++;
			i_split++;
		}
		else if (str[i] != ' ')
		{
			i += handle_no_quote(split, i_split, str, i);
			i_split++;
		}
		else
			i++;
	}
	split[count_token(str)] = NULL;
	return (split);
}

int	main(void)
{
	char	*rd;
	int		flag;
	char	**split;

	flag = 1;
	while (flag)
	{
		rd = readline("> ");
		if (rd && *rd)
			add_history(rd);
		if (rd == NULL)
			flag = 0;
		else
		{
			split = parse_str(rd);
			print_split(split);
			free_split(split);
		}
		free(rd);
	}
	rl_clear_history();
	return (0);
}
