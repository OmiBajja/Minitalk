OBJDIR = obj
SRCDIR = src

CC = cc
VPATH = $(SRCDIR)
FLAGS = -Wall -Wextra -Werror -O3
SERVER = server
CLIENT = client
SRCS_SERVER = server.c
SRCS_CLIENT = client.c

OBJ_SERVER = $(addprefix $(OBJDIR)/, $(SRCS_SERVER:.c=.o))
OBJ_CLIENT = $(addprefix $(OBJDIR)/, $(SRCS_CLIENT:.c=.o))

PRINTF_DIR = include/ft_printf
PRINTF_LIB = $(PRINTF_DIR)/printf.a
INCLUDE_PATH = -I./include -I./$(PRINTF_DIR)/include
CFLAGS = $(FLAGS) $(INCLUDE_PATH)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(V)$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

all: $(SERVER) $(CLIENT)

$(PRINTF_LIB):
	@cd $(PRINTF_DIR) && $(MAKE)

$(SERVER): $(OBJDIR) $(PRINTF_LIB) $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) -L$(PRINTF_DIR) -l:printf.a -o $(SERVER)

$(CLIENT): $(OBJDIR) $(PRINTF_LIB) $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) -L$(PRINTF_DIR) -l:printf.a -o $(CLIENT)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)
	@cd $(PRINTF_DIR) && $(MAKE) clean

fclean: clean
	rm -rf $(SERVER) $(CLIENT)
	@cd $(PRINTF_DIR) && $(MAKE) fclean

re: fclean all

.PHONY: all clean fclean re