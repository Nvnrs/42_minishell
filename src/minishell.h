/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:12:26 by nveneros          #+#    #+#             */
/*   Updated: 2025/02/19 15:06:12 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/MYLIB42/mylib42.h"

# define DOUBLE_QUOTE 34
# define SINGLE_QUOTE 39

typedef struct s_key_val
{
	char	*key;
	char	*value;
}	t_key_val;

typedef struct s_cmd
{
	char	*name;
	char	**args_exec;
	t_list	**operators_in;
	t_list	**operators_out;
	int		pipes[2][2];
}	t_cmd;

//src/parsing/parse_input.c
int		count_word_in_input(char *str);
char	**parse_input(char *str);

//src/parsing/handle_no_quote.c
int		handle_no_quote(char **split, int split_index, char *str, int i_start);
int		count_no_quote(char *str, int i_start);

//src/parsing/handle_quote.c
int		handle_quote(char **split, int split_index, char *str, int i_start);
int		count_quote(char *str, int i_start);

//src/parsing/parse_utils.c
t_bool	is_double_redirection(char *str, int index);
t_bool	is_single_operator(char *str, int index);

//src/parsing/checks/checks_after_operators.c
t_bool	after_operators_is_empty(char *str);

//src/parsing/checks/checks_operators.c
t_bool	is_start_of_operator(char *operator, char *str, int i_str);
t_bool	operators_are_valid(char *str);

//src/parsing/checks/checks_consecutive_operators.c
t_bool	consecutives_operators(char *str);

//src/parsing/checks/check_quotes.c
t_bool	nb_quotes_is_even(char type_quote, char other_quote, char *str);
t_bool	quotes_are_valid(char *str);

//src/parsing/checks/checks.c
t_bool	basics_checks(char *str);

// STR to ENV
t_key_val	*init_key_val(char *key, char *value);
t_list		**init_list_env(char *envp[]);
void		free_key_val(void *env_var_void);
void		free_list_env(t_list **env);
void		print_env_var(t_key_val *env_var);
void		print_list_env(t_list **env);

// ENV to STR
char		**lst_env_to_tab_str(t_list **lst_env);

//?/split_utils.c
int		len_split(char **split);
void	free_split(char **split);
void	print_split(char **split);

//operators.c
int		ft_strcmp(const char *s1, const char *s2);
t_list	**init_operators_in(char **split, int i_start, int i_end);
t_list	**init_operators_out(char **split, int i_start, int i_end);

t_list	**init_lst_cmd(char **input);
t_cmd	*init_cmd(char **input, int start, int end);
void	print_start_end(char **tab, int start, int end);
char	*get_cmd_name(char	**input, int i_start, int i_end);
int		count_cmd_arguments(char **input, int i_start, int i_end);
char	**get_cmd_arguments(char **input, int i_start, int i_end);
void	free_lst_cmd(t_list **lst_cmd);
void	print_cmd(void *cmd_content);
void	free_cmd(void *cmd_void);
void	print_list_operators(t_list **operators);

#endif