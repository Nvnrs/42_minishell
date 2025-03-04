/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:47:59 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/04 11:36:30 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	basics_checks(char *str)
{
	if (str_contain_only_point(str))
	{
		return (force_print_stderr("filename argument required"), FALSE);
	}
	if (!quotes_are_valid(str))
		return (force_print_stderr("quotes invalid\n"), FALSE);
	else if (!operators_are_valid(str))
		return (force_print_stderr("operators invalid\n"), FALSE);
	return (TRUE);
}
