/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:52:28 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/17 17:13:54 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	nb_quotes_is_even(char type_quote, char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (type_quote == str[i])
			count++;
		i++;
	}
	if (count % 2 == 0 )
		return (TRUE);
	return (FALSE);
}

t_bool	quotes_are_valid(char *str)
{
	if (!nb_quotes_is_even('\'', str))
		return (FALSE);
	if (!nb_quotes_is_even('\"', str))
		return (FALSE);
	return (TRUE);
}


// #include <stdio.h>
// void	test(char *str, t_bool exp)
// {
// 	static int i = 1;
// 	t_bool otp = quotes_is_valid(str);
// 	// printf("%s\n", str);
// 	// printf("quotes is valid %d\n", otp);
// 	printf("TEST: %d | ", i);
// 	if (exp == otp)
// 		printf("OK");
// 	else
// 		printf("KO");
// 	printf("\n");
// 	i++;
// }
// int	main(void)
// {
// 	test("1 single quote test '", FALSE);
// 	test("2 single quote test ''", TRUE);
// 	test("1 double quote test \"", FALSE);
// 	test("2 double quote test \"\"", TRUE);
// 	test(" 0 quote test", TRUE);
// 	return (0);
// }