CPP = c++
CPP_FLAGS = -g -Wall -Wextra -Werror -std=c++98
SRC = main.cpp
OBJS = $(SRC:.cpp=.o)

NAME = Array

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
