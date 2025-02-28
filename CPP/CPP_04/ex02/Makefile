CPP = c++
CPP_FLAGS = -Wall -Wextra -Werror -std=c++98
SRC = main.cpp Brain.cpp Cat.cpp Dog.cpp Animal.cpp
OBJS = $(SRC:.cpp=.o)

NAME = Animal

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
