SERVER = server
CLIENT = client
LIBFT = libft.a
LIBFT_DIR = ../includes/libft
CLIENTSRC = client.c progress_bar.c
SERVERSRC = server.c

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(LIBFT) $(SERVER) $(CLIENT)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(SERVER): $(SERVERSRC)
	$(CC) $(CFLAGS) $(SERVERSRC) -o $(SERVER) -L$(LIBFT_DIR) -lft

$(CLIENT): $(CLIENTSRC)
	$(CC) $(CFLAGS) $(CLIENTSRC) -o $(CLIENT) -L$(LIBFT_DIR) -lft

clean:
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re
