/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:41:30 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/03 11:42:29 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "minishell.h"

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
void	builtin_echo(t_cmd *cmd)
{
	int	i_split;
	char	*output_str;

	i_split = 1;
	output_str = "\0";
	if (cmd->args_exec[1] && is_n_option_echo(cmd->args_exec[1]))
		i_split++;
	if (cmd->args_exec[i_split])
		output_str = cmd->args_exec[i_split];
	while (cmd->args_exec[i_split] && cmd->args_exec[i_split + 1])
	{
		output_str = ft_strjoin(output_str, " ");
		output_str = ft_strjoin(output_str, cmd->args_exec[i_split + 1]);
		i_split++;
	}
	if ((cmd->args_exec[1] && !is_n_option_echo(cmd->args_exec[1])) || len_split(cmd->args_exec) == 1)
		printf("%s\n", output_str);
	else
		printf("%s", output_str);
	if ((len_split(cmd->args_exec) > 2 && !is_n_option_echo(cmd->args_exec[1]))
		|| (len_split(cmd->args_exec) > 3 && is_n_option_echo(cmd->args_exec[1])))
		free(output_str);
	exit_status(0, TRUE);
}