/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:12:26 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/03 18:25:32 by nveneros         ###   ########.fr       */
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
# define HERE_DOC_FILENAME ".nRuucnTJX07KI45MgLYviuCjeD1XxLsCjRYv3md9"

typedef struct s_key_val
{
	char	*key;
	char	*value;
}	t_key_val;

typedef struct s_cmd
{
	char		*name;
	char		**args_exec;
	t_list		**lst_operator;
	int			pipefd_in;
	int			pipefd_out;
	// t_list	**operators_in;
	// t_list	**operators_out;
	int			**pipes;
	int			nb_pipes;
	int			saved_in;
	int			saved_out;
}	t_cmd;

typedef int t_exit_status;

// PARSING
int			count_word_in_input(char *str);
char		**parse_input(char *str);
int			handle_no_quote(char **split, int split_index, char *str, int i_start);
int			count_no_quote(char *str, int i_start);
int			handle_quote(char **split, int split_index, char *str, int i_start);
int			count_quote(char *str, int i_start);

// PARSING_CHECKS
t_bool		is_double_redirection(char *str, int index);
t_bool		is_single_operator(char *str, int index);
t_bool		after_operators_is_empty(char *str);
t_bool		is_start_of_operator(char *operator, char *str, int i_str);
t_bool		operators_are_valid(char *str);
t_bool		consecutives_operators(char *str);
t_bool		nb_quotes_is_even(char type_quote, char other_quote, char *str);
t_bool		quotes_are_valid(char *str);
t_bool		basics_checks(char *str);
t_bool		str_contain_only_point(char *str);


// STR to ENV
t_key_val	*init_key_val(char *key, char *value);
t_list		**init_list_env(char *envp[]);
void		free_key_val(void *env_var_void);
void		free_list_env(t_list **env);
void		print_env_var(t_key_val *env_var);
void		print_list_env(t_list **env);

// ENV to STR
char		**lst_env_to_tab_str(t_list **lst_env);
char		*find_value_in_env(char *key, t_list **lst_env);

// OPERATORS
void		print_operator(t_key_val *operator);
void		print_list_operators(t_list **operators);

// CMD
t_list		**init_lst_cmd(char **input);
t_cmd		*init_cmd(char **input, int start, int end);
void		print_start_end(char **tab, int start, int end);
char		*get_cmd_name(char	**input, int i_start, int i_end);
int			count_cmd_arguments(char **input, int i_start, int i_end);
char		**get_cmd_arguments(char **input, int i_start, int i_end);
void		free_lst_cmd(t_list **lst_cmd);
void		print_cmd(void *cmd_content);
void		free_cmd(void *cmd_void);

// PIPES
void		add_pipe_redirect(t_list **lst_cmd, int nb_cmd);
int			**init_pipes(int nb_pipe);
void		close_pipe(int pipes[2]);
void		close_all_pipes(int **pipes, int nb_pipe);
void		close_npipe(int **pipes, int nb_pipe, int n);
void		close_and_free_pipes(int **pipes, int nb_pipe);
void		close_and_free_npipe(int **pipes, int nb_pipe, int n);
void		free_all_pipes(int **pipes, int nb_pipe);
void		free_npipe(int **pipes, int nb_pipe, int n);

// EXPANSIONS
int			len_expansion_str(char *str, t_list **lst_env);
char		*expansion_str(char *str, t_list **lst_env);
t_bool		is_start_of_expansion(char *str, int i);
int			expansion_var(char *str, char *out, int *i_out, t_list **lst_env);
char		*get_key_in_str(char *str);
char 		*find_value_in_env(char *key, t_list **lst_env);
void		apply_expansion(t_list **lst_cmd, t_list **lst_env);

// REDIRECTIONS

int			redirect_out(t_key_val *content, t_bool is_last);
int			redirect_out_append(t_key_val *content, t_bool is_last);
int			redirect_in(t_key_val *content, t_bool is_last);
int			handle_here_doc(t_key_val *content, t_bool is_last);
void		create_all_here_doc(t_list **lst_cmd, t_list **env);
// EXECUTING
int			processing(t_list **lst_cmd, int nb_cmd, t_list **env, int **pipes);
void		free_lst_and_pids(t_list **lst_cmd, t_list **env, int *tab_pid);

// PATH exec
t_bool		cmd_path_is_valid(char *path);
char		*get_path_cmd(t_cmd *cmd, t_list **env);

// SIGNALS
void		set_signals(void);

// UTILS
void		init_int_zero(int *first, int *second, int *third, int *fourth);
int			ft_strcmp(const char *s1, const char *s2);

// SPLIT_UTILS
int			len_split(char **split);
void		free_split(char **split);
void		print_split(char **split);

//A TRIER
int			exit_status(int new_status_code, t_bool update);
char		*get_exit_status_str(void);

char		*get_value_from_key(char *key, t_list **lst_env);

t_list		**init_lst_operator(char **split, int i_start, int i_end);

void		redirect_pipe(t_list *lst_operator, t_cmd *cmd);

int			handle_redirection(t_list *lst_operator, t_list **env, t_cmd *cmd);

t_bool		operator_out_in_lst_operator(t_list *lst_operator);
t_bool		operator_in_in_lst_operator(t_list *lst_operator);

int			handle_error(int status_code, char *context, char *message);

void		apply_remove_quotes(t_list **lst_cmd);
char		*remove_quotes_in_str(char *str);
int 		count_pair_of_quotes_in_str(char *str);

void		add_pipes_in_lst_cmd(t_list **lst_cmd, int **pipes);

void		print_pid_tab(int *pid, int nb_cmd);

t_bool	operator_in_in_lst_operator(t_list *lst_operator);
t_bool	operator_out_in_lst_operator(t_list *lst_operator);
int		index_last_in_operator(t_list *lst_operator);
int		index_last_out_operator(t_list *lst_operator);


// BUILTINS
t_bool	is_builtin(t_cmd *cmd);
void	handle_builtins_child(t_list **lst_cmd, t_cmd *cmd, t_list **env, int *pid);
void	handle_builtins_parent(t_list **lst_cmd, t_cmd *cmd, t_list **env);
void	builtin_echo(char **args);
void	builtin_env(t_list **env);
void	builtin_export(char **args, t_list **env);
void	builtin_pwd(void);
void	builtin_exit(char **args, t_list **lst_cmd, t_list **env, int *pid);
void	builtin_unset(char **args, t_list **env);
void	builtin_cd(char **args, t_list **env);
void	create_all_here_doc(t_list **lst_cmd, t_list **env);
// void	handle_builtins(t_list **lst_cmd, t_cmd *cmd, t_list **env, int *pid);

void	save_new_var(t_key_val *new_var, t_list **env);
void	remove_var(char *var_key, t_list **env);

#endif