# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/16 20:23:06 by oipadeol          #+#    #+#              #
#    Updated: 2022/01/08 21:53:25 by oipadeol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	philo

# Color codes

RESET	= \033[0m
GREEN	= \033[32m
YELLOW	= \033[33m
BLUE	= \033[34m

CC =	gcc

# Compiling flags
FLAGS = -Wall -Werror -Wextra
LFLAGS = -L$$HOME/.brew/opt/readline/lib -lreadline
CPFLAGS = -I$$HOME/.brew/opt/readline/include

# Folders
SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./includes/
LIBFT_DIR = ./libft/

# Source files and object files
SRC_FILES =	main.c get_next_line/get_next_line.c\
		input_handling/input_handling.c input_handling/input_handling_2.c\
		utils/rot_matrix.c utils/plotline.c utils/small_utils.c\
		utils/node_utils.c utils/mlx_utils.c utils/rotate_image.c\
		utils/graphical_utils.c utils/free_utils.c\

OBJ_FILES = $(SRC_FILES:.c=.o)

# Paths
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)

all: obj $(LIBFT) $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)get_next_line
	@mkdir -p $(OBJ_DIR)input_handling
	@mkdir -p $(OBJ_DIR)utils

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@gcc $(FLAGS) $(CPFLAGS) -I $(LIBFT_DIR) -I $(INC_DIR) -o $@ -c $<

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(INC_DIR)/*.h
	@echo "$(YELLOW)\n      -> Building $(NAME) ...$(RESET)"
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo "$(GREEN)***   Project $(NAME) successfully compiled   ***\n$(RESET)"
	@echo "fdf compiled!"

# clean rule
clean:
	@echo "$(BLUE)***   Deleting all objects from $(NAME)   ...   ***$(RESET)"
	@rm -Rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

# fclean rule
fclean: clean
	@echo "$(BLUE)***   Deleting executable file from $(NAME)   ...   ***$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

# re rule
re: fclean all