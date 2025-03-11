/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:47:59 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/11 18:03:19 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	checks_no_exit_status(char *str)
{
	if (ft_strlen(str) == 0)
		return (FALSE);
	if (str_contan_only_space(str))
		return (FALSE);
	return (TRUE);
}

t_bool	checks_exit_status_two(char *str)
{
	if (str_contain_only_point(str))
		return (force_print_stderr("filename argument required\n"), FALSE);
	if (!quotes_are_valid(str))
		return (force_print_stderr("quotes invalid\n"), FALSE);
	if (!operators_are_valid(str))
		return (force_print_stderr("operators invalid\n"), FALSE);
	return (TRUE);
}

t_bool	basics_checks(char *str)
{
	if (!checks_no_exit_status(str))
		return (FALSE);
	if (!checks_exit_status_two(str))
	{
		exit_status(2, TRUE);
		return (FALSE);
	}
	return (TRUE);
}
