CC := cc
CFLAGS := -g -Wall -Werror -Wextra 

SRCS := main.c init.c simulation.c actions.c monitor.c utils.c
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