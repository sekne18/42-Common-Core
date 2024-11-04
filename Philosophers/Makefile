CC := cc
CFLAGS := -Wall -Werror -Wextra -I./philo

SRCS := ./philo/main.c
OBJS := $(SRCS:.c=.o)
NAME := philo

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SILENT:
