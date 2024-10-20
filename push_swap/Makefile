CC = cc
CFLAGS = -g -Wall -Werror -Wextra -I.

SRCS = push_swap.c utils.c list_util.c input.c radix.c \
		swap.c push.c rotate.c rev_rotate.c mini_sort.c
BONUS_SRCS = checker.c swap.c utils.c list_util.c input.c \
		radix.c push.c rotate.c rev_rotate.c mini_sort.c
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
NAME = push_swap

$(NAME): $(OBJS)
	@make -C ./libft
	@make bonus -C ./libft
	@$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a -o $(NAME)

all: $(NAME)

bonus:
	@make -C ./libft
	@make bonus	-C ./libft
	$(CC) $(CFLAGS) $(BONUS_SRCS) ./libft/libft.a -o checker

clean:
	@make -C ./libft fclean
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SILENT:
