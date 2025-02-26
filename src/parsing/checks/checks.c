/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:47:59 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/26 10:27:13 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	basics_checks(char *str)
{
	if (str_contain_only_point(str))
	{
		return (ft_putstr_fd("filename argument required", 2), FALSE);
	}
	if (!quotes_are_valid(str))
		return (ft_putstr_fd("quotes invalid\n", 2), FALSE);
	else if (!operators_are_valid(str))
		return (ft_putstr_fd("operators invalid\n", 2), FALSE);
	return (TRUE);
}
