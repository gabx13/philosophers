# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgabovs <vgabovs@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/17 12:03:58 by vgabovs           #+#    #+#              #
#    Updated: 2024/06/25 20:16:43 by vgabovs          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = src
OBJ_DIR = obj
SRC = $(wildcard src/*.c)
OBJ	= $(SRC:%.c=$(OBJ_DIR)/%.o)
PHILO_H = ./inc/philo.h

CC = gcc
CCS = $(CC) #-fsanitize=thread -g
CFLAGS = -Wall -Wextra -Werror -Iinc

NONE='\033[0m'
GREEN='\033[32m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'
WARNING='\033[33m'
RED='\033[31m'

VALG = valgrind  --tool=helgrind --tool=drd #--leak-check=full#-s --show-leak-kinds=all --show-error-list=yes
AT = leaks -atExit --

USE_SANITIZER = 1

ifeq ($(USE_SANITIZER), 1)
	CCFLAGS = $(CCS)
else
	CCFLAGS = $(CC)
endif

all: $(NAME)

$(NAME): $(OBJ)
	@$(CCFLAGS) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo $(GREEN) $(NAME)" compiled!"$(NONE)

$(OBJ_DIR)/%.o: %.c $(PHILO_H)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/src
	@if [ "$(USE_SANITIZER)" = "1" ]; then $(CCS) $(CFLAGS) -c $< -o $@ ; else $(CC) -g $(CFLAGS) -c $< -o $@ ; fi

val: USE_SANITIZER = 0
val: fclean $(OBJ) $(LIBFTA) $(SRC)
	@$(CC) $(OBJ) $(LFLAGS) -o $(NAME) $(LIBFTA)
	@$(VALG) ./$(NAME)  50 400 200 200 5
	@echo $(GREEN)"- Compiled with valgrind -"$(NONE)

clean:
	@rm -rf $(OBJ_DIR)
	@echo $(GRAY)" Object files removed"$(NONE)

fclean: clean
	@rm -f $(NAME)
	@echo $(GRAY)" "$(NAME)" removed"$(NONE)

re: fclean all

.PHONY: all clean fclean re val
