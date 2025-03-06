/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:41:30 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/06 17:15:43 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_n_option_echo(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '-')
		i++;
	else
		return (FALSE);
	if (str[i] && str[i] == 'n')
	{
		while (str[i] && str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (TRUE);
	}
	return (FALSE);
}

/**
 * Creer une chaine de char a partir du tableau de chaine de char
 */
void	builtin_echo(char **args)
{
	int		i;
	char	*output_str;

	i = 0;
	output_str = ft_strdup("\0");
	while (args[i] && is_n_option_echo(args[i]))
		i++;
	if (args[i] && !is_n_option_echo(args[i]))
	{
		free(output_str);
		output_str = ft_strdup(args[i]);
	}
	while (args[i] && args[i + 1])
	{
		output_str = ft_strjoin(output_str, " ");
		output_str = ft_strjoin(output_str, args[i + 1]);
		i++;
	}
	if ((args[0] && is_n_option_echo(args[0])))
		printf("%s", output_str);
	else
		printf("%s\n", output_str);
	free(output_str);
	exit_status(0, TRUE);
}
