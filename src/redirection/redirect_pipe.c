/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:57:08 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/11 10:51:46 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_pipe(t_list *lst_operator, t_cmd *cmd)
{
	if (!operator_in_in_lst_operator(lst_operator))
	{
		if (cmd->pipefd_in >= 0)
			dup2(cmd->pipefd_in, STDIN_FILENO);
	}
	if (!operator_out_in_lst_operator(lst_operator))
	{
		if (cmd->pipefd_out >= 0)
			dup2(cmd->pipefd_out, STDOUT_FILENO);
	}
	if (cmd->nb_pipes > 0)
		close_and_free_pipes(cmd->pipes, cmd->nb_pipes);
}
