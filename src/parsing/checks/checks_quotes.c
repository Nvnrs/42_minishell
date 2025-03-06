/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:52:28 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/05 18:10:01 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_inside_quote(char quote, char *str, int *i)
{
	*i += 1;
	while (str[*i] && str[*i] != quote)
	{
		*i += 1;
	}
}

t_bool	nb_quotes_is_even(char quote, char other_quote, char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == other_quote)
			skip_inside_quote(other_quote, str, &i);
		else if (str[i] == quote)
		{
			skip_inside_quote(quote, str, &i);
			if (str[i] == quote)
				count += 2;
			else
				count++;
		}
		i++;
	}
	return (count % 2 == 0);
}

t_bool	quotes_are_valid(char *str)
{
	if (!nb_quotes_is_even(SINGLE_QUOTE, DOUBLE_QUOTE, str))
		return (FALSE);
	if (!nb_quotes_is_even(DOUBLE_QUOTE, SINGLE_QUOTE, str))
		return (FALSE);
	return (TRUE);
}

// void	test(char *str, t_bool exp)
// {
// 	static int i = 1;
// 	t_bool otp = quotes_are_valid(str);
// 	printf("%s\n", str);
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
// 	test("impair double quote \"", FALSE);
// 	test("pair double quote \"\"", TRUE);
// 	test("impair single quote \'", FALSE);
// 	test("pair single quote \'\'", TRUE);
// 	test("pair single quote but impair double quote \'\'\"", FALSE);
// 	test("pair double quote but impair single quote \"\"\'", FALSE);
// 	test("impair single quote insid double \"hello\'\"", TRUE);
// 	test("impair double quote insid single \'hello\"\'", TRUE);
// 	test("ALL \" salut je test\' \" pour voir\' \"", FALSE);
// 	return (0);
// }
