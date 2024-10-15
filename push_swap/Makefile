CC = cc
CFLAGS = -Wall -Werror -Wextra -I.

SRCS = push_swap.c utils.c
OBJS = $(SRCS:.c=.o)
NAME = push_swap

$(NAME): $(OBJS)
	@$(MAKE) -C ./libft
	@$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a -o $(NAME)

all: $(NAME)

clean:
	@$(MAKE) -C ./libft fclean
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
