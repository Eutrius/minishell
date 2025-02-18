# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jyriarte <jyriarte@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/21 22:09:06 by jyriarte          #+#    #+#              #
#    Updated: 2025/01/28 00:44:42 by jyriarte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
AR = ar rcs
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -I. -Iincludes

LIBFT_SRC = libft/ft_isalpha.c libft/ft_isdigit.c libft/ft_isalnum.c \
			libft/ft_isascii.c libft/ft_isprint.c libft/ft_strlen.c \
			libft/ft_memset.c libft/ft_bzero.c libft/ft_memcpy.c \
			libft/ft_memmove.c libft/ft_strlcpy.c libft/ft_strlcat.c \
			libft/ft_toupper.c libft/ft_tolower.c libft/ft_strchr.c \
			libft/ft_strrchr.c libft/ft_strncmp.c libft/ft_memchr.c \
			libft/ft_memcmp.c libft/ft_strnstr.c libft/ft_atoi.c \
			libft/ft_calloc.c libft/ft_strdup.c libft/ft_substr.c \
			libft/ft_strjoin.c libft/ft_strtrim.c libft/ft_split.c \
			libft/ft_itoa.c libft/ft_strmapi.c libft/ft_striteri.c \
			libft/ft_putchar_fd.c libft/ft_putstr_fd.c libft/ft_putendl_fd.c \
			libft/ft_putnbr_fd.c libft/ft_lstnew.c libft/ft_lstadd_front.c \
			libft/ft_lstsize.c libft/ft_lstlast.c libft/ft_lstadd_back.c \
			libft/ft_lstdelone.c libft/ft_lstclear.c libft/ft_lstiter.c \
			libft/ft_lstmap.c

FR_PRINTF_SRC = ft_printf/ft_printf.c ft_printf/ft_putlchar.c \
			ft_printf/ft_putlstr.c ft_printf/ft_putlmem.c \
			ft_printf/ft_putlint.c ft_printf/ft_putluint.c \
			ft_printf/ft_putlhex.c ft_printf/ft_putlnbr_base.c \
			ft_printf/ft_print_format.c ft_printf/ft_print_format_utils.c \
			ft_printf/ft_nbrlen_base.c ft_printf/ft_putlnchar.c 

GET_NEXT_LINE_SRC = get_next_line/get_next_line.c \
					get_next_line/get_next_line_utils.c \
					get_next_line/get_next_line_bonus.c

OTHERS_SRC = others/ft_strlappend.c others/ft_maxint.c \
			 others/ft_strndup.c others/ft_strcmp.c \
			 others/ft_strslen.c others/ft_strscat.c \
			 others/ft_free_strs.c others/ft_strsmapi.c \
			 others/ft_print_strs.c others/ft_strsdup.c \
			 others/ft_pointnew.c others/ft_pointscat.c \
			 others/ft_free_points.c others/ft_pointcmp.c \



OBJ = $(LIBFT_SRC:.c=.o) $(FR_PRINTF_SRC:.c=.o) $(GET_NEXT_LINE_SRC:.c=.o) $(OTHERS_SRC:.c=.o)

$(NAME): $(OBJ)
	@$(AR) $@ $^
	@echo "libft compiled OK!"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	@$(RM) $(OBJ)
	@echo "libft cleaned!"

fclean: 
	@$(RM) $(OBJ)
	@$(RM) $(NAME) 
	@echo "libft removed!"

re: fclean all

.PHONY: all clean fclean re
