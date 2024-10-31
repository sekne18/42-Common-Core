CC := cc
CFLAGS := -Wall -Werror -Wextra -I.

SRC_SERV := server.c 
SRC_CLI := client.c
OBJ_SERV := $(SRC_SERV:.c=.o)
OBJ_CLI := $(SRC_CLI:.c=.o)
NAME_SERV := server
NAME_CLI := client
LIBFT := ./libft/libft.a

all: client server

server: $(OBJ_SERV)
	@$(MAKE) -C ./libft
	@$(CC) $(CFLAGS) $(OBJ_SERV) $(LIBFT) -o $(NAME_SERV)

client: $(OBJ_CLI)
	@$(MAKE) -C ./libft
	@$(CC) $(CFLAGS) $(OBJ_CLI) $(LIBFT) -o $(NAME_CLI)

clean:
	@$(MAKE) -C ./libft clean
	@rm -f $(OBJ_SERV)
	@rm -f $(OBJ_CLI)

fclean: clean
	@$(MAKE) -C ./libft fclean
	@rm -f $(NAME_SERV) $(NAME_CLI)

re: fclean all

.PHONY: all clean fclean re

.SILENT:
