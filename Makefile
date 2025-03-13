OBJDIR = obj
SRCDIR = src

CC = cc
VPATH = $(SRCDIR)
FLAGS = -Wall -Wextra -Werror -O3
SERVER = server
CLIENT = client
SRCS_SERVER = server.c
SRCS_CLIENT = client.c

SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus
SRCS_SERVER_BONUS = server_bonus.c
SRCS_CLIENT_BONUS = client_bonus.c

OBJ_SERVER_BONUS = $(addprefix $(OBJDIR)/, $(SRCS_SERVER_BONUS:.c=.o))
OBJ_CLIENT_BONUS = $(addprefix $(OBJDIR)/, $(SRCS_CLIENT_BONUS:.c=.o))

OBJ_SERVER = $(addprefix $(OBJDIR)/, $(SRCS_SERVER:.c=.o))
OBJ_CLIENT = $(addprefix $(OBJDIR)/, $(SRCS_CLIENT:.c=.o))

PRINTF_DIR = include/ft_printf
PRINTF_LIB = $(PRINTF_DIR)/printf.a
INCLUDE_PATH = -I./include -I./$(PRINTF_DIR)/include
CFLAGS = $(FLAGS) $(INCLUDE_PATH)

all: $(SERVER) $(CLIENT)

bonus : $(SERVER_BONUS) $(CLIENT_BONUS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(V)$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(PRINTF_LIB):
	@cd $(PRINTF_DIR) && $(MAKE)

$(SERVER): $(OBJDIR) $(PRINTF_LIB) $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) -L$(PRINTF_DIR) -l:printf.a -o $(SERVER)

$(CLIENT): $(OBJDIR) $(PRINTF_LIB) $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) -L$(PRINTF_DIR) -l:printf.a -o $(CLIENT)

$(SERVER_BONUS): $(OBJDIR) $(PRINTF_LIB) $(OBJ_SERVER_BONUS)
	$(CC) $(CFLAGS) $(OBJ_SERVER_BONUS) -L$(PRINTF_DIR) -l:printf.a -o $(SERVER_BONUS)

$(CLIENT_BONUS): $(OBJDIR) $(PRINTF_LIB) $(OBJ_CLIENT_BONUS)
	$(CC) $(CFLAGS) $(OBJ_CLIENT_BONUS) -L$(PRINTF_DIR) -l:printf.a -o $(CLIENT_BONUS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)
	@cd $(PRINTF_DIR) && $(MAKE) clean && cd ../..

fclean: clean
	rm -rf $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)
	@cd $(PRINTF_DIR) && $(MAKE) fclean && cd ../..

re: fclean all

.PHONY: all clean fclean re PRINTF_LIB bonus