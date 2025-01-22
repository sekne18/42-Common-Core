CC := cc
CFLAGS := -g -Wall -Wextra -Werror

LIB := libft
SRC_DIR := src
INC_DIR := include
OBJ_DIR := obj

LINK_FLAGS := -lreadline -L$(LIB) -l$(subst lib,,$(LIB))
INC_FLAGS := -I$(INC_DIR) -I$(LIB)/include

FILES := main.c expansions.c builtins_1.c builtins_2.c signals.c \
cmd_execution.c path_util.c str_utils.c builtin_utils.c setenv.c \
signal_helper.c set_context.c clean.c \
data_structures/dynamic_array.c data_structures/dynamic_array_2.c data_structures/dynamic_array_3.c\
executor/exec_cmd.c executor/exec_arg.c executor/exec_nodes.c \
executor/exec_redir_node.c executor/exec_redir_node_helpers.c executor/executor.c \
lexer/lexer.c lexer/add_token.c lexer/lexer_checks.c lexer/lexer_utils.c lexer/match_token.c \
parser/parser.c parser/tree_traversal.c parser/tree_traversal_2.c parser/create_nodes.c parser/parse_pipeline.c\
parser/connect_nodes.c parser/parser_utils.c parser/parse_cmd.c \
expansion_utils.c wildcard_expansion_utils.c setenv_utils.c init_funcs.c \

SRCS := $(addprefix $(SRC_DIR)/, $(FILES))
OBJS := $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))
NAME := minishell

all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LINK_FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

$(LIB):
	make -C $(LIB)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re $(LIB)
