CPP = c++
CPP_FLAGS = -Wall -Wextra -Werror -std=c++98
SRC = src/main.cpp src/Server.cpp
#Request.cpp Response.cpp Config.cpp Utils.cpp Route.cpp Error.cpp Client.cpp CGI.cpp
OBJS = $(SRC:.cpp=.o)

NAME = webserv

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
