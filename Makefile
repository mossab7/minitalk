SERVER = server
CLIENT = client
LIBFT_DIR = includes/libft
BONUS_DIR = bonus
MANDATORY_DIR = mandatory

all: _mandatory_

_mandatory_:
	make -C $(MANDATORY_DIR)
	cp $(MANDATORY_DIR)/$(SERVER) $(MANDATORY_DIR)/$(CLIENT) .

bonus: _bonus_

_bonus_:
	make -C $(BONUS_DIR)
	cp $(BONUS_DIR)/$(SERVER) $(BONUS_DIR)/$(CLIENT) .

clean:
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(SERVER) $(CLIENT)
	rm -f $(MANDATORY_DIR)/$(SERVER) $(MANDATORY_DIR)/$(CLIENT)
	rm -f $(BONUS_DIR)/$(SERVER) $(BONUS_DIR)/$(CLIENT)

re: fclean all

.PHONY: all bonus clean fclean re
