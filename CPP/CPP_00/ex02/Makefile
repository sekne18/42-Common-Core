CPP = c++
CPP_FLAGS = -Wall -Wextra -Werror -std=c++98
SRC =  Account.cpp tests.cpp

OBJS = $(SRC:.cpp=.o)

NAME = account

all: $(NAME)

$(NAME):$(OBJS)
	$(CPP) $(CPP_FLAGS) $(OBJS) -o $(NAME) 

%.o: %.cpp
	$(CPP) $(CPP_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SILENT:
