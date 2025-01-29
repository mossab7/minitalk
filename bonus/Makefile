SERVER = server
CLIENT = client
LIBFT = libft.a
LIBFT_DIR = ../includes/libft
CLIENTBONUSSRC = client_bonus.c progress_bar.c
SERVERBONUSSRC = server_bonus.c

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(LIBFT) $(SERVER) $(CLIENT)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(SERVER): $(SERVERBONUSSRC)
	$(CC) $(CFLAGS) $(SERVERBONUSSRC) -o $(SERVER) -L$(LIBFT_DIR) -lft

$(CLIENT): $(CLIENTBONUSSRC)
	$(CC) $(CFLAGS) $(CLIENTBONUSSRC) -o $(CLIENT) -L$(LIBFT_DIR) -lft


clean:
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all bonus clean fclean re
