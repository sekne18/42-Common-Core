CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

FILES = ft_isx.c ft_mem_alloc.c ft_mem_op.c ft_put.c ft_split.c ft_itoa.c ft_striteri.c ft_strjoin.c \
ft_strmapi.c ft_str_op.c ft_str_op_2.c ft_str_op_3.c ft_strtrim.c ft_lstnew.c ft_lstadd_back.c \
ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstsize.c \
get_next_line.c get_next_line_utils.c ft_numlen.c ft_atod.c ft_strjoin2.c ft_put_2.c
SRCS = $(addprefix $(SRC_DIR)/, $(FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))
NAME = libft.a

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
