# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 11:18:50 by abourdon          #+#    #+#              #
#    Updated: 2023/06/28 14:33:26 by abourdon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Werror -Wextra -I./include/ -g3
Ldflags = -Lmlx -lX11 -lXext -lz -lm
MLX_PATH = ./mlx-linux/
Libs = -L./mlx-linux
LIBFT_PATH = ./libft/
LIBFT = libft/libft.a
LIBMLX = mlx-linux/libmlx.a
RM = rm -rf

GREEN=\033[33;32m
BLUE=\033[0;34m
BOLD=\033[1m
RESET=\033[0m

SRC =	src/main.c \
	src/utils/free_parsing.c \
	src/utils/free_parsing2.c \
	src/utils/free_graphic.c \
	src/utils/utils.c \
	src/parsing/get_map_info.c \
	src/parsing/check_map.c \
	src/parsing/cut_map.c \
	src/parsing/make_tab.c \
	src/parsing/check_elements.c \
	src/parsing/check_identifier.c \
	src/graphic/window.c \
	src/graphic/rayon.c \
	src/graphic/draw_map.c \
	src/graphic/draw_tools.c \
	src/graphic/key_imput.c \
	src/graphic/texture.c \


OBJ = $(SRC:.c=.o)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@ 

$(NAME): $(LIBFT) $(LIBMLX) $(OBJ)
	@echo "$(BLUE)$(BOLD)Compiling $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBMLX) -o $(NAME) $(Ldflags)
	@echo "$(GREEN)$(BOLD)$(NAME) compiled!$(RESET)"

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_PATH)
$(LIBMLX):
	@make --no-print-directory -C $(MLX_PATH)

all: $(NAME)

clean:
	@echo "$(BLUE)$(BOLD)Cleaning object files...$(RESET)"
	@$(RM) $(OBJ)
	@make clean --no-print-directory -C $(LIBFT_PATH)
	@make clean --no-print-directory -C $(MLX_PATH)

fclean: clean
	@echo "$(BLUE)$(BOLD)Cleaning $(NAME)...$(RESET)"
	@$(RM) $(NAME)
	@make fclean --no-print-directory -C $(LIBFT_PATH)

re: fclean all

.PHONY: init all clean fclean re
