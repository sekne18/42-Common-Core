CC = cc
CFLAGS = -Wall -Werror -Wextra

SRCS = ft_printf.c srcs/util.c srcs/hex_util.c 
OBJS = $(SRCS:.c=.o)
NAME = libftprintf.a

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

all: $(NAME) #testing

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(EXEC)

re: fclean all
