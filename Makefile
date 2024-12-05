SERVER = server
CLIENT = client
LIBFT = libft.a
LIBFT_DIR = includes/libft
CLIENTBONUSSRC = client_bonus.c
SERVERBONUSSRC = server_bonus.c
CLIENTSRC = client.c
SERVERSRC = server.c

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(LIBFT) $(SERVER) $(CLIENT)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(SERVER): $(SERVERSRC)
	$(CC) $(CFLAGS) $(SERVERSRC) -o $(SERVER) -Lincludes/libft -lft

$(CLIENT): $(CLIENTSRC)
	$(CC) $(CFLAGS) $(CLIENTSRC) -o $(CLIENT) -Lincludes/libft -lft

bonus: $(SERVER)_bonus $(CLIENT)_bonus

$(SERVER)_bonus: $(SERVERBONUSSRC)
	$(CC) $(CFLAGS) $(SERVERBONUSSRC) -o $(SERVER) -Lincludes/libft -lft

$(CLIENT)_bonus: $(CLIENTBONUSSRC)
	$(CC) $(CFLAGS) $(CLIENTBONUSSRC) -o $(CLIENT) -Lincludes/libft -lft

clean:
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all bonus clean fclean re
