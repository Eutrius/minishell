NAME = minishell
TITLE = minishell

LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a
LIBFT_FLAGS = -L$(LIBFT_PATH) -lft

CC = cc
CFLAGS = -Wall -Werror -Wextra -I$(LIBFT_PATH) -Iincludes -g -gdwarf-4 
RM = rm -rf

OBJS_DIR = objs
SRCS_DIR = srcs

SRC = srcs/main.c \
	  srcs/init.c \
	  srcs/signals.c \
	  srcs/pathfinder.c \
	  srcs/parse/parse.c \
	  srcs/parse/utils.c \
	  srcs/parse/split.c \
	  srcs/parse/extract.c \
	  srcs/parse/check.c \
	  srcs/parse/extract_utils.c \
	  srcs/parse/token.c \
	  srcs/parse/extra.c \
	  srcs/parse/prepare.c \
	  srcs/parse/heredoc.c \
	  srcs/parse/parse_utils.c \
	  srcs/expand/expand_var.c\
	  srcs/expand/expand_wildcards.c\
	  srcs/expand/expand_utils.c\
	  srcs/expand/remove_quotes.c\
	  srcs/expand/match_wildcard.c\
	  srcs/expand/get_files.c\
	  srcs/builtins/utils.c\
	  srcs/builtins/echo.c \
	  srcs/builtins/exit.c \
	  srcs/builtins/export.c \
	  srcs/builtins/env.c \
	  srcs/builtins/cd.c \
	  srcs/builtins/pwd.c \
	  srcs/builtins/unset.c \
	  srcs/builtins/export_utils.c\
	  srcs/builtins/filter_builtins.c\
	  srcs/builtins/memory_handling.c\
	  srcs/utils/print_errors.c\
	  srcs/executor/executor.c\
	  srcs/executor/custom_cmds.c\
	  srcs/executor/redirect_utils.c\
	  srcs/executor/executor_utils.c\
	  srcs/executor/pathfinder.c\
	  srcs/executor/expand_utils.c

OBJ = $(SRC:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_FLAGS) -lreadline
	@printf "\n\033[1A\033[K"
	@printf "\033[0;32m$(TITLE) compiled OK!\n"
	@printf "LETS GO BASH BROS!\n"
	@printf "\033[0;37m"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "\033[0;37m Generating $(TITLE) objects... %-33.33s\r" $@
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

bonus: all

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH) --no-print-directory

clean:
	@$(RM) $(OBJ)
	@$(RM) $(OBJS_DIR)
	@$(MAKE) -C $(LIBFT_PATH) clean --no-print-directory
	@printf "\033[0;31m$(TITLE) cleaned!\n"
	@printf "\033[0;37m"

fclean:
	@$(RM) $(OBJ)
	@$(RM) $(OBJS_DIR)
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean --no-print-directory
	@printf "\033[0;31m$(TITLE) removed!\n"
	@printf "\033[0;37m"


re: fclean all

run: $(NAME)
	@clear
	@./$(NAME)

valgrind: $(NAME)
	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=supp.supp ./$(NAME)

.PHONY: all clean fclean re bonus run valgrind

