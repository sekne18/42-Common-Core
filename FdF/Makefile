CC := cc
CLFAGS := -Wall -Werror -Wextra -I.

SRCS = FdF.c main.c
OBJS = $(SRCS:.c=.o)
NAME = FdF

$(NAME): $(OBJS)
	@make -C ./libft
	$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a -o $(NAME)

all: $(NAME)

clean:
	@make -C ./libft fclean
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SILENT:
