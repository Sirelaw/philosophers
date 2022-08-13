# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/16 20:23:06 by oipadeol          #+#    #+#              #
#    Updated: 2022/08/14 00:35:08 by oipadeol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	philo
BONUS_NAME = bonus_philo
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

# Source files and object files
SRC_FILES =	main.c input_handling.c living.c utils_helpers/ft_atoi.c\
			utils_helpers/fork_utils.c utils_helpers/timing_utils.c
			
OBJ_FILES = $(SRC_FILES:.c=.o)

# Paths
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

all: obj $(NAME)

bonus:
	@cd ../philo_bonus && $(MAKE)
	@cp ../philo_bonus/philo_bonus philo_bonus

obj:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)utils_helpers
	@mkdir -p $(OBJ_DIR)input_handling
	@mkdir -p $(OBJ_DIR)utils

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@$(CC) $(FLAGS) $(CPFLAGS) -I $(INC_DIR) -o $@ -c $<

$(NAME): $(OBJ) $(INC_DIR)/*.h
	@echo "$(YELLOW)\n      -> Building $(NAME) ...$(RESET)"
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)***   Project $(NAME) successfully compiled   ***\n$(RESET)"
	@echo "$(NAME) compiled!"

# clean rule
clean:
	@echo "$(BLUE)***   Deleting all objects from $(NAME)   ...   ***$(RESET)"
	@rm -Rf $(OBJ_DIR)

# fclean rule
fclean: clean
	@echo "$(BLUE)***   Deleting executable file from $(NAME)   ...   ***$(RESET)"
	@rm -f $(NAME)
	@rm -f philo_bonus

# re rule
re: fclean all