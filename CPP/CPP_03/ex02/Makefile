CPP = c++
CPP_FLAGS = -Wall -Wextra -Werror -std=c++98
SRC = main.cpp FragTrap.cpp ScavTrap.cpp ClapTrap.cpp
OBJS = $(SRC:.cpp=.o)

NAME = fragtrap

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