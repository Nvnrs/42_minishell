SRC_DIR = /src
SRC_PARSE_DIR = $(SRC_DIR)/parsing
SRC_INIT_DIR = $(SRC_DIR)/init
SRC_PARSE_CHECK_DIR = $(SRC_PARSE_DIR)/checks
SRC_INIT_CMD_DIR = $(SRC_INIT_DIR)/cmd
SRC_INIT_ENV_DIR = $(SRC_INIT_DIR)/env
SRC_INIT_PIPE_DIR = $(SRC_INIT_DIR)/pipe
SRC_EXPANSION_DIR = $(SRC_DIR)/expansion
SRC_REMOVES_QUOTES_DIR = $(SRC_DIR)/remove_quotes
SRC_DEBUG_DIR = $(SRC_DIR)/debug
SRC_REDIRECTION_DIR = $(SRC_DIR)/redirection
SRC_EXEC_DIR = $(SRC_DIR)/executing
SRC_BUILTINS_DIR = $(SRC_DIR)/builtins
SRC_SIGNALS_DIR = $(SRC_DIR)/signals

SRC_PARSE_CHECK = $(SRC_PARSE_CHECK_DIR)/checks_after_operators.c \
				$(SRC_PARSE_CHECK_DIR)/checks_consecutive_operators.c \
				$(SRC_PARSE_CHECK_DIR)/checks_operators.c \
				$(SRC_PARSE_CHECK_DIR)/checks_quotes.c \
				$(SRC_PARSE_CHECK_DIR)/checks.c \
				$(SRC_PARSE_CHECK_DIR)/check_only_point.c \
				$(SRC_PARSE_CHECK_DIR)/check_only_space.c

SRC_PARSE = $(SRC_PARSE_DIR)/parse_input.c \
		$(SRC_PARSE_DIR)/parse_utils.c \
		$(SRC_PARSE_DIR)/handle_quote.c \
		$(SRC_PARSE_DIR)/handle_no_quote.c \
		$(SRC_PARSE_CHECK)

SRC_INIT_CMD = $(SRC_INIT_CMD_DIR)/cmd_arguments.c \
			$(SRC_INIT_CMD_DIR)/cmd_name.c \
			$(SRC_INIT_CMD_DIR)/cmd.c

SRC_INIT_ENV = $(SRC_INIT_ENV_DIR)/env_lst.c \
			$(SRC_INIT_ENV_DIR)/env_tab_str.c

SRC_INIT_PIPE = $(SRC_INIT_PIPE_DIR)/add_pipe_redir.c \
				$(SRC_INIT_PIPE_DIR)/close_pipes.c \
				$(SRC_INIT_PIPE_DIR)/free_pipes.c \
				$(SRC_INIT_PIPE_DIR)/pipes.c

SRC_INIT = $(SRC_INIT_DIR)/key_val.c \
		$(SRC_INIT_DIR)/operators.c \
		$(SRC_INIT_CMD) \
		$(SRC_INIT_ENV) \
		$(SRC_INIT_PIPE)

SRC_DEBUG = $(SRC_DEBUG_DIR)/cmd.c \
			$(SRC_DEBUG_DIR)/env.c \
			$(SRC_DEBUG_DIR)/operators.c

SRC_EXPANSION = $(SRC_EXPANSION_DIR)/expansion_len_str.c \
				$(SRC_EXPANSION_DIR)/expansion_str.c \
				$(SRC_EXPANSION_DIR)/expansion_var.c \
				$(SRC_EXPANSION_DIR)/apply_expansion.c

SRC_REMOVES_QUOTES = $(SRC_REMOVES_QUOTES_DIR)/remove_quotes.c \
					$(SRC_REMOVES_QUOTES_DIR)/apply_remove_quotes.c \
					$(SRC_REMOVES_QUOTES_DIR)/handle_cases_quotes.c

SRC_REDIRECTION = $(SRC_REDIRECTION_DIR)/handle_redirection.c \
				$(SRC_REDIRECTION_DIR)/redirect_in.c \
				$(SRC_REDIRECTION_DIR)/redirect_out.c \
				$(SRC_REDIRECTION_DIR)/redirect_pipe.c \
				$(SRC_REDIRECTION_DIR)/create_here_doc.c \
				$(SRC_REDIRECTION_DIR)/create_tmp_file_here_doc.c \
				$(SRC_REDIRECTION_DIR)/write_tmp_file_here_doc.c \
				$(SRC_REDIRECTION_DIR)/operators_utils.c \
				$(SRC_REDIRECTION_DIR)/parent_redirection.c

SRC_EXEC = $(SRC_EXEC_DIR)/processing.c \
		$(SRC_EXEC_DIR)/exit_status.c \
		$(SRC_EXEC_DIR)/path.c

SRC_BUILTINS = $(SRC_BUILTINS_DIR)/builtins.c \
				$(SRC_BUILTINS_DIR)/echo.c \
				$(SRC_BUILTINS_DIR)/env.c \
				$(SRC_BUILTINS_DIR)/export.c \
				$(SRC_BUILTINS_DIR)/pwd.c \
				$(SRC_BUILTINS_DIR)/exit.c \
				$(SRC_BUILTINS_DIR)/unset.c \
				$(SRC_BUILTINS_DIR)/cd.c

SRC_SIGNALS = $(SRC_SIGNALS_DIR)/sigint.c \
			$(SRC_SIGNALS_DIR)/signals.c

SRC = $(SRC_DIR)/main.c \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/split_utils.c \
	$(SRC_DIR)/env_utils.c \
	$(SRC_INIT) \
	$(SRC_PARSE) \
	$(SRC_DEBUG) \
	$(SRC_EXPANSION) \
	$(SRC_REMOVES_QUOTES) \
	$(SRC_REDIRECTION) \
	$(SRC_BUILTINS) \
	$(SRC_EXEC) \
	$(SRC_SIGNALS)

ALLDIR = $(OBJ_DIR) \
		$(OBJ_DIR)$(SRC_DIR) \
		$(OBJ_DIR)$(SRC_BUILTINS_DIR) \
		$(OBJ_DIR)$(SRC_DEBUG_DIR) \
		$(OBJ_DIR)$(SRC_EXEC_DIR) \
		$(OBJ_DIR)$(SRC_EXPANSION_DIR) \
		$(OBJ_DIR)$(SRC_INIT_DIR) \
		$(OBJ_DIR)$(SRC_INIT_CMD_DIR) \
		$(OBJ_DIR)$(SRC_INIT_ENV_DIR) \
		$(OBJ_DIR)$(SRC_INIT_PIPE_DIR) \
		$(OBJ_DIR)$(SRC_PARSE_DIR) \
		$(OBJ_DIR)$(SRC_PARSE_CHECK_DIR) \
		$(OBJ_DIR)$(SRC_REDIRECTION_DIR) \
		$(OBJ_DIR)$(SRC_REMOVES_QUOTES_DIR) \
		$(OBJ_DIR)$(SRC_SIGNALS_DIR)

OBJ_DIR = ./obj
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)
CC = cc
CFLAGS += -Wall -Wextra -Werror -g -Isrc
NAME = minishell

LIB_DIR = ./lib
MYLIB42_DIR = $(LIB_DIR)/MYLIB42
MYLIB42 = $(MYLIB42_DIR)/mylib42.a

all : $(NAME)

$(ALLDIR):
	mkdir $@

$(OBJ): $(OBJ_DIR)/%.o:%.c
	$(CC) $(CFLAGS) -c $(<) -o $(@)

$(NAME) : $(MYLIB42) $(ALLDIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MYLIB42) -o $(NAME) -lreadline

$(MYLIB42_DIR) :
	git clone https://github.com/Nvnrs/MYLIB42.git $(MYLIB42_DIR)

$(MYLIB42) : $(MYLIB42_DIR)
	$(MAKE) -C $(MYLIB42_DIR)

clean :
	rm -rf $(OBJ)
	$(MAKE) clean -C $(MYLIB42_DIR)

fclean : clean
	rm -rf $(NAME)
	$(MAKE) fclean -C $(MYLIB42_DIR)

re : fclean all

PHONY : clean fclean re all