CC := cc
CFLAGS := -Wall -Werror -Wextra 

SRCS := main.c cycle.c monitor.c clean.c input.c
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

.PHONY : all clean fclean re
.SILENT:
