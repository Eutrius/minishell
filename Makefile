NAME = minishell

LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a
LIBFT_FLAGS = -L$(LIBFT_PATH) -lft

CC = cc
CFLAGS = -Wall -Werror -Wextra -I$(LIBFT_PATH) -Iincludes -g -O3
RM = rm -rf

OBJS_DIR = objs
SRCS_DIR = srcs

SRC = srcs/main.c \
	  srcs/init.c \
	  srcs/parse/parse.c \
	  srcs/parse/utils.c \
	  srcs/parse/split.c \
	  srcs/parse/extract.c \
	  srcs/builtins/utils.c\
	  srcs/builtins/echo.c \
	  srcs/builtins/exit.c \
	  srcs/builtins/export.c \
	  srcs/builtins/env.c \
	  srcs/builtins/cd.c \
	  srcs/builtins/pwd.c \
	  srcs/builtins/unset.c \
		srcs/builtins/export_utils.c\
	  srcs/pathfinder.c

OBJ = $(SRC:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_FLAGS) -lreadline
	@echo "LETS GO BASH BROS!"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

bonus: all

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH) --no-print-directory

clean:
	@$(RM) $(OBJ)
	@$(RM) $(OBJS_DIR)
	@$(MAKE) -C $(LIBFT_PATH) clean --no-print-directory

fclean:
	@$(RM) $(OBJ)
	@$(RM) $(OBJS_DIR)
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean --no-print-directory

run: $(NAME)
	@./$(NAME)

re: fclean all

.PHONY: all clean fclean re bonus run

