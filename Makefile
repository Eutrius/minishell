NAME = minishell

LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a
LIBFT_FLAGS = -L$(LIBFT_PATH) -lft

CC = cc
CFLAGS = -Wall -Werror -Wextra -I$(LIBFT_PATH) -Iincludes 
RM = rm -rf

SRC_DIR = srcs
OBJ_DIR = objs

SRC = minishell.c \
	  parsing.c \
	  builtins.c\
	  pathfinder.c

OBJS = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))


$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_FLAGS) -lreadline
	@echo "LETS GO BASH BROS!"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ 

all: $(NAME)

bonus: all

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH) --no-print-directory

clean:
	@$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_PATH) clean --no-print-directory

fclean:
	@$(RM) $(OBJS)
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean --no-print-directory
	@$(RM) $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re bonus

