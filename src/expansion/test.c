/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:53:47 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/24 15:15:03 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	test(char *str, t_list **env, char *expected)
// {
// 	char			*output;
// 	static int		i = 1;

// 	output = expansion_str(str, env);
// 	// printf("expected : %s\n", expected);
// 	printf("Len exp : %d\n", (int)ft_strlen(output));
// 	printf("Len out : %d\n", len_expansion_str(str, env));
// 	printf("Test %d | ", i);
// 	if (ft_strcmp(output, expected) == 0)
// 	{
// 		printf("\033[0;32mOK");
// 	}
// 	else
// 		printf("\033[0;31mKO");
// 	printf("\033[0;37m\n");
// 	free(output);
// 	i++;
// }

// int	main()
// {
// 	t_list	*lst1;

// 	lst1 = ft_lstnew(init_key_val("USER", "nveneros"));

// 	// expansion_var("salut $123\"$USER\"suite $'$USER' '$USER'$", &lst1);
// 	// expansion_var("$USER | $'$USER'\"$USER\" $$", &lst1);
// 	// expansion_var("$hello_bye_bye$", &lst1);
// 	// expansion_var("hel$'$'USER", &lst1);
// 	test("\"$USER|$USER>\"", &lst1, "\"nveneros|nveneros>\"");
// 	test("salut $123", &lst1, "salut $123");
// 	test("hel$'$'USER", &lst1, "hel$'$'USER");
// 	test("$USER | $'$USER'\"$USER\" $$", &lst1, "nveneros | $'$USER'\"nveneros\" $$");
// 	free_key_val(lst1->content);
// 	free(lst1);
// 	return (0);
// }
