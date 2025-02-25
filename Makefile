SRC_DIR = ./src
SRC_PARSE_DIR = $(SRC_DIR)/parsing
SRC_INIT_DIR = $(SRC_DIR)/init
SRC_PARSE_CHECK_DIR = $(SRC_PARSE_DIR)/checks
SRC_INIT_CMD_DIR = $(SRC_INIT_DIR)/cmd
SRC_INIT_ENV_DIR = $(SRC_INIT_DIR)/env
SRC_EXPANSION_DIR = $(SRC_DIR)/expansion
SRC_DEBUG_DIR = $(SRC_DIR)/debug
SRC_REDIRECTION_DIR = $(SRC_DIR)/redirection

SRC_PARSE = $(SRC_PARSE_DIR)/parse_input.c \
		$(SRC_PARSE_DIR)/parse_utils.c \
		$(SRC_PARSE_DIR)/handle_quote.c \
		$(SRC_PARSE_DIR)/handle_no_quote.c \
	
SRC_PARSE_CHECK = $(SRC_PARSE_CHECK_DIR)/checks_after_operators.c \
				$(SRC_PARSE_CHECK_DIR)/checks_consecutive_operators.c \
				$(SRC_PARSE_CHECK_DIR)/checks_operators.c \
				$(SRC_PARSE_CHECK_DIR)/checks_quotes.c \
				$(SRC_PARSE_CHECK_DIR)/checks.c

SRC_INIT = $(SRC_INIT_DIR)/key_val.c \
		$(SRC_INIT_DIR)/operators.c \
		$(SRC_INIT_DIR)/pipe_redirections.c \
		$(SRC_INIT_DIR)/close_pipes.c \
		$(SRC_INIT_DIR)/free_pipes.c \
		$(SRC_INIT_DIR)/pipes.c

SRC_INIT_CMD = $(SRC_INIT_CMD_DIR)/cmd_arguments.c \
			$(SRC_INIT_CMD_DIR)/cmd_name.c \
			$(SRC_INIT_CMD_DIR)/cmd.c

SRC_INIT_ENV = $(SRC_INIT_ENV_DIR)/env_lst.c \
		$(SRC_INIT_ENV_DIR)/env_tab_str.c

SRC_DEBUG = $(SRC_DEBUG_DIR)/cmd.c \
			$(SRC_DEBUG_DIR)/env.c \
			$(SRC_DEBUG_DIR)/operators.c

SRC_EXPANSION = $(SRC_EXPANSION_DIR)/expansion_len_str.c \
				$(SRC_EXPANSION_DIR)/expansion_str.c \
				$(SRC_EXPANSION_DIR)/expansion_var.c \

SRC_REDIRECTION = $(SRC_REDIRECTION_DIR)/handle_redirection.c \
				$(SRC_REDIRECTION_DIR)/redirect_in.c \
				$(SRC_REDIRECTION_DIR)/redirect_out.c \
				$(SRC_REDIRECTION_DIR)/redirect_pipe.c

SRC = $(SRC_DIR)/main.c \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/split_utils.c \
	$(SRC_INIT) \
	$(SRC_INIT_CMD) \
	$(SRC_INIT_ENV) \
	$(SRC_PARSE) \
	$(SRC_PARSE_CHECK) \
	$(SRC_DEBUG) \
	$(SRC_EXPANSION) \
	$(SRC_REDIRECTION)

OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS += -Wall -Wextra -Werror -g -Isrc
CFLAGS += -Isrc
NAME = minishell

LIB_DIR = ./lib
MYLIB42_DIR = $(LIB_DIR)/MYLIB42
MYLIB42 = $(MYLIB42_DIR)/mylib42.a

%.o: %.c 
	$(CC) $(CFLAGS) -c $(<) -o $(@)

all : $(NAME)

$(NAME) :  $(MYLIB42) $(OBJ)
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