CC := cc
CFLAGS := -g -Wall -Werror -Wextra -I.

SRCS := main.c utils.c input.c eating.c getters_setters.c sync_utils.c \
		write.c
OBJS := $(SRCS:.c=.o)
NAME := philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SILENT:
