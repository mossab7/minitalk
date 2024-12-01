SERVER = server
CLIENT = client
FTPRINTF = libftprintf.a
FTPRINTF_DIR = includes/ftprintf
FTPRINTFSRC = ft_printf.c ft_printf_number_utilities.c \
              ft_printf_handlers.c ft_printf_utilities.c \
              ft_printf_set_flags.c
CLIENTBONUSSRC = client_bonus.c
SERVERBONUSSRC = server_bonus.c
CLIENTSRC = client.c
SERVERSRC = server.c

CC = cc
CFLAGS = -Wall -Wextra -Werror
FTPRINTFOBJS = $(FTPRINTFSRC:%.c=$(FTPRINTF_DIR)/%.o)

all: $(SERVER) $(CLIENT)

$(FTPRINTF_DIR)/%.o: $(FTPRINTF_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(FTPRINTF): $(FTPRINTFOBJS)
	ar rcs $(FTPRINTF) $(FTPRINTFOBJS)

$(SERVER): $(SERVERSRC) $(FTPRINTF)
	$(CC) $(CFLAGS) $(SERVERSRC) -o $(SERVER) -L. -lftprintf

$(CLIENT): $(CLIENTSRC) $(FTPRINTF)
	$(CC) $(CFLAGS) $(CLIENTSRC) -o $(CLIENT) -L. -lftprintf

bonus: $(SERVER)_bonus $(CLIENT)_bonus

$(SERVER)_bonus: $(SERVERBONUSSRC) $(FTPRINTF)
	$(CC) $(CFLAGS) $(SERVERBONUSSRC) -o $(SERVER) -L. -lftprintf

$(CLIENT)_bonus: $(CLIENTBONUSSRC) $(FTPRINTF)
	$(CC) $(CFLAGS) $(CLIENTBONUSSRC) -o $(CLIENT) -L. -lftprintf

clean:
	rm -f $(FTPRINTFOBJS) $(FTPRINTF)

fclean: clean
	rm -f $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all bonus clean fclean re