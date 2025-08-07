CC := cc
CFLAGS := -g -Wall -Werror -Wextra 

SRCS := main.c utils.c input.c eating.c getters_setters.c \
		monitor.c write.c sync.c clean.c threads.c
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
