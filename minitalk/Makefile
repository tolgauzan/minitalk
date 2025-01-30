CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
SERVER = server
CLIENT = client
SERVER_B = server_bonus
CLIENT_B = client_bonus
SRC_SERVER = server.c
SRC_CLIENT = client.c
SRC_SERVER_B = server_bonus.c
SRC_CLIENT_B = client_bonus.c
OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER_B = $(SRC_SERVER_B:.c=.o)
OBJ_CLIENT_B = $(SRC_CLIENT_B:.c=.o)

all: $(NAME)

$(NAME): $(SERVER) $(CLIENT)

$(SERVER): $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) -o $(SERVER)

$(CLIENT): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) -o $(CLIENT)

bonus: $(SERVER_B) $(CLIENT_B)

$(SERVER_B): $(OBJ_SERVER_B)
	$(CC) $(CFLAGS) $(OBJ_SERVER_B) -o $(SERVER_B)

$(CLIENT_B): $(OBJ_CLIENT_B)
	$(CC) $(CFLAGS) $(OBJ_CLIENT_B) -o $(CLIENT_B)

clean: 
	$(RM) $(OBJ_SERVER) $(OBJ_CLIENT) $(OBJ_SERVER_B) $(OBJ_CLIENT_B)

fclean: clean
	$(RM) $(SERVER) $(CLIENT) $(SERVER_B) $(CLIENT_B)

re: fclean all

.PHONY: all clean fclean re bonus