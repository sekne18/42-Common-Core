CPP = c++
CPP_FLAGS = -Wshadow -Wno-shadow -Wall -Wextra -Werror -std=c++98
SRC = main.cpp FragTrap.cpp ScavTrap.cpp ClapTrap.cpp DiamondTrap.cpp
OBJS = $(SRC:.cpp=.o)

NAME = diamondtrap

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
