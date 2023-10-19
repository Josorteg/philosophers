# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/13 09:28:02 by josorteg          #+#    #+#              #
#    Updated: 2023/10/06 18:49:17 by josorteg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = philo
CC = gcc
RM = rm -rf
LIBC = ar -rcs
FLAGS = -Wall -Wextra -Werror -g 
#-fsanitize=thread

#------------------------------SORUCES-----------------------------------------#

SRC = main.c check.c init.c utils.c rutina.c
PATH_SRC = ./src/
INC = 	-I ./inc/\

#------------------------------DIRECTORIES------------------------------------#

F_OBJ = $(PATH_SRC)obj/
OBJ = $(addprefix $(F_OBJ), $(SRC:.c=.o))
DEP = $(addprefix $(F_OBJ), $(SRC:.c=.d))

#------------------------------MAKE RULES-------------------------------------#

all : dir $(NAME)
-include $(DEP)

dir:
	@mkdir -p $(F_OBJ)

$(F_OBJ)%.o:$(PATH_SRC)%.c
	@$(CC) -MMD $(FLAGS) -c $< -o $@ $(INC)
$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(INC)

#---------------------------------CLEAN---------------------------------------#

.PHONY: clean fclean re

fclean: clean
	$(RM) $(NAME)

clean:
	$(RM) ./src/obj

re: fclean all
