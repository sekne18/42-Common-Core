CC = cc
CFLAGS = -g -Wall -Werror -Wextra

SRCS = ft_printf.c srcs/util.c srcs/hex_util.c 
OBJS = $(SRCS:.c=.o)
NAME = libftprintf.a

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

all: $(NAME) #testing

#test: test.o $(NAME) clean
#	$(CC) -o test test.o $(NAME)

#test.o: test.c	
#	$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(EXEC) #test

re: fclean all
