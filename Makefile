SRC_DIR = ./src
SRC_PARSE_DIR = $(SRC_DIR)/parsing
SRC_INIT_DIR = $(SRC_DIR)/init

SRC_PARSE = $(SRC_PARSE_DIR)/parse_input.c \
		$(SRC_PARSE_DIR)/parse_utils.c \
		$(SRC_PARSE_DIR)/handle_quote.c \
		$(SRC_PARSE_DIR)/handle_no_quote.c \
		$(SRC_PARSE_DIR)/checks/checks_after_operators.c \
		$(SRC_PARSE_DIR)/checks/checks_consecutive_operators.c \
		$(SRC_PARSE_DIR)/checks/checks_operators.c \
		$(SRC_PARSE_DIR)/checks/checks_quotes.c \
		$(SRC_PARSE_DIR)/checks/checks.c

SRC_INIT = $(SRC_INIT_DIR)/key_val.c

SRC_ENV = $(SRC_INIT_DIR)/env/env_lst.c \
		$(SRC_INIT_DIR)/env/env_tab_str.c \
		$(SRC_INIT_DIR)/env/env_utils.c

SRC = $(SRC_DIR)/main.c \
	$(SRC_DIR)/split_utils.c \
	$(SRC_DIR)/init/operators.c \
	$(SRC_DIR)/init/cmd.c \
	$(SRC_INIT) \
	$(SRC_ENV) \
	$(SRC_PARSE)

OBJ = $(SRC:.c=.o)
CC = cc
# CFLAGS += -Wall -Wextra -Werror -g -Isrc
CFLAGS += -Isrc
NAME = minishell

LIB_DIR = ./lib
MYLIB42_DIR = $(LIB_DIR)/MYLIB42
MYLIB42 = $(MYLIB42_DIR)/mylib42.a

%.o: %.c 
	$(CC) $(CFLAGS) -c $(<) -o $(@)

all : $(NAME)

$(NAME) :  $(MYLIB42) $(OBJ)
	$(CC) -g $(CFLAGS) $(OBJ) $(MYLIB42) -o $(NAME) -lreadline

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