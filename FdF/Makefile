CC := cc
CFLAGS := -g -Wall -Werror -Wextra -I.
MLXFLAGS := -lmlx -lXext -lX11 -lm -lbsd

SRCS := fdf.c main.c get_next_line.c
OBJS := $(SRCS:.c=.o)
NAME := fdf
LIBMLX := ./mlx/libmlx.a

$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	$(MAKE) -C ./mlx
	$(CC) $(CFLAGS) $(OBJS) -Lmlx $(MLXFLAGS) ./libft/libft.a -o $(NAME)

all: $(NAME)

clean:
	@make -C ./libft clean
	@make -C ./mlx clean
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME) ./libft/libft.a

re: fclean all

.PHONY: all clean fclean re

.SILENT:
