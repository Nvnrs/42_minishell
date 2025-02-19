/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:53:02 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/19 15:38:56 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//   * char *name
//   * char **parameters_execve
//   * t_list operators_in
//   * t_list operators_out
//   * int pipes[2][2]


void	print_start_end(char **tab, int start, int end)
{
	printf("start :%d\n", start);
	printf("end :%d\n", end);
	while (start <= end)
	{
		printf("%s", tab[start]);
		start++;
	}
	printf("\n");
}


char	*get_cmd_name(char	**input, int i_start, int i_end)
{
	while (input[i_start] && i_start <= i_end)
	{
		if (is_start_of_operator("<", input[i_start], 0) || is_start_of_operator(">", input[i_start], 0))
			i_start += 2;
		else
		{
			if (input[i_start])
				return(ft_strdup(input[i_start]));
			else
				return (NULL);
		}
	}
	return (NULL);
}

int		count_cmd_arguments(char **input, int i_start, int i_end)
{
	int	counter;

	counter = 0;
	while (input[i_start] && i_start <= i_end)
	{
		if (is_start_of_operator("<", input[i_start], 0) || is_start_of_operator(">", input[i_start], 0))
			i_start += 2;
		else
		{
			counter++;
			i_start++;
		}
	}
	return (counter);
}

char	**get_cmd_arguments(char **input, int i_start, int i_end)
{
	char	**cmd_arguments;
	int		i_arguments;
	int		number_of_arguments;

	number_of_arguments = count_cmd_arguments(input, i_start, i_end);
	cmd_arguments = malloc(sizeof (char *) * (number_of_arguments + 1));
	if (cmd_arguments == NULL)
		return (NULL);
	i_arguments = 0;
	while (input[i_start] && i_start <= i_end)
	{
		if (is_start_of_operator("<", input[i_start], 0) || is_start_of_operator(">", input[i_start], 0))
			i_start += 2;
		else
		{
			cmd_arguments[i_arguments] = ft_strdup(input[i_start]);
			i_start++;
			i_arguments++;
		}
	}
	cmd_arguments[number_of_arguments] = NULL;
	return (cmd_arguments);
}

t_cmd	*init_cmd(char **input, int start, int end)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof (t_cmd));
	cmd->name = get_cmd_name(input, start, end);
	cmd->args_exec = get_cmd_arguments(input, start, end);
	cmd->operators_in = init_operators_in(input, start, end);
	cmd->operators_out = init_operators_out(input, start, end);
	return (cmd);
}
void	print_operator(t_key_val *operator)
{
	printf("%s %s\n", operator->key, operator->value);
}

void	print_list_operators(t_list **operators)
{
	t_list	*lst;
	int		i;

	lst = *operators;
	i = 0;
	while (lst)
	{
		printf("~~~[%d] :", i);
		print_operator(lst->content);
		lst = lst->next;
		i++;
	}
}

void	print_args_of_cmd(char **args)
{
	int i;

	i = 0;
	printf("args_exec :\n");
	while (args[i])
	{
		printf("~~~[%d] :%s\n", i, args[i]);
		i++;
	}
}

void	print_cmd(void *cmd_content)
{
	t_cmd	*cmd;
	static int i;

	cmd = cmd_content;
	printf("\033[0;35m%d ------------------------------ %d\n\033[0;30m", i, i);
	printf("name :%s\n", cmd->name);
	print_args_of_cmd(cmd->args_exec);
	printf("operators_in :\n");
	print_list_operators(cmd->operators_in);
	printf("operators_out :\n");
	print_list_operators(cmd->operators_out);
	printf("\033[0;37m");
	i++;
}

void	free_cmd(void *cmd_void)
{
	t_cmd	*cmd;

	cmd = cmd_void;
	free(cmd->name);
	free_split(cmd->args_exec);
	// if (cmd->operators_in == NULL)
	// {
	// 	printf("HEAD IN NULL\n");
	// }
	// if (*cmd->operators_in == NULL)
	// {
	// 	printf("FIRST IN NULL\n");
	// }
	if (cmd->operators_in != NULL)
	{
		// printf("CHEF\n");
		if (*cmd->operators_in != NULL)
		{
			// printf("SIZE= %d\n", ft_lstsize(*cmd->operators_in));
			ft_lstclear(cmd->operators_in, free_key_val);
		}
		free(cmd->operators_in);
	}
	if (cmd->operators_out != NULL)
	{
		// printf("CHEF\n");
		if (*cmd->operators_out != NULL)
		{
			// printf("SIZE= %d\n", ft_lstsize(*cmd->operators_in));
			ft_lstclear(cmd->operators_out, free_key_val);
		}
		free(cmd->operators_out);
	}
	// if (cmd->operators_out != NULL)
	// 	ft_lstclear(cmd->operators_out, free_key_val);
	// if (cmd->operators_in != NULL)
	// 	free(cmd->operators_in);
	//free(cmd->operators_out);
	free(cmd);
}

void	free_lst_cmd(t_list **lst_cmd)
{
	ft_lstclear(lst_cmd, free_cmd);
	free(lst_cmd);
	lst_cmd = NULL;
}

t_list	**init_lst_cmd(char **input)
{
	t_list	**lst_cmd;
	int		i;
	int		start;
	int		end;

	i = 0;
	start = 0;
	end = 0;
	lst_cmd = malloc(sizeof(t_list *));
	*lst_cmd = NULL;
	while (input[i] && input)
	{
		if (ft_strcmp(input[i], "|") == 0 ||  i == (len_split(input) - 1))
		{
			end = i - 1;
			if (i == (len_split(input) - 1))
				end = i;
			if (*lst_cmd == NULL)
			{
				*lst_cmd =  ft_lstnew(init_cmd(input, start, end));
			}
			else
				ft_lstadd_back(lst_cmd, ft_lstnew(init_cmd(input, start, end)));
			// print_start_end(input, start, end);
			start = i + 1;
		}
		i++;
	}
	return (lst_cmd);
}
