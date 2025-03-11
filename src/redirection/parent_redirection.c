/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:53:26 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/11 13:17:50 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Save a copy of STDIN in the t_cmd struct
 * if the command has an in redirection linked to it.
 * Save a copy of STDOUT int the t_cmd struct
 * if the command has an out redirection linked to it.
 */
void	save_in_and_out(t_cmd *cmd)
{
	if (operator_in_in_lst_operator(*cmd->lst_operator))
		cmd->saved_in = dup(0);
	if (operator_out_in_lst_operator(*cmd->lst_operator))
		cmd->saved_out = dup(1);
}

/**
 * Restore the original STDIN if it was changed.
 * Restore the original STDOUT if it was changed.
 */
void	restore_in_and_out(t_cmd *cmd)
{
	if (cmd->saved_in != -1)
	{
		dup2(cmd->saved_in, 0);
		close(cmd->saved_in);
	}
	if (cmd->saved_out != -1)
	{
		dup2(cmd->saved_out, 1);
		close(cmd->saved_out);
	}
}
