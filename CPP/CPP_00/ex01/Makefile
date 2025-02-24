CPP = c++
CPP_FLAGS = -Wall -Wextra -Werror -std=c++98
SRC =  PhoneBook.cpp Contact.cpp main.cpp

OBJS = $(SRC:.cpp=.o)

NAME = phonebook

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
